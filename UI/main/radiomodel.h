#ifndef RADIOMODEL_H
#define RADIOMODEL_H

#include <QFrame>

namespace Ui {
class RadioModel;
}

class RadioModel : public QFrame
{
    Q_OBJECT

public:
    explicit RadioModel(QWidget *parent = 0);
    ~RadioModel();

private:
    Ui::RadioModel *ui;
};

#endif // RADIOMODEL_H
