#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    //ui->linkModel_2->hide();


    ui->linkModel_1->initThis(0);
    ui->linkModel_2->initThis(1);

}

Window::~Window()
{
    delete ui;
}
