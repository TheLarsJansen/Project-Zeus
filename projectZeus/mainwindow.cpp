#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Data retrieve part
    // Database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("databases.aii.avans.nl");
    db.setPort(3306);
    db.setUserName("ljphjans");
    db.setPassword("Ab12345");
    db.setDatabaseName("ljphjans_db");

    if(db.open()){
        qDebug() << "Database connected";
    } else{
        QSqlError err = db.lastError();
        qDebug() << err.databaseText();
        qDebug() << err.driverText();
        qDebug() << err.text();
        qDebug() << "Database connection failed";
    }

    QSqlQuery MySQLqeury;
    MySQLqeury.exec("SELECT * FROM data\
                     WHERE id = (SELECT MAX(id) FROM data);");

    // Request currentWeather tab values
    while(MySQLqeury.next()){
        tempValue = MySQLqeury.value("temp").toString();
        humiValue = MySQLqeury.value("humi").toString();
        lightValue = MySQLqeury.value("light").toString();
        timeValue = MySQLqeury.value("date").toString();
    }

    // Visual part


    //Set currentWeather tab Values
    ui->tempValueBox->setText(tempValue + " C");
    ui->lightValueBox->setText(lightValue + " Lumen");
    ui->humiValueBox->setText(humiValue + " %");

    timeValue.chop(13);
    ui->timeValueBox->setText(timeValue);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_refreshButton_pressed()
{
    QSqlQuery MySQLqeury;
    MySQLqeury.exec("SELECT * FROM data\
                     WHERE id = (SELECT MAX(id) FROM data);");

    // Request currentWeather tab values
    while(MySQLqeury.next()){
        tempValue = MySQLqeury.value("temp").toString();
        humiValue = MySQLqeury.value("humi").toString();
        lightValue = MySQLqeury.value("light").toString();
        timeValue = MySQLqeury.value("date").toString();
    }

    // Visual part


    //Set currentWeather tab Values
    ui->tempValueBox->setText(tempValue);
    ui->lightValueBox->setText(lightValue);
    ui->humiValueBox->setText(humiValue);

    timeValue.chop(13);
    ui->timeValueBox->setText(timeValue);
}
