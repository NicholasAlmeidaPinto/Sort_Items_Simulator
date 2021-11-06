#include "CMetodos.h"

CMetodos::CMetodos(QVector<double> _vetor)
{
    vetor = _vetor;
    SIZE  = _vetor.size();
    bRadixSort.resize(SIZE);
    options.resize(9);
    options[0] = "metodo0";
    options[1] = "metodo1";
    options[2] = "metodo2";
    options[3] = "BubbleSort";
    options[4] = "BubbleSort_invert";
    options[5] = "doubleBubbleSort";
    options[6] = "RadixSort";
    options[7] = "QuickSort";
    options[8] = "metodo8";
}

bool CMetodos::isSorted(){
    for (int i = 0; i < SIZE-1; i++){
        if (vetor[i+1] < vetor[i])
            return false;
    }
    return true;
}

void CMetodos::setOption(QString opt){
    for(int i = 0; i < options.size(); i++){
        if (options[i] == opt){
            choose = i;
            break;
        }
    }
}

QVector<double> CMetodos::run(){
    if(choose == 0)
        return metodo0();
    else if(choose == 1)
        return metodo1();
    else if(choose == 2)
        return metodo2();
    else if(choose == 3)
        return BubbleSort();
    else if(choose == 4)
        return BubbleSort_invert();
    else if(choose == 5)
        return doubleBubbleSort();
    else if(choose == 6)
        return RadixSort();
    else if(choose == 7)
        return QuickSort();
    else if(choose == 8)
        return metodo8();
}

QVector<double> CMetodos::metodo0(){
    double min_value;
    int x;
    for (int pos_analisada = lastUpdatePoint; pos_analisada<SIZE; pos_analisada++){
      min_value = vetor[pos_analisada];
      for (int i = 1; i < SIZE-pos_analisada; i++){
        count ++;
        x = i + pos_analisada;
        if (min_value > vetor[x]){
          min_value = vetor[x];
          vetor[x] = vetor[pos_analisada];
          vetor[pos_analisada] = min_value;
          return vetor;
        }
      }
    }
    return vetor;
}

QVector<double> CMetodos::metodo1(){
    double min_value;
    int x, min_pos;
    for (int pos_analisada = lastUpdatePoint; pos_analisada<SIZE; pos_analisada++){
      min_value = vetor[pos_analisada];
      for (int i = 0; i < SIZE-pos_analisada; i++){
        count ++;
        x = i + pos_analisada;
        if (min_value > vetor[x]){
            min_value = vetor[x];
            min_pos = x;
        }
      }
      if (min_value < vetor[pos_analisada]){
          vetor[min_pos] = vetor[pos_analisada];
          vetor[pos_analisada] = min_value;
          return vetor;
      }
    }
    return vetor;
}

QVector<double> CMetodos::metodo2(){
    double temp;
    for (int i = 0; i < SIZE-1; i++){
        count ++;
        if (vetor[i+1] < vetor[i]){
            temp = vetor[i];
            vetor[i] = vetor[i+1];
            vetor[i+1] = temp;
            return vetor;
        }
    }
    return vetor;
}


QVector<double> CMetodos::BubbleSort(){
    double temp;
    for (int i = 0; i < SIZE-1; i++){
        count ++;
        if (vetor[i+1] < vetor[i]){
            temp = vetor[i];
            vetor[i] = vetor[i+1];
            vetor[i+1] = temp;
        }
    }
    return vetor;
}

QVector<double> CMetodos::BubbleSort_invert(){
    double temp;
    for (int i = SIZE-1; i > 0; i--){
        count ++;
        if (vetor[i-1] > vetor[i]){
            temp = vetor[i];
            vetor[i] = vetor[i-1];
            vetor[i-1] = temp;
        }
    }
    return vetor;
}

QVector<double> CMetodos::doubleBubbleSort(){
    double temp;
    for (int i = 0; i < SIZE-1; i++){
        count ++;
        if (vetor[i+1] < vetor[i]){
            temp = vetor[i];
            vetor[i] = vetor[i+1];
            vetor[i+1] = temp;
        }
        if (vetor[SIZE-i-1] < vetor[SIZE-i-2]){
            temp = vetor[SIZE-i-1];
            vetor[SIZE-i-1] = vetor[SIZE-i-2];
            vetor[SIZE-i-2] = temp;
        }

    }
    return vetor;
}

QVector<double> CMetodos::RadixSort(){
    for (int i = 0; i < SIZE; i++)
        vetor[i] *=1000000;

    int NDIVISIONS = 10;
    double maior = max();
    while((int)maior/expRadixSort > 0){
        std::cout<<"hello 0" << std::endl;
        for (int i = 0; i < SIZE; i++){
            count++;
            bucketRadixSort[(int)(vetor[i] / expRadixSort) % NDIVISIONS]++;
        }
        std::cout<<"hello 1" << std::endl;
        for (int i = 1; i < NDIVISIONS; i++){
            count++;
            bucketRadixSort[i] += bucketRadixSort[i - 1];

        }
        std::cout<<"hello 2" << std::endl;
        for (int i = SIZE - 1; i >= 0; i--){
            count++;
            bRadixSort[bucketRadixSort[(int)(vetor[i] / expRadixSort) % NDIVISIONS]-1] = vetor[i];
            bucketRadixSort[(int)(vetor[i] / expRadixSort) % NDIVISIONS]--;
        }
        std::cout<<"hello 3" << std::endl;
        for (int i = 0; i < SIZE; i++){
            count++;
            vetor[i] = bRadixSort[i];
        }
        expRadixSort *= NDIVISIONS;

        for (int i = 0; i < SIZE; i++)
            vetor[i] /=1000000;
        return vetor;
    }
    for (int i = 0; i < SIZE; i++)
        vetor[i] /=1000000;
    return vetor;
}

double CMetodos::max(){
    double maior = vetor[0];
    for(int i = 1; i < SIZE; i++)
        if (vetor[i] > maior)
            maior = vetor[i];
    return maior;
}

QVector<double> CMetodos::QuickSort(){
    quicksort(0,SIZE);
    return vetor;
}

void CMetodos::quicksort(int began, int end)
{
    double aux, pivo;
    iQS = began;
    jQS = end-1;
    pivo = vetor[(began + end) / 2];
    while(iQS <= jQS)
    {
        while(vetor[iQS] < pivo && iQS < end)
        {
            count++;
            iQS++;
        }
        while(vetor[jQS] > pivo && jQS > began)
        {
            count++;
            jQS--;
        }
        if(iQS <= jQS)
        {
            aux = vetor[iQS];
            vetor[iQS] = vetor[jQS];
            vetor[jQS] = aux;
            iQS++;
            jQS--;
        }
    }
    if(jQS > began)
        quicksort( began, jQS+1);
    if(iQS < end)
        quicksort( iQS, end);
}

QVector<double> CMetodos::metodo8(){
    return vetor;
}
