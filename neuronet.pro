QT += core
QT -= gui

CONFIG += c++11

TARGET = neuronet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    MultilayerPerceptron.cc \
    analyze.cpp

HEADERS += \
    MultilayerPerceptron.h \
    weights.h \
    analyze.h
