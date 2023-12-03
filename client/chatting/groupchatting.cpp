#include "groupchatting.h"
#include "ui_groupchatting.h"
#include<QColorDialog>
#include"mysocket.h"
#include "usersql.h"

extern MySocket *mysocket;
extern UserSql *user;

groupChatting::groupChatting(QWidget *parent,QString groupName) :
    QWidget(parent),
    ui(new Ui::groupChatting)
{
    ui->setupUi(this);
    this->GName=groupName;
    mysocket->requestGroupMemberCount(this->GName);
    connect(mysocket,&MySocket::groupMembersCountUpdated,this,&groupChatting::getMessage);
    setTableWidget(user->cnt,user->groupNumberName,user->friendIsOnline,user->userFriend);
    connect(mysocket,&MySocket::groupMessageReceived,this,&groupChatting::showMessage);
}

groupChatting::~groupChatting()
{
    delete ui;
}

void groupChatting::showMessage(const QString& message)
{
    ui->textBrowser->setText(message);
}

void groupChatting::getMessage(const QJsonObject &groupMessage)
{
    user->cnt=groupMessage["count"].toInt();
    QJsonArray arr=groupMessage["members"].toArray();
    user->groupNumberName.resize(user->cnt);
    for(int i=0;i<arr.size();i++)
    {
        user->groupNumberName[i-1]=arr[i].toString();
    }
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

void groupChatting::on_sendBtn_clicked()
{
    mysocket->sendGroupMessage(this->GName,user->userName,ui->textEdit->toPlainText());
}

void groupChatting::on_exitBtn_clicked()
{
    this->hide();
}

void groupChatting::setTableWidget(int cnt,QVector<QString>groupNumberName,QVector<int>&friendIsOnline,QVector<QString>&userFriend)
{
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"成员"<<"在线情况");
    ui->tableWidget->setRowCount(cnt);
    for(int i=0;i<cnt;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(j==0)
            {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(groupNumberName[i]));
            }
            if(j==1)
            {
                for(int k=0;k<friendIsOnline.size();k++)
                {
                    if(groupNumberName[i]==userFriend[k])
                    {
                        if(friendIsOnline[k]==0)
                        {
                            ui->tableWidget->setItem(i,j,new QTableWidgetItem("离线"));
                        }
                        if(friendIsOnline[k]==1)
                        {
                            ui->tableWidget->setItem(i,j,new QTableWidgetItem("离线"));
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
    ui->tableWidget->show();
}

