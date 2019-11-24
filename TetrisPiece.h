//
// Created by Douglas Wilcox on 2019-03-30.
//

#ifndef QT_TEST_TETROPIECE_H
#define QT_TEST_TETROPIECE_H

#include "PField.h"

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QList>
#include <QKeyEvent>
#include <QObject>
#include <QColor>
#include <QTimer>

#include <iostream>
#include <memory>
#include <random>
#include <vector>


using namespace std;

class TetrisPiece: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    TetrisPiece(QGraphicsScene *scene, PField& pTetrinoField, int x, int y, int gridsize);

    virtual ~TetrisPiece();

    void keyPressEvent(QKeyEvent *event) override;

    void Spawn();

    void SetMoveDownTimer(int time);

    void UpdateTempField();

    int GetRotatedPieceIndex(int gridX, int gridY, int r);

    bool CheckMove(int posX, int posY, int rot);

    bool getIsActive() const;

    void FixPiece();

    void Drop();

    bool isEndGame() const;

    int getMyDropRows() const;

public slots:
    void moveDown();

private:
    int startPosY;
    int myPosX;
    int myPosY;
    int myRot;
    int myGridSize;
    int myDropRows;
    bool doCountDropRows;
    bool isActive;
    bool endGame;

    QTimer *myMoveDownTimer;
    QColor myColor;
    QColor myStaticColor;
    vector<int> myShape;
    vector<shared_ptr<QGraphicsRectItem>> mySquares;
    QGraphicsScene* myScene;
    PField &myTetrinoField;

};



#endif //QT_TEST_TETROPIECE_H
