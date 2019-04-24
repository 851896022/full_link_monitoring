#include "linkmodel.h"
#include "ui_linkmodel.h"

LinkModel::LinkModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LinkModel)
{
    ui->setupUi(this);
}

LinkModel::~LinkModel()
{
    delete ui;
}
