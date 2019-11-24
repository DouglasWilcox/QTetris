//
// Created by Douglas Wilcox on 2019-03-31.
//

#ifndef QT_TEST_TETRIS_H
#define QT_TEST_TETRIS_H


#include "TetrisScore.h"
#include "TetrisPiece.h"
#include "PField.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>
#include <QTimer>
#include <QObject>
#include <QLabel>
#include <QString>

#include <random>
#include <ctime>
#include <memory>
#include <iostream>
#include <vector>

using namespace std;
using namespace Qt;


//this needs a timer to check that piece is active, spawn new one when not, and manage game state.


class Tetris : public QObject {
    Q_OBJECT
public:
    Tetris(int fieldwidth, int fieldheight, int gridsize);
    void Init();

    const shared_ptr<QGraphicsView> &getMyView() const;
    const unique_ptr<PField> &getMyField() const;
    const shared_ptr<QGraphicsScene> &getMyScene() const;

    void upDateScore();

    virtual ~Tetris();

    static TetrisScore gamescore;

public slots:
    void GameLoop();

private:
    int myFieldWidth;
    int myFieldHeight;
    int myGridSize;
    int mySceneWidth;
    int mySceneHeight;
    int moveDownTime;

    bool isActive;
    QGraphicsTextItem *myScoreText;
    QGraphicsTextItem *myScoreValue;
    QString myScoreValueString;
    QTimer *myGameLoopTimer;
    shared_ptr<QGraphicsView> myView;
    shared_ptr<QGraphicsScene> myScene;
    unique_ptr<PField> myField;
    vector<shared_ptr<TetrisPiece>> myTetrisPieces;

};




#endif //QT_TEST_TETRIS_H
