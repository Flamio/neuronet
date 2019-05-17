#include <QCoreApplication>
#include "neuronet.h"
#include <iostream>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Neuronet n(&a);

    QVector<QVector<float>> v;

    QFile file("learning.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        return 1;
    }

    while (!file.atEnd()) {
        QVector<float> floats;
        QByteArray line = file.readLine();
        auto strings = line.split(';');
        for (auto s : strings)
        {
            floats.append(s.trimmed().toFloat());
        }

        v.append(floats);
    }

    v.remove(0);

    n.learn(v);

    QString f ("2;2000;3;1;0;2;0");

    auto fs = f.split(";");

     QVector<float> g2;

     for (auto fss : fs)
         g2.append(fss.toFloat());

    auto res = n.forward(g2);

    qDebug() << res;

   return a.exec();
}
