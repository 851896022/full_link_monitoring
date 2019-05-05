#include "global.h"
Global *g;
Global::Global(QObject *parent) : QObject(parent)
{
    //=====全局参数初始化=====
    linkCount=2;
    stationName="新疆广电厅中波台";
    for(int i=0;i<8;i++)
    {
        receiverName[i]="888KHz卫星接收机";
        radioName[i]="888KHz开环接收";
    }
    textMoveSpeed=10;
    for(int i=0;i<16;i++)
    {
        textMoveText[i]="节目源";
    }


}
void Global::initThis()
{
    QSettings iniFile(QCoreApplication::applicationDirPath()+"/setSinkiang.ini", QSettings::IniFormat);
    iniFile.setIniCodec("UTF-8");
    if(iniFile.contains("global/xjjc"))
    {
        linkCount=iniFile.value("global/xjjc").toInt();
    }
    if(iniFile.contains("global/stationName"))
    {
        stationName=iniFile.value("global/stationName").toString();
    }
    if(iniFile.contains("global/sourceName"))
    {
        QStringList receiverNameList=iniFile.value("global/sourceName").toStringList();

        for(int i=0;i<receiverNameList.count();i++)
        {
            receiverName[i]=receiverNameList.at(i);
        }
    }
    if(iniFile.contains("global/radioName"))
    {
        QStringList radioNameList=iniFile.value("global/radioName").toStringList();
        for(int i=0;i<radioNameList.count();i++)
        {
            radioName[i]=radioNameList.at(i);
        }
    }

    //============================================================
    {
        QString base_dir=qApp->applicationDirPath()+"/sav";
        QDir *temp = new QDir;
        bool exist = temp->exists(base_dir);
        if(!exist)
        {
            temp->mkdir(base_dir);
        }
    }
    loadEqu();
//========================================================
    receivePCM=new QUdpSocket;
    connect(receivePCM,SIGNAL(readyRead()),this,SLOT(onReceivePCM()));
    player=new Player;



}
void Global::loadEqu()
{
    //================================================================
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/equ.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {
            for(int i=0;i<10;i++)
            {
                {
                    QString ba(file->readLine());
                    QStringList list=ba.split("|");
                    equ[i].name=list.at(0);
                    equ[i].ip=equ[i].name.split(":").at(0);
                    equ[i].port=equ[i].name.split(":").at(1).toInt();
                    for(int j=0;j<18;j++)
                    {
                        equ[i].chName[j]=list.at(j+1);
                    }
                }


                if(file->atEnd())break;
            }
            file->close();
        }
        file->deleteLater();
    }

    //--------------------------
    int equCount=10;
    for(int i=0;i<10;i++)
    {
        if(equ[i].port==0)
        {
            equCount=i;
            break;
        }
    }
    this->equCount=equCount;
}
void Global::changePlayCh(int ch)
{
    if(receivePCM->state()==QAbstractSocket::BoundState)
    {
        receivePCM->close();
    }
    receivePCM->bind((50000+(ch*10)));
}
void Global::stopPlay()
{
    receivePCM->close();
}
void Global::onReceivePCM()
{


    char ch[23040]={0};

    int len=receivePCM->readDatagram(ch,23040);


    if(len>2304)
    {
        qDebug()<<"this time receive len is"<<len;
    }
    if(len<2304)return;
    player->tempBuffer.append(ch,len);


}
