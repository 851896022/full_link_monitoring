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
    ui->linkModel_1->initThis(0);
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


    logoButton[0]=ui->linkModel_1->ui->source_1->ui->toolButton_1;
    logoButton[1]=ui->linkModel_1->ui->source_1->ui->toolButton_2;
    logoButton[2]=ui->linkModel_1->ui->radio_1->ui->toolButton_1;

    logoButton[3]=ui->linkModel_1->ui->source_2->ui->toolButton_1;
    logoButton[4]=ui->linkModel_1->ui->source_2->ui->toolButton_2;
    logoButton[5]=ui->linkModel_1->ui->radio_2->ui->toolButton_1;

    logoButton[6]=ui->linkModel_1->ui->source_3->ui->toolButton_1;
    logoButton[7]=ui->linkModel_1->ui->source_3->ui->toolButton_2;
    logoButton[8]=ui->linkModel_1->ui->radio_3->ui->toolButton_1;

    logoButton[9]=ui->linkModel_1->ui->source_4->ui->toolButton_1;
    logoButton[10]=ui->linkModel_1->ui->source_4->ui->toolButton_2;
    logoButton[11]=ui->linkModel_1->ui->radio_4->ui->toolButton_1;



    logoButton[12]=ui->linkModel_2->ui->source_1->ui->toolButton_1;
    logoButton[13]=ui->linkModel_2->ui->source_1->ui->toolButton_2;
    logoButton[14]=ui->linkModel_2->ui->radio_1->ui->toolButton_1;

    logoButton[15]=ui->linkModel_2->ui->source_2->ui->toolButton_1;
    logoButton[16]=ui->linkModel_2->ui->source_2->ui->toolButton_2;
    logoButton[17]=ui->linkModel_2->ui->radio_2->ui->toolButton_1;

    logoButton[18]=ui->linkModel_2->ui->source_3->ui->toolButton_1;
    logoButton[19]=ui->linkModel_2->ui->source_3->ui->toolButton_2;
    logoButton[20]=ui->linkModel_2->ui->radio_3->ui->toolButton_1;

    logoButton[21]=ui->linkModel_2->ui->source_4->ui->toolButton_1;
    logoButton[22]=ui->linkModel_2->ui->source_4->ui->toolButton_2;
    logoButton[23]=ui->linkModel_2->ui->radio_4->ui->toolButton_1;

    for(int i=0;i<24;i++)
    {
        waveBarDGNList[i]->setHeadHeight(0);
        waveBarDGNList[i]->setStep(0.7);
        waveBarDGNList[i]->setSpace(2);
        connect(logoButton[i],SIGNAL(clicked(bool)),this,SLOT(onLogoButtonClicked(bool)));
    }

}

Window::~Window()
{
    delete ui;
}
void Window::closeEvent(QCloseEvent *event)
{
    {
        QProcess p;
        QString c = "taskkill /im pcm_to_mp3.exe /f";
        p.execute(c);
        p.close();

    }
    {
        QProcess p;
        QString c = "taskkill /im hex_to_pcm.exe /f";
        p.execute(c);
        p.close();

    }
    {
        QProcess p;
        QString c = "taskkill /im alarm_server.exe /f";
        p.execute(c);
        p.close();

    }
    {
        QProcess p;
        QString c = "taskkill /im "+qApp->applicationName()+".exe /f";
        p.execute(c);
        p.close();

    }
    event->accept();
}
void Window::onLogoButtonClicked(bool)
{
    int i;
    QToolButton *c=(QToolButton*)sender();
    for(i=0;i<24;i++)
    {
        if(c==logoButton[i])
        {
            if(g->nowPlayCh==i)
            {

                g->stopPlay();
                logoButton[i]->setStyleSheet("background-color: rgba(0, 255, 0, 0);");
                g->nowPlayCh=999;
            }
            else
            {
                g->changePlayCh(i);
                logoButton[i]->setStyleSheet("background-color: rgba(0, 255, 0, 255);");
                g->nowPlayCh=i;
            }


        }
        else
        {
            logoButton[i]->setStyleSheet("background-color: rgba(0, 255, 0, 0);");
        }
    }

}
void Window::onRefApm()
{
    for(int i=0;i<24;i++)
    {
        waveBarDGNList[i]->setValue(g->ac32Apm[i]);
    }
}
void Window::onRefApm(int i)
{
    waveBarDGNList[i]->setValue(g->ac32Apm[i]);
}
