#include "sourcemodel.h"
#include "ui_sourcemodel.h"

SourceModel::SourceModel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SourceModel)
{
    ui->setupUi(this);
}

SourceModel::~SourceModel()
{
    delete ui;
}
