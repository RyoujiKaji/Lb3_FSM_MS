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

    lockStaticCells();
}

void MainWindow::lockStaticCells() {
    // Запрещаем менять состояния
    for (int col = 0; col < ui->modelTableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->modelTableWidget->item(1, col);
        if (item) {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    }
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
    addStepToTraceTable(QString("x%1").arg(x + 1));
}

void MainWindow::addStepToTraceTable(QString currentX){
    auto ind = ui->traceTableWidget->rowCount();
    ui->traceTableWidget->insertRow(ind);
    // Создаем элементы для каждой колонки
    for (int col = 0; col < ui->traceTableWidget->columnCount(); ++col) {
        ui->traceTableWidget->setItem(ind, col, new QTableWidgetItem());
    }

    ui->traceTableWidget->item(ind, 0)->setText(QString::number(ind));
    ui->traceTableWidget->item(ind, 1)->setText(currentX);
    ui->traceTableWidget->item(ind, 2)->setText(QString("z%1").arg(fsm->getCurrentState() + 1));
    ui->traceTableWidget->item(ind, 3)->setText(QString("y%1").arg(fsm->getCurrentOutput() + 1));
}

void MainWindow::on_loadModelPushButton_clicked()
{
    std::vector<int> newOuts(4);
    std::vector<std::vector<int>> newTrans(5, std::vector<int>(4));

    try {
        //Считываем выходы
        for (int z = 0; z < 4; ++z) {
            QString val = ui->modelTableWidget->item(0, z)->text();
            // Убираем 'y', если пользователь его ввел (напр. "y1" -> "1")
            newOuts[z] = val.remove('y').toInt() - 1;
        }

        //Считываем переходы
        for (int x = 0; x < 5; ++x) {
            for (int z = 0; z < 4; ++z) {
                QString val = ui->modelTableWidget->item(x + 2, z)->text();
                newTrans[x][z] = val.remove('z').toInt() - 1;
            }
        }

        int startState = ui->startStateComboBox->currentIndex();

        //Обновляем модель
        delete fsm;
        fsm = new MooreFSM(newTrans, newOuts, startState);

        //Обновляем историю переходов
        ui->traceTableWidget->setRowCount(0);
        addStepToTraceTable("-");

        QMessageBox::information(this, "Успех", "Модель автомата загружена!");

    } catch (...) {
        QMessageBox::warning(this, "Ошибка", "Проверьте корректность введенных данных (только цифры или форматы z1, y1)");
    }
}


void MainWindow::on_clearModelPushButton_clicked()
{
    for (int row : rowsToClear) {
        for (int col = 0; col < ui->modelTableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = ui->modelTableWidget->item(row, col);
            if (item) {
                item->setText(""); // Очищаем текст
            }
        }
    }
}

