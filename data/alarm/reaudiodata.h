#ifndef REAUDIODATA_H
#define REAUDIODATA_H

#include <QObject>
#include "data/global.h"
#include <QList>
class ReAudioData : public QObject
{
    Q_OBJECT
public:
    explicit ReAudioData(QObject *parent = nullptr);
    int No;
    QUdpSocket *socket;
    int sendCount=0;
    int alarmCount=0;
    QTimer * timer;
signals:
    void apmOk(int ch);
    void sendAlarm(int ch);
    void alarmCancel(int ch);
public slots:
    void initThis();
    void initThis(int);
    void onReadyRead();
    void onTimerOut();
    bool thisChIsWork();

};

#endif // REAUDIODATA_H
