#ifndef RECEIVEDATA_H
#define RECEIVEDATA_H

#include <QObject>
#include "data/global.h"
class ReceiveData : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveData(QObject *parent = nullptr);

    QUdpSocket *socket;
signals:
    void sendALarm(int,int,QDateTime);
    void sendSim(int ch,float sim);
    void apmRef();
public slots:
    void onReceived();
    void initThis();
};

#endif // RECEIVEDATA_H
