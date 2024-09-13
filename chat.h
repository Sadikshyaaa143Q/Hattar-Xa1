#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    void loadMessages();
    ~Chat();

private slots:
    void on_enter_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::Chat *ui;
    QSqlDatabase db;
};

#endif // CHAT_H
