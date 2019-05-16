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
