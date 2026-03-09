#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fsm = new MooreFSM;

    ui->modelTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->traceTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete fsm;
    delete ui;
}

void MainWindow::on_makeStepPushButton_clicked()
{
    auto x = ui->inSignalComboBox->currentIndex();

    fsm->makeStep(ui->inSignalComboBox->currentIndex());

    auto ind = ui->traceTableWidget->rowCount();
    ui->traceTableWidget->insertRow(ui->traceTableWidget->rowCount());
    // Создаем элементы для каждой колонки
    for (int col = 0; col < ui->traceTableWidget->columnCount(); ++col) {
        ui->traceTableWidget->setItem(ind, col, new QTableWidgetItem());
    }

    ui->traceTableWidget->item(ind, 0)->setText(QString::number(ind));
    ui->traceTableWidget->item(ind, 1)->setText(QString("x%1").arg(x + 1));
    ui->traceTableWidget->item(ind, 2)->setText(QString("z%1").arg(fsm->getCurrentState() + 1));
    ui->traceTableWidget->item(ind, 3)->setText(QString("y%1").arg(fsm->getCurrentOutput() + 1));
}


