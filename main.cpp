#include "window.h"
#include <QApplication>
#include <QObject>
#include "data/global.h"
#include "data/audio/processmanage.h"
#include "data/audio/receivedata.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g=new Global;
    g->initThis();
    ReceiveData *receiveData=new ReceiveData;
    receiveData->initThis();

    ProcessManage *processManage=new ProcessManage;
    processManage->initHexToPcm();
    processManage->initAlarm();



    Window w;
    w.show();

    QObject::connect(receiveData,SIGNAL(apmRef()),&w,SLOT(onRefApm()));
    return a.exec();
}
