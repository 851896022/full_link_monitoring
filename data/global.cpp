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
    sqlite = new SQLite;
    sqlite->initThis(QString(),"DataBase.db",QString(),QString());
    sqlite->takeLog(/*日志内容*/"程序启动",
                     /*表*/"user_log",
                     /*类型*/"log",
                     /*用户名*/"admin"
                     );//用户日志模板
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
    for(int i=0;i<8;i++)
    {
        if(iniFile.contains("link/"+QString::number(i)+"isUsing"))
        {
            linkIsUsing[i]=iniFile.value("link/"+QString::number(i)+"isUsing").toBool();

        }

    }
    {
        QString asd;
        for(int i=0;i<8;i++)
        {
            if(linkIsUsing[i])
            {
                asd.append("t ");
            }
            else
            {
                asd.append("f ");
            }

        }
        qDebug()<<asd;
    }

    //链路表示方法
    {
        for(int linkNo=0;linkNo<8;linkNo++)
        {
            QSettings iniFile(QCoreApplication::applicationDirPath()+
                              "/setAlarmLink"+QString::number(linkNo)+".ini", QSettings::IniFormat);
            iniFile.setIniCodec("UTF-8");

            linkALarmGateTime[linkNo].linkGate.sourceGate_1=iniFile.value("gate/sourceGate_1").toInt();
            linkALarmGateTime[linkNo].linkGate.sourceGate_2=iniFile.value("gate/sourceGate_2").toInt();
            linkALarmGateTime[linkNo].linkGate.radioGate=iniFile.value("gate/radioGate").toInt();
            linkALarmGateTime[linkNo].linkGate.sourceDelay_1=iniFile.value("delay/sourceDelay_1").toInt();
            linkALarmGateTime[linkNo].linkGate.sourceDelay_2=iniFile.value("delay/sourceDelay_2").toInt();
            linkALarmGateTime[linkNo].linkGate.radioDelay=iniFile.value("delay/radioDelay").toInt();

            for(int day=0;day<7;day++)
            {
                for(int i=0;i<5;i++)
                {

                    linkALarmGateTime[linkNo].linkTime.day[day].line[i].startTime=
                            iniFile.value("day"+QString::number(day)+"/startTime"+QString::number(i)).toTime();
                    linkALarmGateTime[linkNo].linkTime.day[day].line[i].endTime=
                            iniFile.value("day"+QString::number(day)+"/endTime"+QString::number(i)).toTime();

                }

            }
        }



    }
    //通道表示方法
    chAlarmGateTime[0].alarmDelay=linkALarmGateTime[0].linkGate.sourceDelay_1;
    chAlarmGateTime[0].alarmGate=linkALarmGateTime[0].linkGate.sourceGate_1;
    chAlarmGateTime[0].timeList=&linkALarmGateTime[0].linkTime;
    chAlarmGateTime[0].isUsing=linkIsUsing[0];//待添加
    chAlarmGateTime[1].alarmDelay=linkALarmGateTime[0].linkGate.sourceDelay_2;
    chAlarmGateTime[1].alarmGate=linkALarmGateTime[0].linkGate.sourceGate_2;
    chAlarmGateTime[1].timeList=&linkALarmGateTime[0].linkTime;
    chAlarmGateTime[1].isUsing=linkIsUsing[0];//待添加
    chAlarmGateTime[2].alarmDelay=linkALarmGateTime[0].linkGate.radioDelay;
    chAlarmGateTime[2].alarmGate=linkALarmGateTime[0].linkGate.radioGate;
    chAlarmGateTime[2].timeList=&linkALarmGateTime[0].linkTime;
    chAlarmGateTime[2].isUsing=linkIsUsing[0];//待添加

    chAlarmGateTime[3].alarmDelay=linkALarmGateTime[1].linkGate.sourceDelay_1;
    chAlarmGateTime[3].alarmGate=linkALarmGateTime[1].linkGate.sourceGate_1;
    chAlarmGateTime[3].timeList=&linkALarmGateTime[1].linkTime;
    chAlarmGateTime[3].isUsing=linkIsUsing[1];//待添加
    chAlarmGateTime[4].alarmDelay=linkALarmGateTime[1].linkGate.sourceDelay_2;
    chAlarmGateTime[4].alarmGate=linkALarmGateTime[1].linkGate.sourceGate_2;
    chAlarmGateTime[4].timeList=&linkALarmGateTime[1].linkTime;
    chAlarmGateTime[4].isUsing=linkIsUsing[1];//待添加
    chAlarmGateTime[5].alarmDelay=linkALarmGateTime[1].linkGate.radioDelay;
    chAlarmGateTime[5].alarmGate=linkALarmGateTime[1].linkGate.radioGate;
    chAlarmGateTime[5].timeList=&linkALarmGateTime[1].linkTime;
    chAlarmGateTime[5].isUsing=linkIsUsing[1];//待添加

    chAlarmGateTime[6].alarmDelay=linkALarmGateTime[2].linkGate.sourceDelay_1;
    chAlarmGateTime[6].alarmGate=linkALarmGateTime[2].linkGate.sourceGate_1;
    chAlarmGateTime[6].timeList=&linkALarmGateTime[2].linkTime;
    chAlarmGateTime[6].isUsing=linkIsUsing[2];//待添加
    chAlarmGateTime[7].alarmDelay=linkALarmGateTime[2].linkGate.sourceDelay_2;
    chAlarmGateTime[7].alarmGate=linkALarmGateTime[2].linkGate.sourceGate_2;
    chAlarmGateTime[7].timeList=&linkALarmGateTime[2].linkTime;
    chAlarmGateTime[7].isUsing=linkIsUsing[2];//待添加
    chAlarmGateTime[8].alarmDelay=linkALarmGateTime[2].linkGate.radioDelay;
    chAlarmGateTime[8].alarmGate=linkALarmGateTime[2].linkGate.radioGate;
    chAlarmGateTime[8].timeList=&linkALarmGateTime[2].linkTime;
    chAlarmGateTime[8].isUsing=linkIsUsing[2];//待添加

    chAlarmGateTime[9].alarmDelay=linkALarmGateTime[3].linkGate.sourceDelay_1;
    chAlarmGateTime[9].alarmGate=linkALarmGateTime[3].linkGate.sourceGate_1;
    chAlarmGateTime[9].timeList=&linkALarmGateTime[3].linkTime;
    chAlarmGateTime[9].isUsing=linkIsUsing[3];//待添加
    chAlarmGateTime[10].alarmDelay=linkALarmGateTime[3].linkGate.sourceDelay_2;
    chAlarmGateTime[10].alarmGate=linkALarmGateTime[3].linkGate.sourceGate_2;
    chAlarmGateTime[10].timeList=&linkALarmGateTime[3].linkTime;
    chAlarmGateTime[10].isUsing=linkIsUsing[3];//待添加
    chAlarmGateTime[11].alarmDelay=linkALarmGateTime[3].linkGate.radioDelay;
    chAlarmGateTime[11].alarmGate=linkALarmGateTime[3].linkGate.radioGate;
    chAlarmGateTime[11].timeList=&linkALarmGateTime[3].linkTime;
    chAlarmGateTime[11].isUsing=linkIsUsing[3];//待添加

    chAlarmGateTime[12].alarmDelay=linkALarmGateTime[4].linkGate.sourceDelay_1;
    chAlarmGateTime[12].alarmGate=linkALarmGateTime[4].linkGate.sourceGate_1;
    chAlarmGateTime[12].timeList=&linkALarmGateTime[4].linkTime;
    chAlarmGateTime[12].isUsing=linkIsUsing[4];//待添加
    chAlarmGateTime[13].alarmDelay=linkALarmGateTime[4].linkGate.sourceDelay_2;
    chAlarmGateTime[13].alarmGate=linkALarmGateTime[4].linkGate.sourceGate_2;
    chAlarmGateTime[13].timeList=&linkALarmGateTime[4].linkTime;
    chAlarmGateTime[13].isUsing=linkIsUsing[4];//待添加
    chAlarmGateTime[14].alarmDelay=linkALarmGateTime[4].linkGate.radioDelay;
    chAlarmGateTime[14].alarmGate=linkALarmGateTime[4].linkGate.radioGate;
    chAlarmGateTime[14].timeList=&linkALarmGateTime[4].linkTime;
    chAlarmGateTime[14].isUsing=linkIsUsing[4];//待添加

    chAlarmGateTime[15].alarmDelay=linkALarmGateTime[5].linkGate.sourceDelay_1;
    chAlarmGateTime[15].alarmGate=linkALarmGateTime[5].linkGate.sourceGate_1;
    chAlarmGateTime[15].timeList=&linkALarmGateTime[5].linkTime;
    chAlarmGateTime[15].isUsing=linkIsUsing[5];//待添加
    chAlarmGateTime[18].alarmDelay=linkALarmGateTime[5].linkGate.sourceDelay_2;
    chAlarmGateTime[18].alarmGate=linkALarmGateTime[5].linkGate.sourceGate_2;
    chAlarmGateTime[18].timeList=&linkALarmGateTime[5].linkTime;
    chAlarmGateTime[18].isUsing=linkIsUsing[5];//待添加
    chAlarmGateTime[19].alarmDelay=linkALarmGateTime[5].linkGate.radioDelay;
    chAlarmGateTime[19].alarmGate=linkALarmGateTime[5].linkGate.radioGate;
    chAlarmGateTime[19].timeList=&linkALarmGateTime[5].linkTime;
    chAlarmGateTime[19].isUsing=linkIsUsing[5];//待添加

    chAlarmGateTime[20].alarmDelay=linkALarmGateTime[6].linkGate.sourceDelay_1;
    chAlarmGateTime[20].alarmGate=linkALarmGateTime[6].linkGate.sourceGate_1;
    chAlarmGateTime[20].timeList=&linkALarmGateTime[6].linkTime;
    chAlarmGateTime[20].isUsing=linkIsUsing[6];//待添加
    chAlarmGateTime[21].alarmDelay=linkALarmGateTime[6].linkGate.sourceDelay_2;
    chAlarmGateTime[21].alarmGate=linkALarmGateTime[6].linkGate.sourceGate_2;
    chAlarmGateTime[21].timeList=&linkALarmGateTime[6].linkTime;
    chAlarmGateTime[21].isUsing=linkIsUsing[6];//待添加
    chAlarmGateTime[22].alarmDelay=linkALarmGateTime[6].linkGate.radioDelay;
    chAlarmGateTime[22].alarmGate=linkALarmGateTime[6].linkGate.radioGate;
    chAlarmGateTime[22].timeList=&linkALarmGateTime[6].linkTime;
    chAlarmGateTime[22].isUsing=linkIsUsing[6];//待添加

    chAlarmGateTime[23].alarmDelay=linkALarmGateTime[7].linkGate.sourceDelay_1;
    chAlarmGateTime[23].alarmGate=linkALarmGateTime[7].linkGate.sourceGate_1;
    chAlarmGateTime[23].timeList=&linkALarmGateTime[7].linkTime;
    chAlarmGateTime[23].isUsing=linkIsUsing[7];//待添加
    chAlarmGateTime[24].alarmDelay=linkALarmGateTime[7].linkGate.sourceDelay_2;
    chAlarmGateTime[24].alarmGate=linkALarmGateTime[7].linkGate.sourceGate_2;
    chAlarmGateTime[24].timeList=&linkALarmGateTime[7].linkTime;
    chAlarmGateTime[24].isUsing=linkIsUsing[7];//待添加
    chAlarmGateTime[25].alarmDelay=linkALarmGateTime[7].linkGate.radioDelay;
    chAlarmGateTime[25].alarmGate=linkALarmGateTime[7].linkGate.radioGate;
    chAlarmGateTime[25].timeList=&linkALarmGateTime[7].linkTime;
    chAlarmGateTime[25].isUsing=linkIsUsing[7];//待添加

    {
        QString asd;
        for(int i=0;i<26;i++)
        {
            if(i==17||i==16)
            {
                continue;
            }
            if(chAlarmGateTime[i].isUsing)
            {
                asd.append("t ");
            }
            else
            {
                asd.append("f ");
            }

        }
        qDebug()<<asd;
    }




//    if(iniFile.contains("global/alarmGate"))
//    {
//        int gate=iniFile.value("global/alarmGate").toInt();
//        if(gate < 1) gate=1;
//        if(gate > 100) gate=100;
//        if(gate > 0 && gate <=100)
//        {
//            alarmGate = gate;
//        }

//    }
//    if(iniFile.contains("global/alarmDelay"))
//    {
//        int delay=iniFile.value("global/alarmDelay").toInt();
//        if(delay < 1) delay=1;
//        if(delay >1000) delay=1000;
//        if(delay > 0 && delay <=1000)
//        {
//            alarmDelay = delay;
//        }

//    }


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

    {
        QString str;
        for(int i=0;i<35;i++)
        {
            str.append(QString::number(g->ac32Apm[i]));
            str.append("  ");

        }
        qDebug()<<str;
    }

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
QString Global::getChName(int ch)
{
    if(ch<0||ch>25)
    {
        return "未知";
    }
    if(ch>15)
    {
        ch-=2;
    }
    int link=ch/3;
    int d=ch%3;
    if(d==0)
    {
        return g->receiverName[link]+"主";
    }
    else if(d==1)
    {
        return g->receiverName[link]+"备";
    }
    else if(d==2)
    {
        return g->radioName[link];
    }
    return "未知";
}

