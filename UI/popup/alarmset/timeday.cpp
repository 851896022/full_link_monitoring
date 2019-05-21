#include "timeday.h"
#include "ui_timeday.h"

TimeDay::TimeDay(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeDay)
{
    ui->setupUi(this);
    for(int i=0;i<5;i++)
    {
        timeLine[i]=new TimeLine;
        ui->vBox->addWidget(timeLine[i]);
    }

}

TimeDay::~TimeDay()
{
    delete ui;
}
void TimeDay::setTime(int line,QTime startTime,QTime endTime)
{
    timeLine[line]->setTime(startTime,endTime);
}
