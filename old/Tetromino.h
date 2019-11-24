//
// Created by Douglas Wilcox on 2019-03-27.
//

#ifndef QT_TEST_TETROMINO_H
#define QT_TEST_TETROMINO_H

#include <vector>
#include <QGraphicsScene>
#include <QList>
#include <ostream>
#include <iostream>
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>
#include <random>
#include "TetrisRect.h"

using namespace std;
using namespace Qt;




class Tetromino : public QObject{
    Q_OBJECT
public:

    Tetromino(QGraphicsScene *scene, vector<unique_ptr<TetrisRect>>& pTetrinoField, int x, int y);

    void Drop();

    void Spawn();

    int GetRotatedPieceIndex(int gridX, int gridY, int r);


public slots:
    void moveDown();
    void CheckCollisions();


private:

    bool isColliding = false;
    vector<int> myShape;
    vector<TetrisRect> mySquares;
    vector<unique_ptr<TetrisRect>> &myTetrinoField;
    unique_ptr<TetrisRect> masterSquare;
    QGraphicsScene* myScene;
    int myPosX;
    int myPosY;

};

#endif //QT_TEST_TETROMINO_H
