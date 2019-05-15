#include "globalset.h"
#include "ui_globalset.h"

GlobalSet::GlobalSet(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GlobalSet)
{
    ui->setupUi(this);
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

    ui->txt_delay->setText(QString::number(g->alarmDelay));
    ui->txt_gate->setText(QString::number(g->alarmGate));


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
    iniFile.setValue("global/alarmGate",ui->txt_gate->text());
    iniFile.setValue("global/alarmDelay",ui->txt_delay->text());
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
