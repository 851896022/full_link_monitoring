#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "data/global.h"
#include <UI/main/forcemodel.h>
#include <ui_forcemodel.h>
#include <UI/main/linkmodel.h>
#include <ui_linkmodel.h>
#include <UI/main/radiomodel.h>
#include <ui_radiomodel.h>
#include <UI/main/sourcemodel.h>
#include <ui_sourcemodel.h>
#include <UI/main/tittle.h>
#include <ui_tittle.h>
#include "wavebar.h"
namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    WaveBar *waveBarDGNList[24];
private:
    Ui::Window *ui;
};

#endif // WINDOW_H
