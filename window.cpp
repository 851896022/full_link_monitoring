#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    if(g->linkCount<2)
    {
        ui->linkModel_2->hide();
    }
    ui->linkModel_2->initThis(0);
    ui->linkModel_2->initThis(1);

    waveBarDGNList[0]=ui->linkModel_1->ui->source_1->ui->waveBar_1;
    waveBarDGNList[1]=ui->linkModel_1->ui->source_1->ui->waveBar_2;
    waveBarDGNList[2]=ui->linkModel_1->ui->radio_1->ui->waveBar_1;

    waveBarDGNList[3]=ui->linkModel_1->ui->source_2->ui->waveBar_1;
    waveBarDGNList[4]=ui->linkModel_1->ui->source_2->ui->waveBar_2;
    waveBarDGNList[5]=ui->linkModel_1->ui->radio_2->ui->waveBar_1;

    waveBarDGNList[6]=ui->linkModel_1->ui->source_3->ui->waveBar_1;
    waveBarDGNList[7]=ui->linkModel_1->ui->source_3->ui->waveBar_2;
    waveBarDGNList[8]=ui->linkModel_1->ui->radio_3->ui->waveBar_1;

    waveBarDGNList[9]=ui->linkModel_1->ui->source_4->ui->waveBar_1;
    waveBarDGNList[10]=ui->linkModel_1->ui->source_4->ui->waveBar_2;
    waveBarDGNList[11]=ui->linkModel_1->ui->radio_4->ui->waveBar_1;



    waveBarDGNList[12]=ui->linkModel_2->ui->source_1->ui->waveBar_1;
    waveBarDGNList[13]=ui->linkModel_2->ui->source_1->ui->waveBar_2;
    waveBarDGNList[14]=ui->linkModel_2->ui->radio_1->ui->waveBar_1;

    waveBarDGNList[15]=ui->linkModel_2->ui->source_2->ui->waveBar_1;
    waveBarDGNList[16]=ui->linkModel_2->ui->source_2->ui->waveBar_2;
    waveBarDGNList[17]=ui->linkModel_2->ui->radio_2->ui->waveBar_1;

    waveBarDGNList[18]=ui->linkModel_2->ui->source_3->ui->waveBar_1;
    waveBarDGNList[19]=ui->linkModel_2->ui->source_3->ui->waveBar_2;
    waveBarDGNList[20]=ui->linkModel_2->ui->radio_3->ui->waveBar_1;

    waveBarDGNList[21]=ui->linkModel_2->ui->source_4->ui->waveBar_1;
    waveBarDGNList[22]=ui->linkModel_2->ui->source_4->ui->waveBar_2;
    waveBarDGNList[23]=ui->linkModel_2->ui->radio_4->ui->waveBar_1;





}

Window::~Window()
{
    delete ui;
}
