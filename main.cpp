#include <QCoreApplication>
#include "neuronet.h"
#include <iostream>

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
    g.push_back(0.9);


    QVector<float> g1;

    g1.push_back(7);
    g1.push_back(6);
    g1.push_back(5);
    g1.push_back(4);
    g1.push_back(3);
    g1.push_back(2);
    g1.push_back(1);
    g1.push_back(0.2);

    Neuronet n(&a);

    QVector<QVector<float>> f;
    f.push_back(g);
    f.push_back(g1);
    n.learn(f);


   /* QVector<float> v;
    for (int i = 0; i <7; i++)
    {
        int a;
        std::cin >> a;
        v.push_back(a);
    }*/

    std::cout << n.forward(g1);
    std::cout.flush();

    return a.exec();
}
