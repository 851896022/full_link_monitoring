#include "tittle.h"
#include "ui_tittle.h"

Tittle::Tittle(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Tittle)
{
    ui->setupUi(this);
}

Tittle::~Tittle()
{
    delete ui;
}
