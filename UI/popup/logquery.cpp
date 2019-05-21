#include "logquery.h"
#include "ui_logquery.h"
#include "QMessageBox"

LogQuery::LogQuery(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LogQuery)
{
    ui->setupUi(this);
    model=new QSqlQueryModel;
    typeList<<"user_log"<<"alarm_log";
    QDateTime t=QDateTime::currentDateTime();
    ui->dateTimeEditStart->setDateTime(t.addDays(0-1));
    ui->dateTimeEditEnd->setDateTime(t);


}


LogQuery::~LogQuery()
{
    delete ui;
}

void LogQuery::on_BtnFind_clicked()
{
    /*
    if(!g->mySql.db.isOpen())
    {

        QMessageBox::information(this,"连接失败","数据库连接失败！1001");
        return;
    }
    */
    g->sqlite->takeLog(/*日志内容*/"查询"+ui->type->currentText(),
                     /*表*/"user_log",
                     /*类型*/"操作日志",
                     /*用户名*/"user"
                     );//用户日志模板

    if(model) model->deleteLater();

    model = new QSqlQueryModel;

    //qWarning()<<"查询日志";



    QString type=typeList.at(ui->type->currentIndex());

    QString startTime=ui->dateTimeEditStart->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    QString endTime=ui->dateTimeEditEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    QStringList strHeader;

    QString msg;

        if(ui->type->currentIndex()==0)
        {

            strHeader<<"时间"<<"类型"<<"日志";
            msg+="select time,type,log from "
                    +type
                    +" where dt>'"
                    +startTime
                    +"' and dt<'"
                    +endTime
                +"';　";

        }
        else
        {
            strHeader<<"时间"<<"通道"<<"日志";
            msg+="select time,user,log from "
                    +type
                    +" where dt>'"
                    +startTime
                    +"' and dt<'"
                    +endTime
                +"';　";
        }


    //qDebug()<<msg;

    model->setQuery(msg);//这里直接设置SQL语句，忽略最后一个参数

    while(model->canFetchMore())
    {

        model->fetchMore();

    }

    if(model->rowCount()==0&&model->columnCount()==0)
    {
        QMessageBox::information(this,"连接失败","数据库连接失败！1002");
        return;
    }

    for(int i=0;i<strHeader.count();i++)
    {

        model->setHeaderData(i,Qt::Horizontal,strHeader[i]);
    }

    ui->tableView->setModel(model);

    //qDebug()<< model->query().size();
    //以下是视觉方面的效果，不加也没影响
    
    //隔行变色

    ui->tableView->setAlternatingRowColors(true);
    //setHorizontalHeaderLabels;
    //ui->tableView->horizontalHeader()->
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    //设置行高

    int row_count = model->rowCount();

    for(int i =0; i < row_count; i++)
    {
      ui->tableView->setRowHeight(i, 20);
    }
}


#include <QFileDialog>
#include <QTextEdit>

void LogQuery::on_btnSaveToFile_clicked()
{
   QTableView *table=ui->tableView;
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),
                QString(), tr("EXCEL 文档 (*.csv );;文本文件 (*.txt);;"));

    if(filepath.isEmpty())return;
    if(table->model()==NULL)return;
        int row = table->model()->rowCount();
        int col = table->model()->columnCount();
        QList<QString> list;
        //添加列标题
        QString HeaderRow;
        for(int i=0;i<col;i++)
        {
            HeaderRow.append(table->model()->headerData(i,Qt::Horizontal).toString()+",");
        }
        list.push_back(HeaderRow);
        for(int i=0;i<row;i++)
        {
            QString rowStr = "";
            for(int j=0;j<col;j++){

                rowStr += table->model()->data(table->model()->index(i,j)).toString() + ",";
            }
            list.push_back(rowStr);
        }
        QTextEdit textEdit;
        for(int i=0;i<list.size();i++)
        {
            textEdit.append(list.at(i));
        }

        QFile file(filepath);
        if(file.open(QFile::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(&file);
            //ts.setCodec("UTF-8");
            ts<<textEdit.document()->toPlainText();
            file.close();
        }
}
