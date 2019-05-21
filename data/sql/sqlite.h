#ifndef SQLITE_H
#define SQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#include <QMutex>
class SQLite : public QObject
{
    Q_OBJECT
public:
    explicit SQLite(QObject *parent = nullptr);
    QString SqlHostName;
    QString SqlDataBaseName;
    QString SqlUserName;
    QString SqlPassWord;
    QSqlDatabase db;
    QSqlQuery query;
    QMutex mutex;
signals:

public slots:
    void initThis(QString HostName,QString DataBaseName,QString UserName,QString PassWord);
    bool command(QString);
    bool takeLog(QString log="NULL",QString sheet="log",QString type="NULL",QString user="admin");
};

#endif // SQLITE_H
