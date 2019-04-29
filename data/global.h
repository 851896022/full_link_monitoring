#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDebug>
class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    //========全局设置===========
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



    //=======数据=======
    //最新幅度
    int ac32Apm[36];
    int xjjcApm[36];

signals:

public slots:
    void initThis();
};
extern Global *g;
#endif // GLOBAL_H
