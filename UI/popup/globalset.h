#ifndef GLOBALSET_H
#define GLOBALSET_H

#include <QFrame>
#include <data/global.h>
#include <QDateTime>
#include "alarmset/timelink.h"
#include "data/global.h"
namespace Ui {
class GlobalSet;
}

class GlobalSet : public QFrame
{
    Q_OBJECT

public:
    explicit GlobalSet(QWidget *parent = 0);
    ~GlobalSet();
    TimeLink timeLink;
private slots:
    void on_btn_save_clicked();

    void on_btn_chose_clicked();

    void on_btn_cacel_clicked();

private:
    Ui::GlobalSet *ui;
};

#endif // GLOBALSET_H
