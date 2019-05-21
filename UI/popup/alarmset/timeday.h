#ifndef TIMEDAY_H
#define TIMEDAY_H

#include <QFrame>
#include "timeline.h"
namespace Ui {
class TimeDay;
}

class TimeDay : public QFrame
{
    Q_OBJECT

public:
    explicit TimeDay(QWidget *parent = 0);
    ~TimeDay();
    TimeLine *timeLine[5];
private:
    Ui::TimeDay *ui;
public slots:
    void setTime(int line,QTime startTime,QTime endTime);
};

#endif // TIMEDAY_H
