#include "tittle.h"
#include "ui_tittle.h"

Tittle::Tittle(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Tittle)
{
    ui->setupUi(this);
    ui->name->setText(g->stationName);
    globalSet=new GlobalSet;
    logQuery=new LogQuery;
}

Tittle::~Tittle()
{
    delete ui;
}
#include <QFont>
void Tittle::resizeEvent(QResizeEvent *event)
{

    event->accept();
    this->setMaximumHeight(this->parentWidget()->geometry().height()*0.065);

    this->ui->gridLayout->setContentsMargins(10,this->geometry().height()*0.15,10,0);
    QFont tmp= ui->name->font();
    tmp.setPointSizeF(this->geometry().height()*0.3);
    ui->name->setFont(tmp);

    ui->btn_set->setIconSize(QSize(this->geometry().height()*1.6,this->geometry().height()*0.8));
    ui->btn_log->setIconSize(QSize(this->geometry().height()*1.6,this->geometry().height()*0.8));
    ui->btn_mp3->setIconSize(QSize(this->geometry().height()*1.6,this->geometry().height()*0.8));
}
#include <QInputDialog>
void Tittle::on_btn_set_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("请输入操作密码"),
                                          tr("密码:"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        if(text==QString("admin"))
        {
            globalSet->deleteLater();
            globalSet= new GlobalSet;
            globalSet->setWindowFlags(globalSet->windowFlags()  |   Qt::WindowStaysOnTopHint);
            globalSet->show();
            globalSet->raise();
            globalSet->activateWindow();
        }
    }


}
#include <QDesktopServices>
void Tittle::on_btn_mp3_clicked()
{
    QString dir;
    {
        QString filename;
        filename+=(qApp->applicationDirPath()+"/sav/savedir.sav");
        //判断文件是否存在
        QFile *file = new QFile(filename);
        if(file->open(QIODevice::ReadOnly))
        {

            {
                QString ba(file->readLine());
                ba=QString::fromStdString( ba.toStdString());
                dir=ba;
            }




            file->close();
        }
        file->deleteLater();
    }
    QDesktopServices::openUrl(QUrl(dir, QUrl::TolerantMode));
}

void Tittle::on_btn_log_clicked()
{
    logQuery->deleteLater();
    logQuery=new LogQuery;
    logQuery->setWindowFlags(globalSet->windowFlags()  |   Qt::WindowStaysOnTopHint);
    logQuery->show();
    logQuery->raise();
    logQuery->activateWindow();
}
