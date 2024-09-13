#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>
#include "destination.h"
#include "viewrequests.h"
#include "signup.h"


namespace Ui {
class login;
//class signup;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    //void setCurrentPhoneNumber(const QString &phoneNumber);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_loginrider_clicked();

    void on_loginuser_clicked();

    void on_signup_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;
    destination *destinationWindow;
    viewRequests *viewrequestWindow;
    class signup *signupWindow;    // Add a member for the destination window
     //QString currentPhoneNumber;

// public:
//     void updateUserStatus(const QString &status);
//     void updateRiderStatus(const QString &status);

};

#endif // LOGIN_H
