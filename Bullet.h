//
// Created by Douglas Wilcox on 2019-03-24.
//

#ifndef QT_TEST_BULLET_H
#define QT_TEST_BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

//any class that uses slots has to derive from QObject

class Bullet : public QObject, public QGraphicsRectItem{
    Q_OBJECT //must add this macro to beginning of class to use slots
public:
    Bullet();

public slots:
    //member function goes here to react to a signal
    void move();
};

#endif //QT_TEST_BULLET_H

