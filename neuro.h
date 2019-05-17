#ifndef NEURO_H
#define NEURO_H

#include <QObject>
#include <QVector>
#include "random.h"

class Neuro : public QObject
{
    Q_OBJECT
public:
    explicit Neuro(int ins, QObject *parent = 0);

    float forward(QVector<float>& inputs);

    QVector<float>* getWeights();
    float getOut() const;
signals:

public slots:

private:
    QVector<float> weights;

    float out = 0;
};

#endif // NEURO_H
