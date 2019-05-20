#include <QCoreApplication>
#include "neuronet.h"
#include <iostream>
#include <QFile>
#include <QDebug>
#include "MultilayerPerceptron.h"
#include <QDataStream>

struct Weights
{
    int ins;
    int outs;
    float w[1000];
};

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

    QFile file2("weights");
    file2.open(QIODevice::ReadOnly);

    std::vector<WeightMatrix> matrix;

    while (true)
    {
        Weights w;

        auto c = sizeof(Weights);
        auto readed = file2.read((char*)&w, c);
        if (readed < c)
            break;
        WeightMatrix wm(w.ins,w.outs, 0);
        wm.inputDim = w.ins;
        wm.outputDim = w.outs;
        wm.w.clear();
        for (int i =0; i<wm.outputDim*wm.inputDim;i++)
            wm.w.push_back(w.w[i]);

        matrix.push_back(wm);
    }

    file2.close();

    mlp->setWeights(matrix);

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

    /* QFile file2("weights");
    file2.open(QIODevice::WriteOnly);

    for (WeightMatrix wg : ew)
    {
        Weights w;
        memset(w.w,0x00,1000);
        w.ins = wg.inputDim;
        w.outs = wg.outputDim;

        for (int i = 0; i<wg.w.size(); i++)
            w.w[i] = wg.w[i];

        auto c = sizeof(w);
        auto readed = file2.write((char*)&w,c);
        file2.flush();
    }

    file2.close();*/

    return a.exec();
}
