#ifndef SOURCEMODEL_H
#define SOURCEMODEL_H

#include <QFrame>
#include "data/global.h"
namespace Ui {
class SourceModel;
}

class SourceModel : public QFrame
{
    Q_OBJECT

public:
    explicit SourceModel(QWidget *parent = 0);
    ~SourceModel();
    int No;
    void initThis(int No);
//private:
    Ui::SourceModel *ui;
};

#endif // SOURCEMODEL_H
