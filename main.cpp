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
    ins.push_back(5);
    ins.push_back(2000);
    ins.push_back(1);
    ins.push_back(1);

    Analyze an;

    an.loadWeights();
    an.train(0.001, "learning.csv");
    //an.saveWeights();

    auto out = an.calcResult(ins);
    return a.exec();
}
