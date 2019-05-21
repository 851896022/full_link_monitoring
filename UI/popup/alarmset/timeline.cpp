#include "timeline.h"
#include "ui_timeline.h"

TimeLine::TimeLine(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeLine)
{
    ui->setupUi(this);
}

TimeLine::~TimeLine()
{
    delete ui;
}
void TimeLine::setTime(QTime startTime,QTime endTime)
{
    ui->startTime->setTime(startTime);
    ui->endTime->setTime(endTime);
}
QTime TimeLine::getStartTime()
{
    return ui->startTime->time();
}
QTime TimeLine::getEndTime()
{
    return ui->endTime->time();
}
