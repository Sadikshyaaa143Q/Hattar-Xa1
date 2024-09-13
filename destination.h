#ifndef DESTINATION_H
#define DESTINATION_H
#include <QWidget>
#include <QtSql>
#include <QMainWindow>
#include<QtDebug>
#include<QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>
#include "chatuser.h"

namespace Ui {
class destination;
}
class chat;
class destination : public QMainWindow
{
    Q_OBJECT

public:
    explicit destination(QWidget *parent = nullptr);
    ~destination();
private slots:
    //void on_saveButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_status_clicked();

    void on_chat_clicked();

private:
    Ui::destination *ui;
    QSqlDatabase db;
    chat *chatWindow;
    QString currentPhoneNumber;  // Store the current user's phone number
    ChatUser *chatuserWindow;

public:
    void setCurrentPhoneNumber(const QString &phoneNumber);// Method to set the current user's phone number

    void checkUserStatus();

};

#endif // DESTINATION_H
