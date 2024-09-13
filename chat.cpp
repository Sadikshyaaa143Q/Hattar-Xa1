#include "chat.h"
#include "ui_chat.h"
#include <QPixmap>

Chat::Chat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chat)
{
    ui->setupUi(this);
    ui->pushButton_3->setIcon(QIcon(":/icons/send.png"));
    ui->pushButton_4->setIcon(QIcon(":/icons/change.png"));

    QPixmap label(":/icons/message.png");
    int w1=ui->label->width();
    int h1=ui->label->height();
    ui->label->setPixmap(label.scaled(w1,h1,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open the database.");
    }
}

Chat::~Chat()
{
    delete ui;
}

void Chat::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT message FROM messages ORDER BY timestamp DESC LIMIT 1");
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

void Chat::on_pushButton_3_clicked()
{
        QString message = ui->lineEdit->text();
        if (message.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Message cannot be empty.");
            return;
        }

        // Save the message to the database
        QSqlQuery query;
        query.prepare("INSERT INTO messagesRider(message) VALUES ( :message)");
        query.bindValue(":message", message);
        query.exec();

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to send the message.");
            qDebug() << "Error sending message: " << query.lastError();
            return;
        }
        QString message1=ui->lineEdit->text();
        ui->textEdit_2->setText(message1);
        ui->lineEdit->clear();
    }


void Chat::on_pushButton_4_clicked()
{
    loadMessages();
}


void Chat::on_pushButton_clicked()
{
    this->close();  // Closes the current window
}

