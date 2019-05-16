#include "neuro.h"
#include <QDateTime>

Neuro::Neuro(int ins,QObject *parent) : QObject(parent)
{
    for (int i = 0; i<ins;i++)
    {
        auto r = Random::get(1,10);
        weights.push_back(1.0f/r);
    }
}

float Neuro::forward(QVector<float> &inputs)
{
    float sum = 0;
    for (int i = 0; i < inputs.size(); i++)
    {
        sum += inputs[i] * weights[i];
    }

    out = sum / (1 + fabs(sum));
    return out;
}

QVector<float>* Neuro::getWeights()
{
    return &weights;
}

float Neuro::getOut() const
{
    return out;
}
