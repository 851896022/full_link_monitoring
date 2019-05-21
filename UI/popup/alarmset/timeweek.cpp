#include "timeweek.h"
#include "ui_timeweek.h"

TimeWeek::TimeWeek(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeWeek)
{
    ui->setupUi(this);
    for(int i=0;i<7;i++)
    {
        timeDay[i]=new TimeDay;
    }

    ui->vBox_1->addWidget(timeDay[0]);
    ui->vBox_2->addWidget(timeDay[1]);
    ui->vBox_3->addWidget(timeDay[2]);
    ui->vBox_4->addWidget(timeDay[3]);
    ui->vBox_5->addWidget(timeDay[4]);
    ui->vBox_6->addWidget(timeDay[5]);
    ui->vBox_7->addWidget(timeDay[6]);

}

TimeWeek::~TimeWeek()
{
    delete ui;
}

void TimeWeek::on_oneKey_clicked()
{
    for(int i=1;i<7;i++)
    {
        for(int j=0;j<5;j++)
        {
            timeDay[i]->setTime(j,
                    timeDay[0]->timeLine[j]->getStartTime(),
                    timeDay[0]->timeLine[j]->getEndTime());
        }
    }
}
