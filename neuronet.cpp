#include "neuronet.h"

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
        float sumError = 0;
        for (auto d : data)
        {

            auto res = d[7];

            d.remove(7);

            auto neuroRes = forward(d);

            float error = neuroRes - res;
            sumError += fabs(error);

            float weightDelta = error*neuroRes*(1-neuroRes);

            auto outNeuro = outLayer.getNeuros().first();

            for (int i = 0 ; i< outNeuro->getWeights()->count(); i++)
            {
                auto newWeight = (*outNeuro->getWeights())[i] - hiddenLayer.getNeuros()[i]->getOut()*weightDelta*learningRate;
                (*outNeuro->getWeights())[i] = newWeight;
            }

            for (auto j = 0; j < hiddenLayer.getNeuros().count(); j++)
            {
                auto n = hiddenLayer.getNeuros()[j];
                error = (*outNeuro->getWeights())[j] * weightDelta;
                auto neuroOut = hiddenLayer.getNeuros()[j]->getOut();
                auto weightDelta1 = error*neuroOut*(1-neuroOut);
                for (int i = 0 ; i< n->getWeights()->count(); i++)
                {
                    auto newWeight = (*n->getWeights())[i] - inputLayer.getNeuros()[i]->getOut()*weightDelta1*learningRate;
                    (*n->getWeights())[i] = newWeight;
                }
            }
        }

        error = sumError;
    }

    int a = 0;

}
