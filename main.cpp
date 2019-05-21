#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QDebug>
#include "analyze.h"
#include <QDataStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<float> ins;
    ins.push_back(10);
    ins.push_back(8000);
    ins.push_back(20);
    ins.push_back(0);

    Analyze an;

    an.loadWeights();
    //an.train(0.001);
    //an.saveWeights();

    auto out = an.calcResult(ins);


    return a.exec();
}
