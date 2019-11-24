//
// Created by Douglas Wilcox on 2019-03-30.
//

#include "PField.h"

using namespace std;


//constructor
PField::PField(QGraphicsScene *scene, int sizeX, int sizeY, int gridsize)
    : myGridSize(gridsize), myFieldWidth(sizeX), myFieldHeight(sizeY), myScene(scene)
{
    int size = myFieldHeight * myFieldWidth;

    myClearTimer = new QTimer;
    connect(myClearTimer, SIGNAL(timeout()), this, SLOT(ClearFilledRows()));


    myIntField.reserve(size);
    myIntField.resize(size);

    tempIntField.reserve(size);
    tempIntField.resize(size);

    myTetrinoField.reserve(size);
    myTetrinoField.resize(size);
}

//destructor

PField::~PField() {
    delete myClearTimer;
}


void PField::PFieldInit() {
    myIntField.clear();
    tempIntField.clear();
    myFilledRows.clear();

    for(int i = 0; i < myTetrinoField.size(); i++)
    {
        if (myTetrinoField[i].get() != nullptr)
        {
            if (myTetrinoField[i].get()->scene() != NULL)
            {
                myScene->removeItem(myTetrinoField[i].get());
            }
        }
    }

    //create walls and draw them in dark blue
    for(int y = 0; y < myFieldHeight; y++)
    {
        for(int x = 0; x < myFieldWidth; x++)
        {
            int index = y * myFieldWidth + x;
            myIntField[index] = (x==0 || x == myFieldWidth -1 || y == myFieldHeight - 1) ? 1 : 0;

            if (myIntField[index] == 1)
            {
                //create a block at this spot
                myTetrinoField[index] = make_unique<QGraphicsRectItem>();
                myTetrinoField[index]->setRect(0, 0, myGridSize, myGridSize);//sets UL corner, then offset for LR corner
                myTetrinoField[index]->setBrush(Qt::darkBlue); //setBrush for color
                myTetrinoField[index]->setPos(x*myGridSize, y*myGridSize);
                myScene->addItem(myTetrinoField[index].get());
            }
        }
    }

    ResetTempIntField();
}


int PField::GetFieldWidth() {
    return myFieldWidth;
}

int PField::CheckIntField(int index) {
    return myIntField[index];
}

void PField::PutPieceToField(int index, QColor color) {
    //set this position to 2 to distinguish from wall
    myIntField[index] = 2;

    //how create and draw a rect at this location;
    myTetrinoField[index] = make_unique<QGraphicsRectItem>();
    myTetrinoField[index]->setRect(0, 0, myGridSize, myGridSize);//sets UL corner, then offset for LR corner
    myTetrinoField[index]->setBrush(color); //setBrush for color

    int fieldPosX = index % myFieldWidth;
    int fieldPosY = index / myFieldWidth;

    myTetrinoField[index]->setPos(fieldPosX*myGridSize, fieldPosY*myGridSize);
    myScene->addItem(myTetrinoField[index].get());
}

void PField::CheckForFilledRow() {
//    vector<int> filledRows;
    int row = 0;
    myFilledRows.clear();

    //find filled rows
    for(int y = 0; y < myFieldHeight - 1; y++)  //y steps down through rows (ignoring last)
    {
        bool filled = true; //assume this row is filled

        for(int x = 0; x < myFieldWidth; x++) //x steps across the row checking each pos
        {
            int index = y * myFieldWidth + x;

            if( myIntField[index] == 0 ) //empty positions are 0
            {
                //this row is not filled, move to next row
                filled = false;
                break;
            }
        }
        if (filled)
        {
            myFilledRows.push_back(row);
        }
        row++;
    }

    //turn this row yellow
    for (int thisrow : myFilledRows)
    {
        int y = thisrow;
        for(int x = 0; x < myFieldWidth; x++) //x steps across the row
        {
            int index = y * myFieldWidth + x;
            if (myIntField[index] != 1)
            {
                myTetrinoField[index]->setBrush(Qt::yellow);
            }
            myClearTimer->start(500);
        }
    }
}


void PField::ClearFilledRows() {

    myClearTimer->stop();
    ResetTempIntField();


    //first, remove blocks and set ints to zero
    for(auto thisrow : myFilledRows)
    {
        //clear and remove any QGraphicsItems in this row
        int y = thisrow;
        for(int x = 0; x < myFieldWidth; x++) //x steps across the row
        {
            int index = y * myFieldWidth + x;

            if (myIntField[index] != 1) //do not remove walls
            {
                if (myIntField[index] == 2)
                {
                    myScene->removeItem( myTetrinoField[index].get() );
                    myTetrinoField[index] = nullptr;
                    myIntField[index] = 0;
                }
            }
        }
    }


    //now move blocks above down
    for(int thisrow : myFilledRows)
    {
        for(int y = thisrow; y > 0; y-- )
        {
            for(int x = 0; x < myFieldWidth; x++) //x steps across this row
            {
                int index = y * myFieldWidth + x;

                if (myIntField[index] != 1) //do not move wall pieces
                {
                    //move any blocks above down to this row
                    if (myTetrinoField[index - myFieldWidth] != nullptr)
                    {
//                        cout << "row/block: " << y << "/" << x << endl;
                        myTetrinoField[index - myFieldWidth]->setPos(x*myGridSize, y*myGridSize);
                    }

                    //and update their indices
                    myTetrinoField[index] = myTetrinoField[index - myFieldWidth];
                    myTetrinoField[index - myFieldWidth] = nullptr;
                    myIntField[index] = myIntField[index - myFieldWidth]; //set int to row above
                }
            }
        }

    }
}



int PField::GetNumFilledRows() {
    return myFilledRows.size();
}

void PField::ResetNumFilledRows() {
    myFilledRows.clear();
}


//DEBUGGING / TESTING


void PField::PrintField() {

    cout << "_____INT FIELD_____" << endl;

    for(int y = 0; y < myFieldHeight; y++)
    {
        for (int x = 0; x < myFieldWidth; x++)
        {
            int index = y * myFieldWidth + x;
            cout << myIntField[index];
        }
        cout << endl;
    }

    cout << "___________________" << endl << endl;
}


void PField::ResetTempIntField() {
    for (int x = 0; x < myIntField.size(); x++)
    {
        tempIntField[x] = myIntField[x];
    }
}


void PField::PrintTempIntField() {

    for(int y = 0; y < myFieldHeight; y++)
    {
        for (int x = 0; x < myFieldWidth; x++)
        {
            int index = y * myFieldWidth + x;
            cout << tempIntField[index];
        }
        cout << endl;
    }
    cout << "___________" << endl << endl;
}


void PField::PutTempIntField(int index) {
    tempIntField[index] = 1;
}
