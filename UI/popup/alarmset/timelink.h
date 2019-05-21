#ifndef TIMELINK_H
#define TIMELINK_H

#include <QFrame>
#include "timeweek.h"
#include "gatelink.h"
namespace Ui {
class TimeLink;
}

class TimeLink : public QFrame
{
    Q_OBJECT

public:
    explicit TimeLink(QWidget *parent = 0);
    ~TimeLink();
    GateLink *gateLink[8];
    TimeWeek *timeWeek[8];
private:
    Ui::TimeLink *ui;
};

#endif // TIMELINK_H
