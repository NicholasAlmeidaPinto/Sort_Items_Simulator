#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerId = startTimer(1);

    ui->plot->addGraph();
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->yAxis->setRange(0, 10);

    criar_vetores();
    plot(vetor_y);

    QVector<QString> options = metodos->getOptions();
    for (int i = 0; i < options.size(); i++)
        ui->comboBox->addItem(options[i]);

    ui->spinBox->setSingleStep(50);
    ui->spinBox->setMaximum(100000);
    ui->spinBox->setValue(NPOINTS);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::criar_vetores(){
    vetor_x.resize(NPOINTS);
    vetor_y.resize(NPOINTS);
    for (int i = 0; i < NPOINTS; i++){
        vetor_x[i] = i;
        vetor_y[i] = QRandomGenerator::global()->generateDouble()*10;
    }
    metodos = new CMetodos(vetor_y);
}

void MainWindow::plot(QVector<double> _vector_y){
    ui->plot->xAxis->setRange(0, NPOINTS);
    ui->plot->graph(0)->setData(vetor_x, _vector_y);
    ui->plot->replot();
    ui->plot->update();
}


void MainWindow::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    if (running){
        if (!metodos->isSorted()){
            vetor_y = metodos->run();
            count++;
            if (count == 1){
                plot(vetor_y);
                count = 0;
                std::cout<<"Foram rodadas " << metodos->getCount() << " loops" << std::endl;
            }
        }
    }
}

void MainWindow::print_vector(){
    for(int i = 0; i < NPOINTS; i++)
        std::cout<<vetor_y[i] << " ";
    std::cout<<std::endl;
    ok = false;
}

void MainWindow::on_button_New_clicked()
{
    NPOINTS = ui->spinBox->value();
    running = false;
    criar_vetores();
    plot(vetor_y);
}


void MainWindow::on_button_Run_clicked()
{
    QString opt = ui->comboBox->currentText();
    metodos->setOption(opt);
    running = running? false:true;
}


void MainWindow::on_pushButton_clicked()
{
    print_vector();
}

