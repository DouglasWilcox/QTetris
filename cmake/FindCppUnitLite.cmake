set(FIND_CPPUNITLITE_PATHS
        /Library/Frameworks/CppUnitLite
        )

find_path(CPPUNITLITE_INCLUDE_DIR Failure.h Test.h TestHarness.h TestRegistry.h TestResult.h
        PATH_SUFFIXES include
        PATHS ${FIND_CPPUNITLITE_PATHS})


find_library(CPPUNITLITE_LIBRARY
        NAMES CppUnitLite
        PATH_SUFFIXES lib
        PATHS ${FIND_CPPUNITLITE_PATHS})