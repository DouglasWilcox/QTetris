
#include <iostream>
#include <cstdlib>
#include <memory>
#include <iostream>

#include <QGraphicsView>
#include <QGraphicsItem>

#include "TestHarness.h"
#include "TetrisPiece.h"
#include "PField.h"
#include "Tetris.h"


//#include "KeyPress.h"

using namespace std;

int nFieldWidth = 12;
int nFieldHeight = 18;


int main(int argc, char *argv[])
{
    //CPP Unit tests
    srand(time_t(NULL));

    TestResult tr;
    TestRegistry::runAllTests(tr);

    //Qt application
    QApplication a(argc, argv);

//    auto tetris = make_unique<Tetris>(12, 18, 22);
    auto tetris = make_unique<Tetris>(12, 20, 22);

    tetris->Init();
    auto tetrisview = tetris->getMyView();
    tetrisview->show();

    return a.exec();
}

