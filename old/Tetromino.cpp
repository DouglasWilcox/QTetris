//
// Created by Douglas Wilcox on 2019-03-27.
//

#include "Tetromino.h"



//constructor passes in scene reference and position, reserves 4x4 grid
Tetromino::Tetromino(QGraphicsScene *scene, vector<unique_ptr<TetrisRect>> & pTetrinoField, int x, int y)
        : myScene(scene), myTetrinoField(pTetrinoField), myPosX(x), myPosY(y)
{
    mySquares.reserve(16);
    myShape.reserve(16);


    //connect move down timer
    auto movedowntimer = new QTimer();
    connect(movedowntimer, SIGNAL(timeout()), this, SLOT(moveDown())); //connect syntax example
    movedowntimer->start(1000);  //how to set timer, duration

    //connect
    auto checkcollisiontimer = new QTimer();
    connect(checkcollisiontimer, SIGNAL(timeout()), this, SLOT(CheckCollisions())); //connect syntax example
//    checkcollisiontimer->start(30);  //how to set timer, duration
}



void Tetromino::Spawn() {

    //random generator for piece and color
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 6);
    int piece = uniform_dist(e1);
    int color = uniform_dist(e1);

    //create master control object
    masterSquare = make_unique<TetrisRect>();
    masterSquare->setRect(0, 0, 0, 0);
    masterSquare->setBrush(Qt::blue);
    masterSquare->setPos(myPosX, myPosY);
    myScene->addItem(masterSquare.get());
    masterSquare->setFlag(QGraphicsItem::ItemIsFocusable);
    masterSquare->setFocus();


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
            mySquares[idx] = make_unique<TetrisRect>();
            mySquares[idx]->setRect(0, 0, 10, 10);


            switch (color)
            {
                case 0:
                    mySquares[idx]->setBrush(Qt::darkGreen);
                    break;
                case 1:
                    mySquares[idx]->setBrush(Qt::red);
                    break;
                case 2:
                    mySquares[idx]->setBrush(Qt::blue);
                    break;
                case 3:
                    mySquares[idx]->setBrush(Qt::lightGray);
                    break;
                case 4:
                    mySquares[idx]->setBrush(Qt::darkBlue);
                    break;
                case 5:
                    mySquares[idx]->setBrush(Qt::darkCyan);
                    break;
                case 6:
                    mySquares[idx]->setBrush(Qt::darkYellow);
                    break;
            }

            mySquares[idx].get()->setParentItem(masterSquare.get());

//            masterSquare->setSquares(mySquares);
//            masterSquare->setTetrinoField(myTetrinoField);

            //calculate position correctly
            int xOffset = idx % 4;
            int yOffset = idx / 4;

            mySquares[idx]->setPos(xOffset * 10 - 20, yOffset * 10 - 20);

        }
    }

}


void Tetromino::Drop() {

}


int Tetromino::GetRotatedPieceIndex(int gridX, int gridY, int r) {


    int whichPieceIndex = 0;
    switch (r % 4)
    {
        case 0:                 // 0 degrees			// 0  1  2  3
            whichPieceIndex = gridY * 4 + gridX;			// 4  5  6  7
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
            whichPieceIndex = 3 - gridY + (gridX * 4);		// 2  6 10 14
            break;						                // 1  5  9 13
    }								                    // 0  4  8 12

    return whichPieceIndex;
}



void Tetromino::moveDown() {
    //move down once a second
//    masterSquare->moveDown();

}

void Tetromino::CheckCollisions() {

//    cout << "I'm checking now" << endl;
    for(auto &fielditem : myTetrinoField)
    {
        if (fielditem->collidesWithItem(masterSquare.get(), Qt::IntersectsItemBoundingRect))
        {
             cout << "MASTERSQUARE Found Collision!" << endl;
        }

    }


//    return false;
}


