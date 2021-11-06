#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <vector>
#include "CMetodos.h"
#include <iostream>
#include <QTimerEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void plot(QVector<double> _vector_y);

private slots:
    //void on_pushButton_clicked();
    void timerEvent(QTimerEvent *e);

    void criar_vetores();

    void on_button_Run_clicked();

    void on_button_New_clicked();
    void print_vector();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    int timerId;
    bool running = false;
    int NPOINTS = 2000;
    int count = 0;
    bool ok=true;
    CMetodos *metodos;
    QVector<double> vetor_x;
    QVector<double> vetor_y;

};
#endif // MAINWINDOW_H
