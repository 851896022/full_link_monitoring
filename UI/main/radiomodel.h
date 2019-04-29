#ifndef RADIOMODEL_H
#define RADIOMODEL_H

#include <QFrame>
#include "data/global.h"
namespace Ui {
class RadioModel;
}

class RadioModel : public QFrame
{
    Q_OBJECT
    int No=0;
public:
    explicit RadioModel(QWidget *parent = 0);
    ~RadioModel();

//private:
    Ui::RadioModel *ui;
public slots:
    void initThis(int No);
};

#endif // RADIOMODEL_H
