#ifndef LOGQUERY_H
#define LOGQUERY_H

#include <QFrame>
#include <QSqlQueryModel>
#include "data/global.h"
#include "QDateTime"
namespace Ui {
class LogQuery;
}

class LogQuery : public QFrame
{
    Q_OBJECT

public:
    explicit LogQuery(QWidget *parent = 0);
    ~LogQuery();
    QSqlQueryModel *model;
    QStringList typeList;
private slots:
    void on_BtnFind_clicked();


    void on_btnSaveToFile_clicked();

private:
    Ui::LogQuery *ui;
};

#endif // LOGQUERY_H
