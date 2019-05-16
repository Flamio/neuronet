#ifndef NEURONET_H
#define NEURONET_H

#include <QObject>
#include "neurolayer.h"

class Neuronet : public QObject
{
    Q_OBJECT
public:
    explicit Neuronet(QObject *parent = 0);

    float forward(QVector<float>& ins);

    void learn(QVector<QVector<float>>& data);

signals:

public slots:

private:
    const float learningRate = 0.3;

    NeuroLayer inputLayer;
    NeuroLayer hiddenLayer;
    NeuroLayer outLayer;
};

#endif // NEURONET_H
