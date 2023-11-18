#include "addapply.h"
#include "ui_addapply.h"
#include "friendchat.h"


addApply::addApply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addApply)
{
    ui->setupUi(this);
    setWindowTitle("好友请求");
    setFixedSize(340,240);
    QString name="张大帅";
    editMessage(name);
}

addApply::~addApply()
{
    delete ui;
}

//跳转到friendchat界面
void addApply::on_backBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//显示已拒绝&跳转到friendchat界面
void addApply::on_cancelBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//跳转到friendchat界面&&将信息存到数据库
void addApply::on_confirmBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//将发送请求的名字打印
void addApply::editMessage(QString &name)
{
    ui->message->setText(name+"向你发送了好友请求");
}
