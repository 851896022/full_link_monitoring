#include "forcemodel.h"
#include "ui_forcemodel.h"

ForceModel::ForceModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ForceModel)
{
    ui->setupUi(this);
}

ForceModel::~ForceModel()
{
    delete ui;
}
