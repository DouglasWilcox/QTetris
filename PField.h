//
// Created by Douglas Wilcox on 2019-03-30.
//

#ifndef QT_TEST_PFIELD_H
#define QT_TEST_PFIELD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QTimer>
#include <vector>

#include <iostream>

using namespace std;


class PField : public QObject{
    Q_OBJECT
public:
    PField(QGraphicsScene *scene, int sizeX, int sizeY, int gridsize);

    virtual ~PField();

    void PFieldInit();

    int GetFieldWidth();

    void PutPieceToField(int index, QColor color);

    void CheckForFilledRow();

    int GetNumFilledRows();

    void ResetNumFilledRows();

    int CheckIntField(int index);

    //DEBUGGING / TESTING
    void PrintField();

    void ResetTempIntField();

    void PutTempIntField(int index);

    void PrintTempIntField();


public slots:
    void ClearFilledRows();

private:
    int myGridSize;
    int myFieldWidth;
    int myFieldHeight;
    QGraphicsScene* myScene;

    vector<int> myIntField;
    vector<int> tempIntField;
    QTimer *myClearTimer;
    vector<int> myFilledRows;
    vector<shared_ptr<QGraphicsRectItem>> myTetrinoField;
};

#endif //QT_TEST_PFIELD_H
