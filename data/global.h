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

    //当前录音文件
    QString nowFileName[200];
    //报警信息
    QList<AlarmInfo> alarmListWaitSend;

    //==========对象=======
    QUdpSocket *receivePCM;
    Player *player;

signals:

public slots:
    void initThis();
    void loadEqu();
    void changePlayCh(int);
    void stopPlay();
    void onReceivePCM();
};
extern Global *g;
#endif // GLOBAL_H
