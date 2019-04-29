#include "radiomodel.h"
#include "ui_radiomodel.h"

RadioModel::RadioModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RadioModel)
{
    ui->setupUi(this);
}

RadioModel::~RadioModel()
{
    delete ui;
}
void RadioModel::initThis(int No)
{
    this->No=No;
    ui->name->setText(g->radioName[No]);
}
