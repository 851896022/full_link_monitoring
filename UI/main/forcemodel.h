#ifndef FORCEMODEL_H
#define FORCEMODEL_H

#include <QFrame>

namespace Ui {
class ForceModel;
}

class ForceModel : public QFrame
{
    Q_OBJECT

public:
    explicit ForceModel(QWidget *parent = 0);
    ~ForceModel();

private:
    Ui::ForceModel *ui;
};

#endif // FORCEMODEL_H
