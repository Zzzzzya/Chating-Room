#include "groupchatting.h"
#include "ui_groupchatting.h"
#include<QColorDialog>
#include"online.h"

groupChatting::groupChatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupChatting)
{
    ui->setupUi(this);
    online on;
    on.getgroupPerson();
    on.getGroupPersonIsOnline();
    setTableWidget(on.groupPerson,on.groupPersonIsOnline);
}

groupChatting::~groupChatting()
{
    delete ui;
}

void groupChatting::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setCurrentFont(f);
    ui->textEdit->setFocus();
}


void groupChatting::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ui->textEdit->setFontPointSize(arg1.toDouble());
    ui->textEdit->setFocus();
}

void groupChatting::on_boldBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    ui->textEdit->setFocus();
}


void groupChatting::on_slopeBtn_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}


void groupChatting::on_underlineBtn_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}


void groupChatting::on_setColorBtn_clicked()
{
    color=QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

//需要用到数据库,先不写
void groupChatting::on_preserveBtn_clicked()
{

}


void groupChatting::on_clearBtn_clicked()
{
    ui->textBrowser->clear();
}

//要用到socket,先不写
void groupChatting::on_sendBtn_clicked()
{

}

void groupChatting::on_exitBtn_clicked()
{
    this->hide();
}

void groupChatting::setTableWidget(QVector<QString>&groupPerson,QVector<int>&groupPersonIsOnline)
{
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"成员"<<"在线情况");
    ui->tableWidget->setRowCount(groupPerson.size());
    for(int i=0;i<groupPerson.size();i++)
    {
        for(int j=0;j<2;j++)
        {
            if(j==0)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(groupPerson[i]));
            }
            if(j==1)
            {
                if(groupPersonIsOnline[i]==0)
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem("离线"));
                }
                else
                {
                    ui->tableWidget->setItem(i,j,new QTableWidgetItem("在线"));
                }
            }
        }
    }
    ui->tableWidget->show();
}

