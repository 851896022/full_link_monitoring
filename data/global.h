#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDebug>
#include <QProcess>

#include <QHostAddress>
#include <QUdpSocket>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QList>
#include <QThread>


#include "data/audio/player.h"
#include "data/sql/sqlite.h"
struct TimeSlot
{
    QTime startTime;
    QTime endTime;
};
struct TimeSlotDay
{
    TimeSlot line[5];
};
struct TimeSlotWeek
{
    TimeSlotDay day[7];
};
struct GateLinkStruct
{
    int sourceGate_1=0;
    int sourceGate_2=0;
    int radioGate=0;
    int sourceDelay_1=0;
    int sourceDelay_2=0;
    int radioDelay=0;
};
struct LinkALarmGateTime
{
    GateLinkStruct linkGate;
    TimeSlotWeek linkTime;
};
struct ChAlarmGateTime
{
    int  alarmGate;
    int  alarmDelay;
    TimeSlotWeek * timeList;
    bool isUsing=false;
};
struct equStruct
{
    QString chName[18];
    QString ip;
    int port={0};
    int No={0};
    QString name;

};
enum AlarmType
{
    Normal,
    Similar,
    Range,
    All,
    SimilarCancel,
    RangeCancel,
    Other,

};
struct AlarmInfo
{
    int alarmNo=0;
    int alarmCh=0;
    AlarmType alarmType=Other;
    QDateTime startTime;
    QDateTime endTime;
};
class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    bool isInitOk=false;
    //========UI全局设置===========
    //链路总数
    int linkCount;
    //台站名称
    QString stationName;
    //卫星接收机名称
    QString receiverName[8];
    //开路接收名称
    QString radioName[8];
    //流动速度
    int textMoveSpeed=10;
    //流动字符
    QString textMoveText[16];
    //==========系统配置=============
    equStruct equ[10];
    int equCount;
    QString mp3SaveDir;


    //=======数据=======
    //最新幅度
    int ac32Apm[200];
    int xjjcApm[200];
    //当前监听通道
    int nowPlayCh=999;
    //最大值0~32768
    int maxValue[200];

    //当前录音文件
    QString nowFileName[200];
    //报警信息
    QList<AlarmInfo> alarmListWaitSend;
    LinkALarmGateTime linkALarmGateTime[8];
    bool linkIsUsing[8];
    ChAlarmGateTime chAlarmGateTime[36];
    int alarmGate=100;
    int alarmDelay=100000;

    //监听增益 0.1~5.0
    float listenGain=1.0;

    //==========对象=======
    QUdpSocket *receivePCM;
    Player *player;
    QThread *reAudioDataThread[36];
    SQLite *sqlite;

signals:
    void initOK();
public slots:
    void initThis();
    void loadEqu();
    void changePlayCh(int);
    void stopPlay();
    void onReceivePCM();
public:
    QString getChName(int ch);

};
extern Global *g;
#endif // GLOBAL_H
