#include "destination.h"
#include "ui_destination.h"
#include "chatuser.h"

destination::destination(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::destination),
    chatuserWindow(nullptr)
{
    ui->setupUi(this);
    this->showMaximized();
    QPixmap show(":/map/map_2.png");
    int w=ui->map->width();
    int h=ui->map->height();
    ui->map->setPixmap(show.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QPixmap home(":/icons/home.png");
    int w1=ui->home->width();
    int h1=ui->home->height();
    ui->home->setPixmap(home.scaled(w1,h1,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QPixmap bulb(":/icons/bulb.png");
    int w2=ui->bulb->width();
    int h2=ui->bulb->height();
    ui->bulb->setPixmap(bulb.scaled(w2,h2,Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

destination::~destination()
{
    delete ui;
}
void destination::setCurrentPhoneNumber(const QString &phoneNumber) {
    currentPhoneNumber = phoneNumber;
}

void destination::checkUserStatus() {
    // Ensure the database is open
    if (!db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/sqlite/db.sqlite");
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
    }

    // Prepare the query to check the user's status
    QSqlQuery query;
    query.prepare("SELECT status FROM user WHERE phonenumber = :phonenumber");
    query.bindValue(":phonenumber", currentPhoneNumber);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to query the database.");
        qDebug() << "Error executing query: " << query.lastError();
        return;
    }

    // Check the status
    if (query.next()) {
        QString status = query.value(0).toString();
        if (status == " Accepted ") {
             QMessageBox::information(this, "Ride Status", "Hey, Your ride has been accepted.");
        }
    }else {
         QMessageBox::critical(this, "Error", "User not found.");
    }
}

void destination::on_pushButton_clicked()
{
    QString fromLocation = ui->comboBox->currentText();
    QString toLocation = ui->comboBox_2->currentText();

    // Ensure the database is open
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
    }
    // Prepare the query to update the user's record
    QSqlQuery query;
    query.prepare("UPDATE user SET location_from = :fromLocation, location_to = :toLocation, status = 'on hold' WHERE phonenumber = :phonenumber");
    query.bindValue(":fromLocation", fromLocation);
    query.bindValue(":toLocation", toLocation);
    query.bindValue(":phonenumber", currentPhoneNumber);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update the database.");
        qDebug() << "Error executing query: " << query.lastError();
        return;
    }
    else if(fromLocation==toLocation)
    {
       QMessageBox::information(this, "Invalid locations.", "Please select two different locations.");
    }
    else
    QMessageBox::information(this, "Requests sent.", "Please wait while we search for riders..");
}

void destination::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}

void destination::on_status_clicked()
{
      checkUserStatus();
}


void destination::on_chat_clicked()
{
    if (!chatuserWindow) {
        chatuserWindow= new ChatUser(chatuserWindow);
    }
    chatuserWindow->show();
}

