cmake_minimum_required(VERSION 3.12)
project(QTetris)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/dooglife/Qt/5.12.1/clang_64/lib/cmake")

set(SOURCE_FILES main.cpp
        Bullet.cpp
        TetrisPiece.cpp
        PField.cpp
        Tetris.cpp
        TetrisScore.cpp)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

add_executable(QTetris ${SOURCE_FILES})

#include(FindPkgConfig)
find_package(CppUnitLite)
include_directories(${CPPUNITLITE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CPPUNITLITE_LIBRARY})

target_link_libraries(QTetris Qt5::Core)
target_link_libraries(QTetris Qt5::Widgets)
target_link_libraries(QTetris Qt5::Quick)