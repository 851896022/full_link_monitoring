#ifndef TITTLE_H
#define TITTLE_H

#include <QFrame>
#include <QResizeEvent>
#include <data/global.h>
namespace Ui {
class Tittle;
}

class Tittle : public QFrame
{
    Q_OBJECT

public:
    explicit Tittle(QWidget *parent = 0);
    ~Tittle();

//private:
    Ui::Tittle *ui;
    void resizeEvent(QResizeEvent *event);

};

#endif // TITTLE_H
