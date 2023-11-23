#include "addapply.h"
#include "ui_addapply.h"
#include "friendchat.h"
#include "mysocket.h"

extern MySocket *mysocket; // 引用全局变量

addApply::addApply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addApply)
{
    ui->setupUi(this);
    setWindowTitle("好友请求");
    setFixedSize(340,240);
    this->new_name="张大帅";
    editMessage(new_name);
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
    ui->message->setText("已拒绝");
    f->show();
    this->hide();
}

//跳转到friendchat界面&&将信息存到数据库
void addApply::on_confirmBtn_clicked()
{
    friendChat *f=new friendChat();
    f->updateFriendList(new_name);  // 更新当前用户的好友列表

    // 将当前用户名字添加到new_name用户的好友列表


    f->show();
    this->hide();
}

//将发送请求的名字打印
void addApply::editMessage(QString &name)
{
    ui->message->clear();
    ui->message->setText(name+"向你发送了好友请求");
}
