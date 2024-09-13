#ifndef RIDERHOME_H
#define RIDERHOME_H

#include <QMainWindow>

namespace Ui {
class riderhome;
}

class riderhome : public QWidget
{
    Q_OBJECT

public:
    explicit riderhome(QWidget *parent = nullptr);
    ~riderhome();

private:
    Ui::riderhome *ui;
};

#endif // RIDERHOME_H
