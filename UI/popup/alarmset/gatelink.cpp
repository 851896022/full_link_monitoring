#include "gatelink.h"
#include "ui_gatelink.h"

GateLink::GateLink(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GateLink)
{
    ui->setupUi(this);
}

GateLink::~GateLink()
{
    delete ui;
}
int GateLink::sourceGate_1()
{
    return ui->sourceGate_1->text().toInt();
}
int GateLink::sourceGate_2()
{
    return ui->sourceGate_2->text().toInt();
}
int GateLink::radioGate()
{
    return ui->radioGate_1->text().toInt();
}
int GateLink::sourceDelay_1()
{
    return ui->sourceDelay_1->text().toInt();
}
int GateLink::sourceDelay_2()
{
    return  ui->sourceDelay_2->text().toInt();
}
int GateLink::radioDelay()
{
    return ui->radioDelay_1->text().toInt();
}
void GateLink::setSourceGate_1(int num)
{
    ui->sourceGate_1->setText(QString::number(num));
}
void GateLink::setSourceGate_2(int num)
{
    ui->sourceGate_2->setText(QString::number(num));
}
void GateLink::setRadioGate(int num)
{
    ui->radioGate_1->setText(QString::number(num));
}
void GateLink::setSourceDelay_1(int num)
{
    ui->sourceDelay_1->setText(QString::number(num));
}
void GateLink::setSourceDelay_2(int num)
{
    ui->sourceDelay_2->setText(QString::number(num));
}
void GateLink::setRadioDelay(int num)
{
    ui->radioDelay_1->setText(QString::number(num));
}
