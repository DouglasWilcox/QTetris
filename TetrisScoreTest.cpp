#include "TestHarness.h"
#include "TetrisScore.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Rename this file to match the functionality under test. E.g., StringTest.
// Add tests and CHECKs as required





TEST(init, TetrisScore)
{
    auto test = make_unique<TetrisScore>();

    test->setScore(100);

    CHECK_EQUAL(test->getScore(), 100);

    test->setScore(200);

    CHECK_EQUAL(test->getScore(), 200);

    test->setScore(300);

    CHECK_EQUAL(test->getScore(), 300);

    test->setScore(0);

    CHECK_EQUAL(test->getScore(), 0);
}


TEST(add_score, TetrisScore)
{
    auto test = make_unique<TetrisScore>();

    test->setScore(100);

    CHECK_EQUAL(test->getScore(), 100);

    test->addToScore(45);
    test->addToScore(55);
    test->addToScore(30);

    CHECK_EQUAL(test->getScore(), 230);

}



TEST(reset_score, TetrisScore)
{
    auto test = make_unique<TetrisScore>();

    test->setScore(100);

    CHECK_EQUAL(test->getScore(), 100);

    test->addToScore(45);
    test->addToScore(-30);
    test->addToScore(30);

    CHECK_EQUAL(test->getScore(), 145);

    test->resetScore();

    CHECK_EQUAL(test->getScore(), 0);
}



