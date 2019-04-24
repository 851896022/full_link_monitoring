#ifndef LINKMODEL_H
#define LINKMODEL_H

#include <QFrame>

namespace Ui {
class LinkModel;
}

class LinkModel : public QFrame
{
    Q_OBJECT

public:
    explicit LinkModel(QWidget *parent = 0);
    ~LinkModel();

private:
    Ui::LinkModel *ui;
};

#endif // LINKMODEL_H
