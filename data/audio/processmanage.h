#ifndef PROCESSMANAGE_H
#define PROCESSMANAGE_H

#include <QObject>

#include <data/global.h>
class ProcessManage : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManage(QObject *parent = nullptr);
    QProcess *hexToPcm[10];
    QProcess *alarm;
signals:

public slots:
    void initHexToPcm();
    void initAlarm();
};

#endif // PROCESSMANAGE_H
