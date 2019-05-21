#ifndef GATELINK_H
#define GATELINK_H

#include <QFrame>

namespace Ui {
class GateLink;
}

class GateLink : public QFrame
{
    Q_OBJECT

public:
    explicit GateLink(QWidget *parent = 0);
    ~GateLink();
    int sourceGate_1();
    int sourceGate_2();
    int radioGate();
    int sourceDelay_1();
    int sourceDelay_2();
    int radioDelay();

    void setSourceGate_1(int num);
    void setSourceGate_2(int num);
    void setRadioGate(int num);
    void setSourceDelay_1(int num);
    void setSourceDelay_2(int num);
    void setRadioDelay(int num);
private:

    Ui::GateLink *ui;
};

#endif // GATELINK_H
