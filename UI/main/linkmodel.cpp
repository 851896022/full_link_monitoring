#include "linkmodel.h"
#include "ui_linkmodel.h"

LinkModel::LinkModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LinkModel)
{
    ui->setupUi(this);


}
void LinkModel::initThis(int No)
{
    this->No=No;

    ui->source_1->initThis(No*4+0);
    ui->source_2->initThis(No*4+1);
    ui->source_3->initThis(No*4+2);
    ui->source_4->initThis(No*4+3);

    ui->radio_1->initThis(No*4+0);
    ui->radio_2->initThis(No*4+1);
    ui->radio_3->initThis(No*4+2);
    ui->radio_4->initThis(No*4+3);
}
LinkModel::~LinkModel()
{
    delete ui;
}
