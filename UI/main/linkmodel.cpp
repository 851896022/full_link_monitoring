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

    movie.setFileName(":/img/img/bar.gif");

    ui->line_1->setMovie(&movie);
    ui->line_2->setMovie(&movie);
    ui->line_3->setMovie(&movie);
    ui->line_4->setMovie(&movie);

    ui->line_5->setMovie(&movie);
    ui->line_6->setMovie(&movie);
    ui->line_7->setMovie(&movie);
    ui->line_8->setMovie(&movie);
    movie.start();
}
LinkModel::~LinkModel()
{
    delete ui;
}
