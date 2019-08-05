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

    ui->source_1->initThis(No);

    ui->radio_1->initThis(No);

    movie.setFileName(":/img/img/bar.gif");

    ui->line_1->setMovie(&movie);
    ui->line_2->setMovie(&movie);
    movie.start();
}
LinkModel::~LinkModel()
{
    delete ui;
}
