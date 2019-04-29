#include "sourcemodel.h"
#include "ui_sourcemodel.h"
#include <QDebug>
SourceModel::SourceModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SourceModel)
{
    ui->setupUi(this);
}

void SourceModel::initThis(int No)
{
    this->No=No;
    ui->name->setText(g->receiverName[No]);
}
SourceModel::~SourceModel()
{
    delete ui;
}
