#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QDebug>

#include <QtSql>

#include <QtCharts>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_refreshButton_pressed();

private:
    Ui::MainWindow *ui;

    QTabWidget *tabWidget;

    QString humiValue;
    QString tempValue;
    QString lightValue;
    QString timeValue;
};

#endif // MAINWINDOW_H
