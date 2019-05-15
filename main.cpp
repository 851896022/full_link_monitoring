#include "window.h"
#include <QApplication>
#include <QObject>
#include "data/global.h"
#include "data/audio/processmanage.h"
#include "data/audio/receivedata.h"
#include "data/alarm/reaudiodata.h"
#include <QEventLoop>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThread gThread;
    g=new Global;

    QObject::connect(&gThread,SIGNAL(started()),g,SLOT(initThis()));
    gThread.start();


    QEventLoop loop;
    QObject::connect(g,SIGNAL(initOK()),&loop,SLOT(quit()));
    loop.exec();

    ReceiveData *receiveData=new ReceiveData;
    //receiveData->initThis();

    ProcessManage *processManage=new ProcessManage;
    processManage->initHexToPcm();
    processManage->initAlarm();

    ReAudioData *reAudioData[36];
    for(int i=0;i<36;i++)
    {
        reAudioData[i]=new ReAudioData;
        reAudioData[i]->moveToThread(g->reAudioDataThread[i]);
        reAudioData[i]->No=i;
        QObject::connect(g->reAudioDataThread[i],SIGNAL(started()),reAudioData[i],SLOT(initThis()));
        g->reAudioDataThread[i]->start();
    }


    Window w;




    //================connect====================
    for(int i=0;i<36;i++)
    {
        QObject::connect(reAudioData[i],SIGNAL(apmOk(int)),&w,SLOT(onRefApm(int)));
        QObject::connect(reAudioData[i],SIGNAL(sendAlarm(int)),&w,SLOT(onAlarm(int)));
        QObject::connect(reAudioData[i],SIGNAL(alarmCancel(int)),&w,SLOT(onAlarmCancel(int)));

    }

    //===========================================
    {
        QEventLoop loop;
        QTimer t;
        QObject::connect(&t,SIGNAL(timeout()),&loop,SLOT(quit()));
        t.start(3000);
        loop.exec();
    }

    w.show();
    return a.exec();
}
