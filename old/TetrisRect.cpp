//
// Created by Douglas Wilcox on 3/11/19.
//

#include <Qt>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "TetrisRect.h"
#include "Bullet.h"
#include <QDebug>
#include <memory>

using namespace Qt;
using namespace std;

//
//
//void TetrisRect::keyPressEvent(QKeyEvent *event) {
//
//    QGraphicsItem::keyPressEvent(event);
////    qDebug() << "key press!!";
//    if (event->key() == Key_Left){
//        if ( pos().x() >= 20 ){
//            setPos(x() - 10, y());
//        }
////        CheckCollisions(mySquares, myTetrinoField);
//
//    } else if (event->key() == Key_Right)
//    {
//        if ( pos().x() <= 90 ){
//            setPos(x() + 10, y());
//        }
//
//    } else if (event->key() == Key_Up)
//    {
//        if (pos().y() >= 10) {
//            setPos(x(), y() - 10);
//        }
//
//    } else if (event->key() == Key_Down)
//    {
//        if (pos().y() <= 150) {
//            setPos(x(), y() + 10);
//        }
//
//
//    } else if (event->key() == Key_Z)
//    {
//        setRotation(rotation() + 90);
//
//
//    } else if (event->key() == Key_Space)
//    {
//        auto bullet = make_unique<Bullet>();
//        bullet->setPos(x()+5, y());
//
//        scene()->addItem(bullet.release());
//    }
//}
//
//void TetrisRect::moveDown() {
//    setPos(x(), y() + 10);
//}




