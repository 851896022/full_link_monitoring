#ifndef LINKMODEL_H
#define LINKMODEL_H

#include <QFrame>
#include <QMovie>
namespace Ui {
class LinkModel;
}

class LinkModel : public QFrame
{
    Q_OBJECT

public:
    explicit LinkModel(QWidget *parent = 0);
    ~LinkModel();
    int No=0;
    void initThis(int No);
    QMovie movie;
//private:
    Ui::LinkModel *ui;
};

#endif // LINKMODEL_H
