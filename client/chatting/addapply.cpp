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
    //先向server端请求是否有好友申请

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
void addApply::on_confirmBtn_clicked()          // 同意后首先清除该请求
{
    ui->message->setText("暂无未处理申请");
/*
    关于流程：
    1、在数据库找到发起方
    2、在当前用户的好友列表字段增加发起方
    3、在数据库找到目的方
    4、在发起方的好友列表字段增加当前用户
    5、通知主界面更新ui
*/

}

//将发送请求的名字打印
void addApply::editMessage(QString &name)
{
    ui->message->clear();
    ui->message->setText(name+"向你发送了好友请求");
}
