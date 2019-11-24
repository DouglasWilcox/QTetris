//
// Created by Douglas Wilcox on 2019-04-02.
//

#ifndef QT_TEST_TETRISSCORE_H
#define QT_TEST_TETRISSCORE_H


class TetrisScore {

private:
    int myScore;

public:
    TetrisScore();

    //prohibit copy constructor
    TetrisScore(const TetrisScore&) = delete;

    //prohibit assignment operator
    TetrisScore &operator=(const TetrisScore&) = delete;

    ~TetrisScore() = default;

    void setScore(int score);

    void addToScore(int value);

    int getScore() const;

    void resetScore();

};


#endif //QT_TEST_TETRISSCORE_H
