//
// Created by Douglas Wilcox on 2019-03-24.
//

#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>

Bullet::Bullet() {
    //draw rect
    setRect(0, -20, 1, 20);
    setBrush(Qt::blue);

    //connect
    auto timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect syntax example
    timer->start(50);  //how to set timer, duration
}


//because of the timer, this will happen every 50ms
void Bullet::move() {
    //move up
    setPos(x(), y() - 10);
    if (pos().y() < -80) {
        scene()->removeItem(this);
        delete this;
    }

}
