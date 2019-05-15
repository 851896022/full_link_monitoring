#include "tittle.h"
#include "ui_tittle.h"

Tittle::Tittle(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Tittle)
{
    ui->setupUi(this);
    ui->name->setText(g->stationName);
    globalSet=new GlobalSet;
}

Tittle::~Tittle()
{
    delete ui;
}
#include <QFont>
void Tittle::resizeEvent(QResizeEvent *event)
{

    event->accept();
    this->setMaximumHeight(this->parentWidget()->geometry().height()*0.065);

    this->ui->gridLayout->setContentsMargins(10,this->geometry().height()*0.15,10,0);
    QFont tmp= ui->name->font();
    tmp.setPointSizeF(this->geometry().height()*0.3);
    ui->name->setFont(tmp);
}

void Tittle::on_btn_set_clicked()
{
    globalSet->deleteLater();
    globalSet= new GlobalSet;
    globalSet->setWindowFlags(globalSet->windowFlags()  |   Qt::WindowStaysOnTopHint);
    globalSet->show();
    globalSet->raise();
    globalSet->activateWindow();
}
