#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T13:52:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GA_Galopp_kursa_darbs
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Console.cpp \
    EvaluationFunctionPlayer.cpp \
    Game.cpp \
    GeneticAlgorithm.cpp \
    HumanPlayer.cpp \
    Player.cpp \
    RandomPlayer.cpp \
    Tournament.cpp \
    optimizingphase.cpp \
    gamingphase.cpp \
    coefficientmanager.cpp \
    humanplayerinterface.cpp \
    eksperiment.cpp

HEADERS  += mainwindow.h \
    Console.h \
    Game.h \
    GeneticAlgorithm.h \
    Player.h \
    Tournament.h \
    optimizingphase.h \
    gamingphase.h \
    coefficientmanager.h \
    sleeper.h \
    humanplayerinterface.h \
    eksperiment.h

FORMS    += mainwindow.ui \
    optimizingphase.ui \
    gamingphase.ui \
    coefficientmanager.ui \
    humanplayerinterface.ui \
    eksperiment.ui
