//
// Created by Douglas Wilcox on 2019-03-30.
//

#include "TetrisPiece.h"

#include <Qt>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <memory>

#include <iostream>

using namespace Qt;
using namespace std;


//constructor
TetrisPiece::TetrisPiece(QGraphicsScene *scene, PField & pTetrinoField, int x, int y, int gridsize)
    : myScene(scene), myTetrinoField(pTetrinoField), myPosX(x), myPosY(y), startPosY(y), myGridSize(gridsize)
{

    //connect
    myMoveDownTimer = new QTimer();
    connect(myMoveDownTimer, SIGNAL(timeout()), this, SLOT(moveDown())); //connect syntax example
    myMoveDownTimer->start(1000);  //how to set timer, duration

    mySquares.reserve(16);
    mySquares.resize(16);
    myShape.reserve(16);
    myShape.resize(16);

}

//destructor
TetrisPiece::~TetrisPiece() {
    delete myMoveDownTimer;
}




void TetrisPiece::Spawn() {

    //draw rect
    setRect(0, 0, 0, 0);
    setPos(myPosX, myPosY);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    myScene->addItem(this);

    //random generator for piece and color
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 6);
    int piece = uniform_dist(e1);
    int color = uniform_dist(e1);
    myRot = 0;


    switch (piece)
    {
        case 0:
            myShape = {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
            break;
        case 1:
            myShape = {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
            break;
        case 2:
            myShape = {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
            break;
        case 3:
            myShape = {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0};
            break;
        case 4:
            myShape = {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0};
            break;
        case 5:
            myShape = {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0};
            break;
        case 6:
            myShape = {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};
            break;
    }



    for(int idx = 0; idx < 16; idx++)
    {

        if (myShape[idx])
        {
            mySquares[idx] = make_unique<QGraphicsRectItem>();
//            mySquares[idx] = new QGraphicsRectItem();
            mySquares[idx]->setRect(0, 0, myGridSize, myGridSize);


            //assign active/static colors
            switch (color)
            {
                case 0:
                    mySquares[idx]->setBrush(Qt::green); //darkGreen
                    myColor = Qt::green;
                    myStaticColor = Qt::darkGreen;
                    break;
                case 1:
                    mySquares[idx]->setBrush(Qt::red); //darkRed
                    myColor = Qt::red;
                    myStaticColor = Qt::darkRed;
                    break;
                case 2:
                    mySquares[idx]->setBrush(Qt::blue); //darkBlue
                    myColor = Qt::blue;
                    myStaticColor = Qt::darkBlue;
                    break;
                case 3:
                    mySquares[idx]->setBrush(Qt::lightGray); //gray, DarkGray
                    myColor = Qt::lightGray;
                    myStaticColor = Qt::darkGray;
                    break;
                case 4:
                    mySquares[idx]->setBrush(Qt::yellow); //darkYellow
                    myColor = Qt::yellow;
                    myStaticColor = Qt::darkYellow;
                    break;
                case 5:
                    mySquares[idx]->setBrush(Qt::cyan); //darkCyan
                    myColor = Qt::cyan;
                    myStaticColor = Qt::darkCyan;
                    break;
                case 6:
                    mySquares[idx]->setBrush(Qt::magenta); //darkMagenta
                    myColor = Qt::magenta;
                    myStaticColor = Qt::darkMagenta;
                    break;
            }

            mySquares[idx]->setParentItem(this);

            //calculate position correctly
            int xOffset = idx % 4;
            int yOffset = idx / 4;

            mySquares[idx]->setPos(xOffset * myGridSize - 2*myGridSize, yOffset * myGridSize - 2*myGridSize);

        }
    }

    //initialize bools
    isActive = true;
    doCountDropRows = false;
    myDropRows = 0;
    endGame = false;

}




int TetrisPiece::GetRotatedPieceIndex(int gridX, int gridY, int r) {


    int whichPieceIndex = 0;
    switch (r % 4)
    {
        case 0:                 // 0 degrees			// 0  1  2  3
            whichPieceIndex = gridY * 4 + gridX;		// 4  5  6  7
            break;						                // 8  9 10 11
                                                        //12 13 14 15

        case 1:                 // 90 degrees           //12  8  4  0
            whichPieceIndex = 12 + gridY - (gridX * 4);	//13  9  5  1
            break;						                //14 10  6  2
            //15 11  7  3

        case 2:                 // 180 degrees			//15 14 13 12
            whichPieceIndex = 15 - (gridY * 4) - gridX;	//11 10  9  8
            break;						                // 7  6  5  4
                                                        // 3  2  1  0

        case 3:                 // 270 degrees			// 3  7 11 15
            whichPieceIndex = 3 - gridY + (gridX * 4);	// 2  6 10 14
            break;						                // 1  5  9 13
    }								                    // 0  4  8 12

    return whichPieceIndex;
}


void TetrisPiece::keyPressEvent(QKeyEvent *event) {

    QGraphicsItem::keyPressEvent(event);
    if (event->key() == Key_Left){

        if (CheckMove( myPosX - myGridSize, myPosY, myRot))
        {
            setPos(x() - myGridSize, y());
            myPosX -= myGridSize;
        }
    } else if (event->key() == Key_Right)
    {

        if (CheckMove( myPosX + myGridSize, myPosY, myRot))
        {
            setPos(x() + myGridSize, y());
            myPosX += myGridSize;
        }
    }
//    else if (event->key() == Key_Up)
//    {
//
//        if (CheckMove( pos().x(), pos().y() - 10, myRot))
//        {
//            setPos(x(), y() - 10);
//            myPosY -= 10;
//        }
//
//
//    }
    else if (event->key() == Key_Down)
    {
        moveDown();

    } else if (event->key() == Key_Z)
    {

        if (CheckMove( myPosX, myPosY, (myRot + 1) % 4))
        {
            setRotation(rotation() + 90);
            myRot = (myRot + 1) % 4;
        }


    } else if (event->key() == Key_Space)
    {
        Drop();
    } else if (event->key() == Key_Q)
    {
        qApp->exit();
    }





}

void TetrisPiece::moveDown() {

    if (isActive)
    {
        if (CheckMove( myPosX, myPosY + myGridSize, myRot))
        {
            setPos(x(), y() + myGridSize);
            myPosY += myGridSize;
            if (doCountDropRows)
            {
                myDropRows++;
            }
        } else{
            // can't move down - plant this piece and spawn a new one
            isActive = false;

            //update field for collision
            FixPiece();

            if (myPosY - startPosY < myGridSize) //game over
            {
                endGame = true;
            }
        }
    }
}


void TetrisPiece::UpdateTempField() {

    myTetrinoField.ResetTempIntField();

    for(int x = 0; x < myShape.size(); x++)  //x steps through this tetrino int shape
    {
        int rPosX = x % 4;
        int rPosY = x / 4;

        int indexRotated = GetRotatedPieceIndex(rPosX, rPosY, myRot);

        // Get index into field zero rot gridY * 4 + gridX
        int fieldindex = ((myPosY-myGridSize)/myGridSize + rPosY) * myTetrinoField.GetFieldWidth() + ((myPosX -2*myGridSize)/myGridSize + rPosX);

        if (myShape[indexRotated] == 1)
        {
            myTetrinoField.PutTempIntField(fieldindex);
        }
    }

}

//test this piece against field if moved or rotated
bool TetrisPiece::CheckMove(int posX, int posY, int rot) {

    for(int x = 0; x < myShape.size(); x++)  //x steps through this tetrino grid
    {
        int rPosX = x % 4;
        int rPosY = x / 4;

        int indexRotated = GetRotatedPieceIndex(rPosX, rPosY, rot);

        // Get index into field zero rot gridY * 4 + gridX
        int fieldindex = ((posY-2*myGridSize)/myGridSize + rPosY) * myTetrinoField.GetFieldWidth() + ((posX -2*myGridSize)/myGridSize + rPosX);

        if (myShape[indexRotated] == 1 && myTetrinoField.CheckIntField(fieldindex) >= 1)
        {
            return false;
        }
    }

    return true;
}

bool TetrisPiece::getIsActive() const {
    return isActive;
}

void TetrisPiece::FixPiece() {

    for(int x = 0; x < myShape.size(); x++)  //x steps through this tetrino grid
    {
        int rPosX = x % 4;
        int rPosY = x / 4;

        int indexRotated = GetRotatedPieceIndex(rPosX, rPosY, myRot);

        // Get index into field zero rot gridY * 4 + gridX
        int fieldindex = ((myPosY-2*myGridSize)/myGridSize + rPosY) * myTetrinoField.GetFieldWidth() + ((myPosX -2*myGridSize)/myGridSize + rPosX);

        if (myShape[indexRotated] == 1 )  //this is a piece that needs to be moved to the board and myIntField
        {
            myTetrinoField.PutPieceToField(fieldindex, myStaticColor);
        }
    }

    //remove master rect
    scene()->removeItem(this);

    myTetrinoField.CheckForFilledRow();
}

void TetrisPiece::Drop() {
    myMoveDownTimer->setInterval(35);
    doCountDropRows = true;
}

bool TetrisPiece::isEndGame() const {
    return endGame;
}

int TetrisPiece::getMyDropRows() const {
    return myDropRows;
}

void TetrisPiece::SetMoveDownTimer(int time) {
    myMoveDownTimer->setInterval(time);
}


