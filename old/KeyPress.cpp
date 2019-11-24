//
// Created by Douglas Wilcox on 2019-03-27.
//

#include "KeyPress.h"


#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include "KeyPress.h"

//KeyPress::KeyPress(QWidget *parent) :
//        QWidget(parent)
//{
//}

void KeyPress::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        std::cout << "Q pressed" << std::endl;
    }

}

void KeyPress::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        std::cout << "Q RELEASED" << std::endl;
    }

}