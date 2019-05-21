#ifndef TIMELINE_H
#define TIMELINE_H

#include <QFrame>
#include "QTime"

namespace Ui {
class TimeLine;
}

class TimeLine : public QFrame
{
    Q_OBJECT

public:
    explicit TimeLine(QWidget *parent = 0);
    ~TimeLine();


    Ui::TimeLine *ui;
public slots:
    void setTime(QTime startTime,QTime endTime);
    QTime getStartTime();
    QTime getEndTime();
};

#endif // TIMELINE_H
