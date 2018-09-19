#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Data retrieve part
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
    // Test of het goede map is

    QSqlQuery MySQLqeury;
    MySQLqeury.exec("SELECT * FROM data\
                     WHERE id = (SELECT MAX(id) FROM data);");

    while(MySQLqeury.next()){
        tempValue = MySQLqeury.value("temp").toString();
        humiValue = MySQLqeury.value("humi").toString();
        lightValue = MySQLqeury.value("light").toString();
    }

    // Visual part
    //tempValue = "Temp Value";
    //lightValue = "Light Value";
    //dddhumiValue = "Humi Value";

    ui->setupUi(this);

    ui->tempValueBox->setText(tempValue);
    ui->lightValueBox->setText(lightValue);
    ui->humiValueBox->setText(humiValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}
