#ifndef CHATUSER_H
#define CHATUSER_H

#include <QWidget>
#include <QtSql>
namespace Ui {
class ChatUser;
}

class ChatUser : public QWidget
{
    Q_OBJECT

public:
    explicit ChatUser(QWidget *parent = nullptr);
    void loadMessages();
    ~ChatUser();

private slots:
    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChatUser *ui;
     QSqlDatabase db;
};

#endif // CHATUSER_H
