#ifndef TITTLE_H
#define TITTLE_H

#include <QFrame>
#include <QResizeEvent>
#include "UI/popup/globalset.h"
//#include <data/global.h>

namespace Ui {
class Tittle;
}

class Tittle : public QFrame
{
    Q_OBJECT

public:
    explicit Tittle(QWidget *parent = 0);
    ~Tittle();
    GlobalSet *globalSet;
//private:
    Ui::Tittle *ui;
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_btn_set_clicked();
};

#endif // TITTLE_H
