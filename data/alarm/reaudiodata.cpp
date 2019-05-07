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
}
void ReAudioData::onReadyRead()
{

    char ch[65536]={0};
    int realsize=0;

    //if(socket->pendingDatagramSize()>0)
    {
        realsize=socket->readDatagram((char*)ch, 65536);
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
        int MAX=0;
        short* ch16=(short*)ch;
        for(int i=0;i<(2304/2);i++)
        {
            if(MAX<ch16[i])
            {
                MAX=ch16[i];
            }
        }
/*
        if(MAX<g->maxValue[No])
        {
            g->maxValue[No]=MAX;
        }
        else
        {
            g->maxValue[No]=((g->maxValue[No]*9.0)+(MAX*1.0))/10.0;
        }
*/
        g->maxValue[No]=MAX;

    }
    //qDebug()<<g->audioCache[No].count();

}
