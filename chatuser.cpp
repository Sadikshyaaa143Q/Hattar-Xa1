#include "chatuser.h"
#include "ui_chatuser.h"
#include <QMessageBox>
#include <QPixmap>

ChatUser::ChatUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatUser)
{
    ui->setupUi(this);
    ui->pushButton_3->setIcon(QIcon(":/icons/send.png"));
    ui->pushButton_4->setIcon(QIcon(":/icons/change.png"));


    QPixmap label_2(":/icons/message.png");
    int w1=ui->label_2->width();
    int h1=ui->label_2->height();
    ui->label_2->setPixmap(label_2.scaled(w1,h1,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open the database.");
    }
}

ChatUser::~ChatUser()
{
    delete ui;
}

void ChatUser::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT message FROM messagesRider ORDER BY timestamp DESC LIMIT 1");
    //query.bindValue(":phonenumber", currentPhoneNumber);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to load messages.");
        qDebug() << "Error loading messages: " << query.lastError();
        return;
    }

    while (query.next()) {
        QString message = query.value(0).toString();
        ui->textEdit->setText(message);// text edit widget gives this option so to display message use this
    }
}


void ChatUser::on_pushButton_3_clicked()
{
    QString message = ui->lineEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Message cannot be empty.");
        return;
    }

    // Save the message to the database
    QSqlQuery query;
    query.prepare("INSERT INTO messages ( message) VALUES ( :message)");
    //query.bindValue(":phonenumber", currentPhoneNumber);
    query.bindValue(":message", message);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to send the message.");
        qDebug() << "Error sending message: " << query.lastError();
        return;
    }
    QString message1=ui->lineEdit->text();
    ui->textEdit_2->setText(message1);
    ui->lineEdit->clear();
}



void ChatUser::on_pushButton_4_clicked()
{
    loadMessages();
}


void ChatUser::on_pushButton_clicked()
{
    this->close();  // Closes the current window
}

