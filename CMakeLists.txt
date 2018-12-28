cmake_minimum_required(VERSION 3.6)
project(groupe)

### Compiler Settings

set(CMAKE_CXX_COMPILER "c++")
set(CMAKE_C_COMPILER "c++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")


### Main Kestrel Program

set(KESTREL_SOURCES
    block.cpp
    block.h
    config.h
    declaration.cpp
    declaration.h
    environment.cpp
    environment.h
    log.cpp
    log.h
    keywords.c
    keywords.h
    lexical.c
    lexical.h
    lexsupport.c
    lexsupport.h
    main.cpp
    main.h
    program.cpp
    program.h
    sets.h
    statement.cpp
    statement.h
    stringpool.c
    stringpool.h
    symboltable.c
    symboltable.h
    expression.cpp
    expression.h
    expression.cpp
    expression.h
    reference.cpp
    reference.h
    type.cpp
    type.h
    CodeGen.cpp
    CodeGen.h
    linklst.h)

add_executable(kestrel ${KESTREL_SOURCES})


### TestLex

set(TESTLEX_SOURCES
        testlex.c
        stringpool.h
        stringpool.c
        symboltable.h
        symboltable.c
        keywords.h
        keywords.c
        log.h
        log.cpp
        lexical.h
        lexical.c)

add_executable(testlex ${TESTLEX_SOURCES})


### tester

set(TESTER_SOURCES
        tests/tester.h
        tests/tester.cpp
        tests/testLexer.cpp
        tests/testLexer.h
        tests/testSymbolTable.cpp
        tests/testSymbolTable.h
        tests/testStringPool.cpp
        tests/testStringPool.h
        tests/testStatement.cpp
        tests/testStatement.h
        tests/testExpression.cpp
        tests/testExpression.h
        tests/testlinklst.cpp
        tests/testlinklst.h
        tests/testCodeGen.cpp
        tests/testCodeGen.h
        expression.cpp
        expression.h
        lexical.h
        lexical.c
        keywords.h
        keywords.c
        symboltable.c
        symboltable.h
        stringpool.c
        stringpool.h
        lexsupport.c
        lexical.h
        log.h
        log.cpp
        block.cpp
        block.h
        declaration.cpp
        declaration.h
        environment.cpp
        environment.h
        statement.cpp
        statement.h
        program.h
        program.cpp
        reference.cpp
        reference.h
        type.cpp
        type.h
        CodeGen.cpp
        CodeGen.h
        linklst.h)

add_executable(tester ${TESTER_SOURCES})
