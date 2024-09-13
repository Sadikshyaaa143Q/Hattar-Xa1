#include "login.h"
#include "ui_login.h"
#include "destination.h"
#include "signup.h"
#include "viewrequests.h"
#include<QPixmap>


login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
    ,destinationWindow(nullptr),viewrequestWindow(nullptr),signupWindow(nullptr)// Initialize the destination window pointer
{
    ui->setupUi(this);
    QWidget widget;
    widget.setWindowFlags(Qt::FramelessWindowHint);

    QPixmap logopic(":/pictures/potrait.png");
    int w=ui->logo->width();
    int h=ui->logo->height();
    ui->logo->setPixmap(logopic.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

login::~login()
{
    delete ui;
    if (destinationWindow) {
        delete destinationWindow;
    }
}



void login::on_loginuser_clicked()
{
    QString Phonenumber, Pin;
    Phonenumber = ui->lineEdit_Phonenumber->text();
    Pin = ui->lineEdit_Pin->text();
    if (true){


        // Ensure the database is open
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/sqlite/db.sqlite");
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
        else{
            // Prepare the query to check for a matching record
            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM user WHERE phonenumber = :phonenumber AND pin = :pin");
            query.bindValue(":phonenumber", Phonenumber);
            query.bindValue(":pin", Pin);

            // Execute the query
            if (!query.exec()) {
                QMessageBox::critical(this, "Error", "Failed to execute query.");
                qDebug() << "Error executing query: " << query.lastError();
                return;
            }

            // Check the result
            else if (query.next() && query.value(0).toInt() > 0) {
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE user SET status = 'on hold' WHERE phonenumber = :phonenumber AND pin = :pin");
                updateQuery.bindValue(":phonenumber", Phonenumber);
                updateQuery.bindValue(":pin", Pin);

                // Execute the update query
                if (!updateQuery.exec()) {
                    QMessageBox::critical(this, "Error", "Failed to update status.");
                    qDebug() << "Error updating status: " << updateQuery.lastError();
                    return;
                }
                if (!destinationWindow) {
                    destinationWindow = new destination(this);
                }
                destinationWindow->setCurrentPhoneNumber(Phonenumber); // Pass the phone number
                destinationWindow->show();
                //this->hide(); // Optional: Hide the login window
            }
        else
            {
              QMessageBox::warning(this, "Failure", "Invalid phone number or pin.");
            }
            }}}

void login::on_signup_clicked()
{
    if (!signupWindow) {
        signupWindow= new signup(signupWindow);
    }
    signupWindow->show();
    //this->hide();
}


void login::on_loginrider_clicked()
{
    QString Phonenumber, Pin;
    Phonenumber = ui->lineEdit_Phonenumber->text();
    Pin = ui->lineEdit_Pin->text();

    // Ensure the database is open
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Failed to connect to the database.");
            return;
        }
    }

    // Prepare the query to check for a matching record
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM rider WHERE phonenumber = :phonenumber AND pin = :pin");
    query.bindValue(":phonenumber", Phonenumber);
    query.bindValue(":pin", Pin);

    // Execute the query
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to execute query.");
        qDebug() << "Error executing query: " << query.lastError();
        return;
    }

    // Check the result
    if (query.next() && query.value(0).toInt() > 0) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE user SET status = 'unknown' WHERE phonenumber = :phonenumber AND pin = :pin");
        updateQuery.bindValue(":phonenumber", Phonenumber);
        updateQuery.bindValue(":pin", Pin);

        // Execute the update query
        if (!updateQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update status.");
            qDebug() << "Error updating status: " << updateQuery.lastError();
            return;
        }
        if (!viewrequestWindow){
            viewrequestWindow = new viewRequests(viewrequestWindow);
        }
        viewrequestWindow-> show();
    } else {
        QMessageBox::warning(this, "Failure", "Invalid phone number or pin.");
    }
}


