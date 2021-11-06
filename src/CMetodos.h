#ifndef CMETODOS_H
#define CMETODOS_H

#include <QVector>
#include <iostream>


class CMetodos
{
public:
    CMetodos(QVector<double> _vetor);

    bool isSorted();
    QVector<double> run();
    QVector<QString> getOptions(){return options;}
    void setOption(QString);
    int getCount(){return count;}
private:

    QVector<double> metodo0();
    QVector<double> metodo1();
    QVector<double> metodo2();
    QVector<double> BubbleSort();
    QVector<double> BubbleSort_invert();
    QVector<double> doubleBubbleSort();
    QVector<double> RadixSort();
    QVector<double> QuickSort();
    void quicksort(int began, int end);
    QVector<double> metodo8();

    double max();
private:
    int count=0;
    int choose = 0;
    int lastUpdatePoint = 0;
    int SIZE;
    QVector<double> vetor;
    QVector<QString> options;

    /// RadixSort variables
    double expRadixSort = 1;
    double bucketRadixSort[10] = { 0 };
    std::vector<double> bRadixSort;

    /// QuickSort variables
    int pivotQS, rightQS;
    int iQS, jQS;
};

#endif // CMETODOS_H
