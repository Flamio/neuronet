#include "neuronet.h"
#include <QDebug>

Neuronet::Neuronet(QObject *parent) : QObject(parent), inputLayer(7,1, this), hiddenLayer(7,7, this), outLayer(1,7,this)
{
    auto neuros = inputLayer.getNeuros();

    for (Neuro* n : neuros)
    {
        (*n->getWeights())[0] = 1;
    }
}

float Neuronet::forward(QVector<float> &ins)
{
    QVector<float> insN;

    for (auto i : ins)
        insN.push_back(1.0/(1+exp(-i)));
    auto firstResults = inputLayer.forward(ins);
    auto secondResults = hiddenLayer.forward(firstResults);
    auto v = outLayer.forward(secondResults);

    return v.first();
}

void Neuronet::learn(QVector<QVector<float> > &data)
{
    float error = 10;
    while (error > 0.001)
    {
        error = 0;
        for (auto d : data)
        {
            auto res = d[7];
            d.remove(7);
            auto neuroRes = forward(d);

            float errorT = (neuroRes - res) * (neuroRes - res) / 2;

            auto outNeuro = outLayer.getNeuros().first();

            float b = neuroRes * (1-neuroRes)*(res-neuroRes);

            for (int i = 0 ; i< outNeuro->getWeights()->count(); i++)
            {
                float newWeight = (*outNeuro->getWeights())[i] + hiddenLayer.getNeuros()[i]->getOut()*b*learningRate;
                (*outNeuro->getWeights())[i] = newWeight;
            }

            for (auto j = 0; j < hiddenLayer.getNeuros().count(); j++)
            {
                auto n = hiddenLayer.getNeuros()[j];
                for (int i = 0 ; i< n->getWeights()->count(); i++)
                {
                    float newWeight = (*n->getWeights())[i]  + learningRate*b*(*outNeuro->getWeights())[j]*hiddenLayer.getNeuros()[j]->getOut()
                            *(1 - hiddenLayer.getNeuros()[j]->getOut()*d[i]);
                    (*n->getWeights())[i] = newWeight;
                }

                error+=errorT;
            }

            /*
            float weightDelta = error*outNeuro->getOut()*(1-outNeuro->getOut());

            for (int i = 0 ; i< outNeuro->getWeights()->count(); i++)
            {
                auto newWeight = (*outNeuro->getWeights())[i] - hiddenLayer.getNeuros()[i]->getOut()*weightDelta*learningRate;
                (*outNeuro->getWeights())[i] = newWeight;
            }

            for (auto j = 0; j < hiddenLayer.getNeuros().count(); j++)
            {
                auto n = hiddenLayer.getNeuros()[j];
                float error2 = (*outNeuro->getWeights())[j] * weightDelta;
                auto neuroOut = hiddenLayer.getNeuros()[j]->getOut();
                auto weightDelta1 = error2*neuroOut*(1-neuroOut);
                for (int i = 0 ; i< n->getWeights()->count(); i++)
                {
                    auto newWeight = (*n->getWeights())[i] - inputLayer.getNeuros()[i]->getOut()*weightDelta1*learningRate;
                    (*n->getWeights())[i] = newWeight;
                }
            }*/
        }

        // if (error < 0.5)
        qDebug() << error;
    }

    qDebug() << "end";

}
