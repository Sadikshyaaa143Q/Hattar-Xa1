#include "riderhome.h"
#include "ui_riderhome.h"

riderhome::riderhome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::riderhome)
{
    ui->setupUi(this);
}

riderhome::~riderhome()
{
    delete ui;
}
