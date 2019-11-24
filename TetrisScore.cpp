//
// Created by Douglas Wilcox on 2019-04-02.
//

#include "TetrisScore.h"



void TetrisScore::setScore(int score) {
    TetrisScore::myScore = score;
}

int TetrisScore::getScore() const {
    return myScore;
}

void TetrisScore::resetScore() {
    TetrisScore::myScore = 0;
}

TetrisScore::TetrisScore() : myScore(0) {}

void TetrisScore::addToScore(int value) {
    myScore += value;
}
