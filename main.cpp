#include <QCoreApplication>
#include "neuronet.h"
#include <iostream>
#include <QFile>
#include <QDebug>
#include "MultilayerPerceptron.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<QVector<float>> v;

    QFile file("learning.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        return 1;
    }

    while (!file.atEnd()) {
        QVector<float> floats;
        QByteArray line = file.readLine();
        auto strings = line.split(',');
        for (auto s : strings)
        {
            floats.append(s.trimmed().toFloat());
        }

        v.append(floats);
    }

    v.remove(0);

    auto mlp = new MultilayerPerceptron(4, 1);
    mlp->addHiddenLayer(10);
    mlp->addHiddenLayer(10);
    mlp->init();

    auto bw = mlp->getWeights();

    std::vector<MultilayerPerceptron::TrainingElement> trainingSet;

    for  (auto vv: v)
    {
        std::vector<float> teInput;
        for (int i = 0; i<vv.count()-1; i++)
        {
            teInput.push_back(vv[i] != 0 ? 1/vv[i]:0.0f);
        }
        std::vector<float> teOutput;
        teOutput.push_back(vv[vv.count()-1]);

        trainingSet.push_back(MultilayerPerceptron::TrainingElement(teInput, teOutput));
    }

    mlp->setTrainingSet(trainingSet);

    float error = 10;
    while (error > 0.01)
    {
        error = mlp->train(0.5f);
        qDebug() << error;
    }

    std::vector<float> ins;
    ins.push_back(1/(float)2);
    ins.push_back(1/(float)1000);
    ins.push_back(1/(float)10);
    ins.push_back(1.0f);
    auto out = mlp->classify(ins);

    auto ew = mlp->getWeights();

    QFile wf("weights", QIODevice::WriteOnly);

    for (WeightMatrix m : ew)
    {
        wf.write(QString::number(m.inputDim));
        wf.write(QString::number(m.outputDim));
    }

    return a.exec();
}
