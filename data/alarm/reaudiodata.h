#ifndef REAUDIODATA_H
#define REAUDIODATA_H

#include <QObject>
#include "data/global.h"
class ReAudioData : public QObject
{
    Q_OBJECT
public:
    explicit ReAudioData(QObject *parent = nullptr);
    int No;
    QUdpSocket *socket;
signals:
    void apmOk(int ch);
public slots:
    void initThis();
    void initThis(int);
    void onReadyRead();

};

#endif // REAUDIODATA_H
