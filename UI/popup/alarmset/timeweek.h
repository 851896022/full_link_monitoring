#ifndef TIMEWEEK_H
#define TIMEWEEK_H

#include <QFrame>
#include "timeday.h"
namespace Ui {
class TimeWeek;
}

class TimeWeek : public QFrame
{
    Q_OBJECT

public:
    explicit TimeWeek(QWidget *parent = 0);
    ~TimeWeek();
    TimeDay *timeDay[7];
private slots:
    void on_oneKey_clicked();

private:
    Ui::TimeWeek *ui;
};

#endif // TIMEWEEK_H
