#include "timelink.h"
#include "ui_timelink.h"

TimeLink::TimeLink(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TimeLink)
{
    ui->setupUi(this);
    for(int i=0;i<8;i++)
    {
        gateLink[i]=new GateLink;
        timeWeek[i]=new TimeWeek;
    }
    ui->vBox_1->addWidget(gateLink[0]);
    ui->vBox_1->addWidget(timeWeek[0]);

    ui->vBox_2->addWidget(gateLink[1]);
    ui->vBox_2->addWidget(timeWeek[1]);

    ui->vBox_3->addWidget(gateLink[2]);
    ui->vBox_3->addWidget(timeWeek[2]);

    ui->vBox_4->addWidget(gateLink[3]);
    ui->vBox_4->addWidget(timeWeek[3]);

    ui->vBox_5->addWidget(gateLink[4]);
    ui->vBox_5->addWidget(timeWeek[4]);

    ui->vBox_6->addWidget(gateLink[5]);
    ui->vBox_6->addWidget(timeWeek[5]);

    ui->vBox_7->addWidget(gateLink[6]);
    ui->vBox_7->addWidget(timeWeek[6]);

    ui->vBox_8->addWidget(gateLink[7]);
    ui->vBox_8->addWidget(timeWeek[7]);
}

TimeLink::~TimeLink()
{
    delete ui;
}
