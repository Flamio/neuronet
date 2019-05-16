#include "neurolayer.h"

NeuroLayer::NeuroLayer(int count, int neuroInsCount, QObject *parent) : QObject(parent)
{
    this->neuroInsCount = neuroInsCount;
    for (int i = 0; i < count; i++)
    {
       auto n = new Neuro(neuroInsCount, this);
       neuros.push_back(n);
    }
}

QVector<float> &NeuroLayer::forward(QVector<float> &ins)
{
    out.clear();

    for (Neuro* n : neuros)
    {
        float value;
        if (neuroInsCount != 1)
            value = n->forward(ins);
        else
        {
            static int i = 0;
            QVector<float> v;
            v.push_back(ins[i]);
            value = n->forward(v);
            i++;
        }
        out.push_back(value);
    }

    return out;
}

QVector<Neuro *> NeuroLayer::getNeuros()
{
    return neuros;
}
