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
    ins.push_back(1/(float)10);
    ins.push_back(1/(float)10000);
    ins.push_back(1/(float)10);
    ins.push_back(0.0f);

    Analyze an;

    an.loadWeights();
    an.train(0.01);
    an.saveWeights();

    auto out = an.calcResult(ins);

    return a.exec();
}
