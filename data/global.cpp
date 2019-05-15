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
    isInitOk=false;

}
void Global::initThis()
{
    qDebug()<<"global init start";
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
    if(iniFile.contains("global/alarmGate"))
    {
        int gate=iniFile.value("global/alarmGate").toInt();
        if(gate < 1) gate=1;
        if(gate > 100) gate=100;
        if(gate > 0 && gate <=100)
        {
            alarmGate = gate;
        }

    }
    if(iniFile.contains("global/alarmDelay"))
    {
        int delay=iniFile.value("global/alarmDelay").toInt();
        if(delay < 1) delay=1;
        if(delay >1000) delay=1000;
        if(delay > 0 && delay <=1000)
        {
            alarmDelay = delay;
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
//=============================================================
    for(int i=0;i<36;i++)
    {
        reAudioDataThread[i]=new QThread;
    }

    emit initOK();
    isInitOk=true;
    qDebug()<<"global init ok";
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
    player->tempBuffer.clear();
    if(receivePCM->state()==QAbstractSocket::BoundState)
    {
        receivePCM->close();
    }
    receivePCM->bind((50000+(ch*10)));
}
void Global::stopPlay()
{
    player->tempBuffer.clear();
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


    short *chs;

    chs=(short*)(&ch);
    for(int i=0;i<1152;i++)
    {
        chs[i]=chs[i]*listenGain;
    }

    player->tempBuffer.append(ch,len);


}

