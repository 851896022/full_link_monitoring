#include "sqlite.h"
#include "QDateTime"
#include "QApplication"
//g->mySql.takeLog(/*日志内容*/QString("修改"),
//                 /*表*/"user_log",
//                 /*类型*/"user",
//                 /*用户名*/g->userName
//                 );//用户日志模板
SQLite::SQLite(QObject *parent) : QObject(parent)
{

}
#include <QFile>
#include <QFileInfo>
void SQLite::initThis(QString HostName,QString DataBaseName,QString UserName,QString PassWord)
{
    //检测文件是否存在
    SqlHostName=HostName;
    SqlDataBaseName=DataBaseName;
    SqlUserName=UserName;
    SqlPassWord=PassWord;
    QFileInfo info(qApp->applicationDirPath()+"/"+ SqlDataBaseName);
    if(!info.isFile())
    {
        qDebug()<<"文件不存在";
        QFile file(qApp->applicationDirPath()+"/"+ SqlDataBaseName);
        if(file.open(QIODevice::ReadWrite))
        {
            //已经存在
            //:/other/DataBase.db
            QFile source(":/other/DataBase.db");
            if(source.open(QIODevice::ReadOnly))
            {


                file.write(source.readAll());
                file.flush();
                file.close();
                qDebug()<<"成功写入"<<qApp->applicationDirPath()+"/"+ SqlDataBaseName;
            }



        }
        else
        {

            qDebug()<<"目标文件打开失败";
        }
    }







    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
   // db.setHostName(SqlHostName);
    db.setDatabaseName(qApp->applicationDirPath()+"/"+ SqlDataBaseName);       //这里输入你的数据库名
    //db.setUserName(SqlUserName);
    //db.setPassword(SqlPassWord);   //这里输入你的密码
    if (!db.open())
    {
        qDebug()<<"数据库打开失败！";
    }
    else
    {
        query=QSqlQuery(db);
    }
}

bool SQLite::command(QString cmd)
{
    return query.exec(cmd);
    return false;
        if(query.exec(cmd))
        {
            return true;//一切正常
        }
        else //尝试重新连接
        {

            db.close();
            if(db.open())
            {

                if(query.exec(cmd))//重新尝试执行
                {
                    qDebug()<<"重新连接后，执行成功。";
                    return  true; //成功
                }
                else
                {
                    qDebug()<<"重新连接后，执行失败。";
                    return false; //失败
                }
            }
            else
            {
                qDebug()<<"重新连接失败。";
                return false;//打开失败
            }
        }




}
bool SQLite::takeLog(QString log,QString sheet,QString type,QString user)
{
    //return mySql.command("log values('"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"', '"+QString::number(type)+"', 'admin','"+str+"',NULL)");
    //时间 字符时间 类型 用户 日志 编号
    QMutexLocker locker(&mutex);

    QString cmd;
    cmd+="insert into ";
    cmd+=sheet;
    cmd+=" values('";
    cmd+=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"', '";
    cmd+=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"', '";
    cmd+=type+"', '";
    cmd+=user+"', '";
    cmd+=log+"', ";
    cmd+="NULL);";
    qDebug()<<cmd;
    return command(cmd);
}
