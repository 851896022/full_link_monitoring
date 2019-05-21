#include "reaudiodata.h"

ReAudioData::ReAudioData(QObject *parent) : QObject(parent)
{

}
void ReAudioData::initThis()
{
    //this->No=No;
    socket=new QUdpSocket;
    int port=50000+(No*10)+2;
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    socket->bind(port);

    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer->start(100);
}
void ReAudioData::initThis(int No)
{
    this->No=No;
    socket=new QUdpSocket;
    int port=50000+(No*10)+2;
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    socket->bind(port);
}
void ReAudioData::onReadyRead()
{

    char ch[65536]={0};
    int realsize=0;

    while(socket->bytesAvailable())
    {
        realsize=socket->readDatagram((char*)ch, 65536);
        /*
        if(realsize==2304)
        {
            g->audioCache[No].append((char*)ch,2304);
            int len=g->audioCache[No].count();
            if(len>g->cacheSize)
            {
                //qDebug()<<"delete"<<(len-131072);
                g->audioCache[No].remove(0,(len-(g->cacheSize )));
            }

        }
        */
        int MAX=0;
        short* ch16=(short*)ch;
        for(int i=0;i<(2304/2);i++)
        {
            if(MAX<ch16[i])
            {
                MAX=ch16[i];
            }
        }
        g->maxValue[No]=MAX;
        if(MAX<150) MAX=1;
        double ret=((1.42*20.0*log10(MAX)-30.0)-30.0)*1.50;
        MAX=int(ret);
        if(MAX<0)  MAX=0;
        if(MAX>99) MAX=99+(rand()%2);
        g->ac32Apm[No]=MAX;

        //=============
        if(sendCount>15)
        {
            sendCount=0;
            emit apmOk(No);
        }
        sendCount++;




    }
    //qDebug()<<g->audioCache[No].count();

}
void ReAudioData::onTimerOut()
{

    if(g->ac32Apm[No]>=g->alarmGate)
    {
        if(alarmCount>=(g->alarmDelay*10))
        {
            emit alarmCancel(No);
        }
        alarmCount=0;
    }
    else
    {
        alarmCount++;
    }

    if(alarmCount==(g->alarmDelay*10))
    {
        emit sendAlarm(No);
        int tmp=No+1;
        if(tmp>16)
        {
            tmp-2;
        }
        g->sqlite->takeLog(/*日志内容*/g->getChName(No)+QString("音频幅度过低"),
                         /*表*/"alarm_log",
                         /*类型*/"alarm",
                         /*用户名*/QString::number(tmp)
                         );//用户日志模板
    }

    if(alarmCount>(g->alarmDelay*10))
    {
        alarmCount=(g->alarmDelay*10)+1;
    }

}
