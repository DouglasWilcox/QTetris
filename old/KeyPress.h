//
// Created by Douglas Wilcox on 2019-03-27.
//

#ifndef QT_TEST_KEYPRESS_H
#define QT_TEST_KEYPRESS_H


#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <iostream>

class KeyPress : public QWidget
{
Q_OBJECT

public:
//    KeyPress(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
//    QLabel *myLabelText;
};


#endif //QT_TEST_KEYPRESS_H
