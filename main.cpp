#include <QCoreApplication>
#include "neuronet.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QVector<float> g;

    g.push_back(1);
    g.push_back(2);
    g.push_back(3);
    g.push_back(4);
    g.push_back(5);
    g.push_back(6);
    g.push_back(7);

    Neuronet n(&a);

    n.forward(g);


    return a.exec();
}
