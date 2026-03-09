#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "moorefsm.h"
#include <QMainWindow>
#include "QMessageBox"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_makeStepPushButton_clicked();

    void on_loadModelPushButton_clicked();

    void on_clearModelPushButton_clicked();

private:
    Ui::MainWindow *ui;
    MooreFSM* fsm;

    // Список строк, которые можно менять
    QList<int> rowsToClear = {0, 2, 3, 4, 5, 6};

    void lockStaticCells();
    void addStepToTraceTable(QString currentX);
};
#endif // MAINWINDOW_H
