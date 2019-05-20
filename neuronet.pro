QT += core
QT -= gui

CONFIG += c++11

TARGET = neuronet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    neuro.cpp \
    neurolayer.cpp \
    neuronet.cpp \
    MultilayerPerceptron.cc

HEADERS += \
    neuro.h \
    random.h \
    neurolayer.h \
    neuronet.h \
    MultilayerPerceptron.h
