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
        if(MAX>99) MAX=98+(rand()%2);
        if(MAX<=1)
        {
            apmCount--;
            if(apmCount<=0)
            {
                apmCount=0;
            }
        }
        else
        {
            apmCount++;
            if(apmCount>100)
            {
                apmCount=100;
            }
        }
        if(apmCount<50)
        {
            MAX=0;
        }
        g->ac32Apm[No]=MAX;

        //=============
        if(sendCount>(15+(qrand()%10)))
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
    //if(No<12) qDebug()<<No<<thisChIsWork();
    if(g->ac32Apm[No]>=g->chAlarmGateTime[No].alarmGate
            || (!thisChIsWork()))
    {
        if(alarmCount>=(g->chAlarmGateTime[No].alarmDelay*10))
        {
            emit alarmCancel(No);
        }
        alarmCount=0;
    }
    else
    {
        alarmCount++;
    }

    if(alarmCount==(g->chAlarmGateTime[No].alarmDelay*10))
    {
        emit sendAlarm(No);
        int tmp=No+1;
        if(tmp>16)
        {
            tmp-=2;
        }
        g->sqlite->takeLog(/*日志内容*/g->getChName(No)+QString("音频幅度过低"),
                         /*表*/"alarm_log",
                         /*类型*/"alarm",
                         /*用户名*/QString::number(tmp)
                         );//用户日志模板
    }

    if(alarmCount>(g->chAlarmGateTime[No].alarmDelay*10))
    {
        alarmCount=(g->chAlarmGateTime[No].alarmDelay*10)+1;
    }

}
bool ReAudioData::thisChIsWork()
{


    QDateTime dt=QDateTime::currentDateTime();
    int weekDay=dt.date().dayOfWeek()-1;
    if(g->chAlarmGateTime[No].isUsing==true)
    {
        for(int i=0;i<5;i++)
        {

            QTime start= g->chAlarmGateTime[No].timeList->day[weekDay].line[i].startTime;
            QTime end=g->chAlarmGateTime[No].timeList->day[weekDay].line[i].endTime;
            if(dt.time()>=start)
            {
                if(end==QTime(0,0))
                {
                    //if(No<12)qDebug()<<No<<"符合时段"<<i;
                    return true;
                }
                else if(dt.time()<end)
                {
                    //if(No<12)qDebug()<<No<<"符合时段"<<i;
                    return true;
                }

            }
        }
        //if(No<12)qDebug()<<No<<"没有符合时段";
    }
    else
    {
        //if(No<12)qDebug()<<No<<"没有启用？？？";
        return false;
    }
    return false;
}
