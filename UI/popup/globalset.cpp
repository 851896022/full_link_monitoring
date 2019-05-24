#include "globalset.h"
#include "ui_globalset.h"

GlobalSet::GlobalSet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GlobalSet)
{
    ui->setupUi(this);


    ui->vBox_alarm->addWidget(&timeLink);




    ui->txt_name_1->setText(g->stationName);

    ui->txt_name_2->setText(g->receiverName[0]);
    ui->txt_name_3->setText(g->radioName[0]);
    ui->txt_name_4->setText(g->receiverName[1]);
    ui->txt_name_5->setText(g->radioName[1]);
    ui->txt_name_6->setText(g->receiverName[2]);
    ui->txt_name_7->setText(g->radioName[2]);
    ui->txt_name_8->setText(g->receiverName[3]);
    ui->txt_name_9->setText(g->radioName[3]);
    ui->txt_name_10->setText(g->receiverName[4]);
    ui->txt_name_11->setText(g->radioName[4]);
    ui->txt_name_12->setText(g->receiverName[5]);
    ui->txt_name_13->setText(g->radioName[5]);
    ui->txt_name_14->setText(g->receiverName[6]);
    ui->txt_name_15->setText(g->radioName[6]);
    ui->txt_name_16->setText(g->receiverName[7]);
    ui->txt_name_17->setText(g->radioName[7]);

    ui->checkBox_1->setChecked(g->linkIsUsing[0]);
    ui->checkBox_2->setChecked(g->linkIsUsing[1]);
    ui->checkBox_3->setChecked(g->linkIsUsing[2]);
    ui->checkBox_4->setChecked(g->linkIsUsing[3]);
    ui->checkBox_5->setChecked(g->linkIsUsing[4]);
    ui->checkBox_6->setChecked(g->linkIsUsing[5]);
    ui->checkBox_7->setChecked(g->linkIsUsing[6]);
    ui->checkBox_8->setChecked(g->linkIsUsing[7]);

//    ui->txt_delay->setText(QString::number(g->alarmDelay));
//    ui->txt_gate->setText(QString::number(g->alarmGate));
    {
        for(int linkNo=0;linkNo<8;linkNo++)
        {
            timeLink.gateLink[linkNo]->setSourceGate_1(g->linkALarmGateTime[linkNo].linkGate.sourceGate_1);
            timeLink.gateLink[linkNo]->setSourceGate_2(g->linkALarmGateTime[linkNo].linkGate.sourceGate_2);
            timeLink.gateLink[linkNo]->setRadioGate(g->linkALarmGateTime[linkNo].linkGate.radioGate);

            timeLink.gateLink[linkNo]->setSourceDelay_1(g->linkALarmGateTime[linkNo].linkGate.sourceDelay_1);
            timeLink.gateLink[linkNo]->setSourceDelay_2(g->linkALarmGateTime[linkNo].linkGate.sourceDelay_2);
            timeLink.gateLink[linkNo]->setRadioDelay(g->linkALarmGateTime[linkNo].linkGate.radioDelay);
            for(int day=0;day<7;day++)
            {
                for(int i=0;i<5;i++)
                {
                    timeLink.timeWeek[linkNo]->timeDay[day]->timeLine[i]->setTime(
                                g->linkALarmGateTime[linkNo].linkTime.day[day].line[i].startTime,
                                g->linkALarmGateTime[linkNo].linkTime.day[day].line[i].endTime
                                );

                }

            }
        }



    }



    ui->comboBox_xjjc_count->setCurrentIndex(g->linkCount-1);
    //ip
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/equ.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {

            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                QStringList list=ba.split("|").at(0).split(":");
                if(list.count()==2)
                {
                    ui->ip_ac32_1->setIP(list.at(0));
                    ui->port_ac32_1->setText(list.at(1));
                }
            }
            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                QStringList list=ba.split("|").at(0).split(":");
                if(list.count()==2)
                {
                    ui->ip_ac32_2->setIP(list.at(0));
                    ui->port_ac32_2->setText(list.at(1));
                }
            }




            file->close();
        }
        file->deleteLater();
    }
    //save dir
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/savedir.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {

            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                ui->txt_saveDir->setText(ba);
            }




            file->close();
        }
        file->deleteLater();
    }
    //save day
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/saveday.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {

            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                ui->txt_saveDay->setText(ba);
            }
            file->close();
        }
        file->deleteLater();
    }
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/equ.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {

            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                QStringList list=ba.split("|").at(0).split(":");
                if(list.count()==2)
                {
                    ui->ip_ac32_1->setIP(list.at(0));
                    ui->port_ac32_1->setText(list.at(1));
                }
            }
            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                QStringList list=ba.split("|").at(0).split(":");
                if(list.count()==2)
                {
                    ui->ip_ac32_2->setIP(list.at(0));
                    ui->port_ac32_2->setText(list.at(1));
                }
            }




            file->close();
        }
        file->deleteLater();
    }

}

GlobalSet::~GlobalSet()
{
    delete ui;
}

void GlobalSet::on_btn_save_clicked()
{

    QSettings iniFile(QCoreApplication::applicationDirPath()+"/setSinkiang.ini", QSettings::IniFormat);
    iniFile.setIniCodec("UTF-8");
    iniFile.setValue("global/xjjc",ui->comboBox_xjjc_count->currentIndex()+1);
    iniFile.setValue("global/stationName",ui->txt_name_1->text());
    QStringList source;
    QStringList radio;
    source.append(ui->txt_name_2->text());
    radio.append(ui->txt_name_3->text());
    source.append(ui->txt_name_4->text());
    radio.append(ui->txt_name_5->text());
    source.append(ui->txt_name_6->text());
    radio.append(ui->txt_name_7->text());
    source.append(ui->txt_name_8->text());
    radio.append(ui->txt_name_9->text());
    source.append(ui->txt_name_10->text());
    radio.append(ui->txt_name_11->text());
    source.append(ui->txt_name_12->text());
    radio.append(ui->txt_name_13->text());
    source.append(ui->txt_name_14->text());
    radio.append(ui->txt_name_15->text());
    source.append(ui->txt_name_16->text());
    radio.append(ui->txt_name_17->text());
    iniFile.setValue("global/sourceName",source);
    iniFile.setValue("global/radioName",radio);

    iniFile.setValue("link/"+QString::number(0)+"isUsing",ui->checkBox_1->isChecked());
    iniFile.setValue("link/"+QString::number(1)+"isUsing",ui->checkBox_2->isChecked());
    iniFile.setValue("link/"+QString::number(2)+"isUsing",ui->checkBox_3->isChecked());
    iniFile.setValue("link/"+QString::number(3)+"isUsing",ui->checkBox_4->isChecked());
    iniFile.setValue("link/"+QString::number(4)+"isUsing",ui->checkBox_5->isChecked());
    iniFile.setValue("link/"+QString::number(5)+"isUsing",ui->checkBox_6->isChecked());
    iniFile.setValue("link/"+QString::number(6)+"isUsing",ui->checkBox_7->isChecked());
    iniFile.setValue("link/"+QString::number(7)+"isUsing",ui->checkBox_8->isChecked());


//    iniFile.setValue("global/alarmGate",ui->txt_gate->text());
//    iniFile.setValue("global/alarmDelay",ui->txt_delay->text());
    //时间段+门限//时间段+门限//时间段+门限//时间段+门限//时间段+门限//
    {
        for(int linkNo=0;linkNo<8;linkNo++)
        {
            QSettings iniFile(QCoreApplication::applicationDirPath()+
                              "/setAlarmLink"+QString::number(linkNo)+".ini", QSettings::IniFormat);
            iniFile.setIniCodec("UTF-8");
            iniFile.setValue("gate/sourceGate_1",timeLink.gateLink[linkNo]->sourceGate_1());
            iniFile.setValue("gate/sourceGate_2",timeLink.gateLink[linkNo]->sourceGate_2());
            iniFile.setValue("gate/radioGate",timeLink.gateLink[linkNo]->radioGate());
            iniFile.setValue("delay/sourceDelay_1",timeLink.gateLink[linkNo]->sourceDelay_1());
            iniFile.setValue("delay/sourceDelay_2",timeLink.gateLink[linkNo]->sourceDelay_2());
            iniFile.setValue("delay/radioDelay",timeLink.gateLink[linkNo]->radioDelay());

            for(int day=0;day<7;day++)
            {
                for(int i=0;i<5;i++)
                {
                    iniFile.setValue("day"+QString::number(day)+"/startTime"+QString::number(i),
                                     timeLink.timeWeek[linkNo]->timeDay[day]->timeLine[i]->getStartTime());
                    iniFile.setValue("day"+QString::number(day)+"/endTime"+QString::number(i),
                                     timeLink.timeWeek[linkNo]->timeDay[day]->timeLine[i]->getEndTime());

                }

            }
        }



    }


    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/equ.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::WriteOnly))
        {



            QString str;
            str=ui->ip_ac32_1->getIP()+":"+ui->port_ac32_1->text()+"|";
            str+=ui->txt_name_2->text()+"主|";
            str+=ui->txt_name_2->text()+"备|";
            str+=ui->txt_name_3->text()+"|";
            str+=ui->txt_name_4->text()+"主|";
            str+=ui->txt_name_4->text()+"备|";
            str+=ui->txt_name_5->text()+"|";
            str+=ui->txt_name_6->text()+"主|";
            str+=ui->txt_name_6->text()+"备|";
            str+=ui->txt_name_7->text()+"|";
            str+=ui->txt_name_8->text()+"主|";
            str+=ui->txt_name_8->text()+"备|";
            str+=ui->txt_name_9->text()+"|||||||";
            str+="\r\n";

            str+=ui->ip_ac32_2->getIP()+":"+ui->port_ac32_2->text()+"|";
            str+=ui->txt_name_10->text()+"主|";
            str+=ui->txt_name_10->text()+"备|";
            str+=ui->txt_name_11->text()+"|";
            str+=ui->txt_name_12->text()+"主|";
            str+=ui->txt_name_12->text()+"备|";
            str+=ui->txt_name_13->text()+"|";
            str+=ui->txt_name_14->text()+"主|";
            str+=ui->txt_name_14->text()+"备|";
            str+=ui->txt_name_15->text()+"|";
            str+=ui->txt_name_16->text()+"主|";
            str+=ui->txt_name_16->text()+"备|";
            str+=ui->txt_name_17->text()+"|||||||";

            file->write(str.toStdString().data());
            file->flush();
            file->close();
        }
        file->deleteLater();
    }
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/savedir.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::WriteOnly))
        {



            QString str;
            str=ui->txt_saveDir->text();

            file->write(str.toLatin1());
            file->flush();
            file->close();
        }
        file->deleteLater();
    }
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/saveday.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::WriteOnly))
        {



            QString str;
            str=ui->txt_saveDay->text();

            file->write(str.toStdString().data());
            file->flush();
            file->close();
        }
        file->deleteLater();
    }
    this->hide();
    g->sqlite->takeLog(/*日志内容*/"修改配置",
                     /*表*/"user_log",
                     /*类型*/"log",
                     /*用户名*/"admin"
                     );//用户日志模板


}
#include <QFileDialog>
void GlobalSet::on_btn_chose_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(
                this,
                tr("选择文件夹"),
                ui->txt_saveDir->text(),
                QFileDialog::ShowDirsOnly);
    if (!directory.isEmpty())
    {
        ui->txt_saveDir->setText(directory);
    }
}

void GlobalSet::on_btn_cacel_clicked()
{
    this->hide();
}
