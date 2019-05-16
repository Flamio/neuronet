#ifndef NEUROLAYER_H
#define NEUROLAYER_H

#include <QObject>
#include "neuro.h"

class NeuroLayer : public QObject
{
    Q_OBJECT
public:
    explicit NeuroLayer(int count, int neuroInsCount,QObject *parent = 0);

    QVector<float>& forward(QVector<float>& ins);

    QVector<Neuro *> getNeuros();

signals:

public slots:

private:
    QVector<Neuro*> neuros;
    QVector<float> out;

    int neuroInsCount = 0;
};

#endif // NEUROLAYER_H
