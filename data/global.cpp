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



}
