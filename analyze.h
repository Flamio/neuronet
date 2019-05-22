#ifndef NEURONET_H
#define NEURONET_H

#include <QObject>
#include "MultilayerPerceptron.h"

class Analyze : public QObject
{
    Q_OBJECT

public:
    explicit Analyze(QObject *parent = 0);
    virtual ~Analyze();
    void train(float error, const QString& filename);
    void loadWeights();
    void saveWeights();

    float calcResult(std::vector<float>&);

signals:


public slots:

private:
    MultilayerPerceptron* mlp = nullptr;
};

#endif // NEURONET_H
