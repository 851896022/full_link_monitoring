#ifndef REAUDIODATA_H
#define REAUDIODATA_H

#include <QObject>
#include "global.h"
class ReAudioData : public QObject
{
    Q_OBJECT
public:
    explicit ReAudioData(QObject *parent = nullptr);
    int No;
    QUdpSocket *socket;
signals:

public slots:
    void initThis();
    void onReadyRead();

};

#endif // REAUDIODATA_H
