#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>
#include <QtSql>
#include <QPixmap>


signup::signup(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signup),
    loginWindow(nullptr)
{

    ui->setupUi(this);

    QPixmap sign(":/pictures/sign.png");
    int w=ui->label_4->width();
    int h=ui->label_4->height();
    ui->label_4->setPixmap(sign.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    //QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("C:/sqlite/db.sqlite");
    /*if(!db.open ())
        ui->label_4->setText ("Failed to open the database");
    else
        ui->label_4->setText("Connected .... ");*/
}

signup::~signup()
{
    delete ui;
    if (loginWindow) {
        delete loginWindow;
    }
}

void signup::on_signup_2_clicked()
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

    // Prepare the query to check for duplicates
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM user WHERE phonenumber = :phonenumber");
    checkQuery.bindValue(":phonenumber", Phonenumber);

    // Execute the query
    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to check for duplicates.");
        qDebug() << "Error checking for duplicates: " << checkQuery.lastError();
        return;
    }

    // Check the result
    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Duplicate", "The phone number already exists.");
        return;
    }
    else{
        // Prepare the insertion query
        QSqlQuery insertQuery;
        QSqlQuery insertQuery1;
        insertQuery1.prepare("INSERT INTO rider (phonenumber, pin) VALUES (:phonenumber1, :pin1)");
        insertQuery1.bindValue(":phonenumber1", Phonenumber);
        insertQuery1.bindValue(":pin1", Pin);
        insertQuery.prepare("INSERT INTO user (phonenumber, pin) VALUES (:phonenumber, :pin)");
        insertQuery.bindValue(":phonenumber", Phonenumber);
        insertQuery.bindValue(":pin", Pin);
        insertQuery1.exec();
        // Execute the insertion query
        if (!insertQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to insert data into the database.");
            qDebug() << "Error inserting data: " << insertQuery.lastError();
        } else {
            QMessageBox::information(this, "Success", "Account created sucessfully.");
            QMessageBox::information(this, "Sign-in success", " Redirecting to login...");

            // Show the login window
            if (!loginWindow) {
                loginWindow = new login(this);
            }
            loginWindow->show();
           this->hide(); // Hide the sign-in window
        }
    }
}

