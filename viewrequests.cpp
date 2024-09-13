#include "viewrequests.h"
#include "ui_viewrequests.h"
#include <QPixmap>
#include "chat.h"

viewRequests::viewRequests(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::viewRequests),
    chatWindow(nullptr)
{
    ui->setupUi(this);
    this->showMaximized();

    QPixmap home(":/icons/home.png");
    int w1=ui->home->width();
    int h1=ui->home->height();
    ui->home->setPixmap(home.scaled(w1,h1,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QPixmap label(":/pictures/rider.png");
    int w=ui->label->width();
    int h=ui->label->height();
    ui->label->setPixmap(label.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QPixmap bulb(":/icons/bulb.png");
    int w2=ui->bulb->width();
    int h2=ui->bulb->height();
    ui->bulb->setPixmap(bulb.scaled(w2,h2,Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

viewRequests::~viewRequests()
{
    delete ui;
}

void viewRequests::on_pushButton_clicked()
{
    QSqlQueryModel *modal= new QSqlQueryModel();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    db.open();
    QSqlQuery query = QSqlQuery(db);
    query.prepare ("SELECT USERID, PHONENUMBER, location_from, location_to, status FROM user WHERE status = 'on hold';");
    query.exec();
    modal->setQuery(std::move(query));
    ui->tableView->setModel(modal);
    db.close();
}

void viewRequests::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/db.sqlite");
    db.open();
    QSqlQuery query = QSqlQuery(db);
    query.prepare("UPDATE user SET status = ' Accepted ' WHERE USERID = " + val + ";");
    query.exec();
    if (!query.exec()){
        QMessageBox::warning(this, "Failure", "Please select from UserID.");
    }
    else{
         QMessageBox::information(this, "Ride Booked!", "We have informed the user of the booking.");
    }
    db.close();
}


void viewRequests::on_chat_clicked()
{
    if (!chatWindow) {
        chatWindow= new Chat(chatWindow);
    }
    chatWindow->show();
}

