//
// Created by Douglas Wilcox on 2019-03-31.
//

#include "Tetris.h"


Tetris::Tetris(int fieldwidth, int fieldheight, int gridsize)
    : myFieldWidth(fieldwidth), myFieldHeight(fieldheight), myGridSize(gridsize),
    mySceneWidth(fieldwidth * gridsize), mySceneHeight(fieldheight * gridsize)
{}


Tetris::~Tetris() {
    delete myGameLoopTimer;
}

//define the static variable also in the cpp
TetrisScore Tetris::gamescore;


const shared_ptr<QGraphicsView> &Tetris::getMyView() const {
    return myView;
}

void Tetris::Init() {
    isActive = true;
    myScene = make_shared<QGraphicsScene>();

    //setup
    myScene->setSceneRect(0, 0, mySceneWidth, mySceneHeight); //sets UL corner, then offset for LR corner, scrollable area
    QPen pen = QPen(Qt::darkRed);
    QLineF TopLine(myScene->sceneRect().topLeft(), myScene->sceneRect().topRight());
    QLineF RightLine(myScene->sceneRect().topRight(), myScene->sceneRect().bottomRight());
    QLineF LeftLine(myScene->sceneRect().topLeft(), myScene->sceneRect().bottomLeft());
    QLineF BottomLine(myScene->sceneRect().bottomLeft(), myScene->sceneRect().bottomRight());
    myScene->addLine(TopLine, pen);
    myScene->addLine(LeftLine, pen);
    myScene->addLine(RightLine, pen);
    myScene->addLine(BottomLine, pen);

    //add a view
    myView = make_shared<QGraphicsView>(myScene.get());

    //disable scrollbars
    myView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myView->setFixedSize(mySceneWidth*2, mySceneHeight*2);//this is bigger than scene, note.  Objects move in scene space I think.

    //Gameloop timer
    moveDownTime = 1200;
    myGameLoopTimer = new QTimer();
    connect(myGameLoopTimer, SIGNAL(timeout()), this, SLOT(GameLoop())); //connect syntax example
    myGameLoopTimer->start(moveDownTime);  //once a second if previous piece inactive, spawn a new one


    myField = make_unique<PField>(myScene.get(), myFieldWidth, myFieldHeight, myGridSize);
    myField->PFieldInit();
    gamescore.resetScore();
//    myField->PrintField();

    myTetrisPieces.push_back(  make_shared<TetrisPiece>(myScene.get(), *myField, mySceneWidth/2, 2*myGridSize, myGridSize) );
    myTetrisPieces.back().get()->Spawn();

    myScoreValueString = QString::number(gamescore.getScore(), 10);//base 10

    myScoreText = myScene->addText("SCORE: ");
    myScoreValue = myScene->addText(myScoreValueString);
    myScoreText->setPos(-myGridSize/2.0, -myGridSize*3);
    myScoreValue->setPos(myGridSize*8, -myGridSize*3);
}

const unique_ptr<PField> &Tetris::getMyField() const {
    return myField;
}

const shared_ptr<QGraphicsScene> &Tetris::getMyScene() const {
    return myScene;
}

void Tetris::GameLoop() {

    if (!myTetrisPieces.back().get()->isEndGame())
    {
        if ( !myTetrisPieces.back().get()->getIsActive()  )
        {
            if (myTetrisPieces.back().get()->getMyDropRows() > 0)
            {
                gamescore.addToScore( myTetrisPieces.back().get()->getMyDropRows() + 1 );
            }

            //check also for number of filled rows
            int numfilledrows = myField->GetNumFilledRows();

            switch(numfilledrows)
            {
                case 1:
                    gamescore.addToScore( 40 ); // 2 pts per ms
                    cout << "one cleared + 40" << endl;
                    if (moveDownTime > 300)
                    {
                        moveDownTime -= 20;
                    }
                    break;
                case 2:
                    gamescore.addToScore(120); // 2 pts per ms
                    cout << "two cleared + 100" << endl;
                    if (moveDownTime > 300)
                    {
                        moveDownTime -= 40;
                    }
                    break;
                case 3:
                    gamescore.addToScore(300); // 5 pts per ms
                    cout << "three cleared + 300" << endl;
                    if (moveDownTime > 220)
                    {
                        moveDownTime -= 60;
                    }
                    break;
                case 4:
                    gamescore.addToScore(1200); // 8 pts per ms
                    cout << "four cleared + 1200" << endl;
                    if (moveDownTime > 150) //let's be evil
                     {
                        moveDownTime -= 150;
                    }
                    break;
                default:
                    gamescore.addToScore(0);
            }

            upDateScore();


            myTetrisPieces.push_back(  make_shared<TetrisPiece>(myScene.get(), *myField, mySceneWidth/2, 2*myGridSize, myGridSize) );
            myTetrisPieces.back().get()->Spawn();
            myTetrisPieces.back().get()->SetMoveDownTimer(moveDownTime);

//            myField.get()->PrintField();
        }
    } else{
        cout << "__GAMEOVER__\n\nSCORE: " << gamescore.getScore() << endl;
        gamescore.resetScore();
        myField->PFieldInit();


        myTetrisPieces.push_back(  make_shared<TetrisPiece>(myScene.get(), *myField, mySceneWidth/2, 2*myGridSize, myGridSize) );
        myTetrisPieces.back().get()->Spawn();
        moveDownTime = 1200;
    }

}

void Tetris::upDateScore() {

    myScoreValueString = QString::number(gamescore.getScore(), 10);
    myScoreValue->setPlainText(myScoreValueString);

}


