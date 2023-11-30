#include "addapply.h"
#include "ui_addapply.h"
#include "friendchat.h"
#include "mysocket.h"

extern MySocket *mysocket;

addApply::addApply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addApply)
{
    ui->setupUi(this);
    setWindowTitle("好友请求");
    setFixedSize(340,240);
    connect(mysocket, &MySocket::friendApplyReceived, this, &addApply::handleFriendRequests);
    //先向server端请求是否有好友申请
    mysocket->requestFriendApplication();   // 括号里是当前用户的username
}

void addApply::handleFriendRequests(const QJsonArray &friendApply)
{
    ui->message->clear();
    if(friendApply.isEmpty()){
        ui->message->setText("暂无好友申请");
        return;
    }
    // 获取第一个好友申请
    QString friendName = friendApply.first().toString();
    this->new_name = friendName;

    // 设置 QLabel 的文本
    QString displayText = QString("%1想成为您的好友").arg(friendName);

    ui->message->setText(displayText);

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
    mysocket->addFriend(, this->new_name);      // 参数：当前用户名，框内申请者的用户名

}

//将发送请求的名字打印
void addApply::editMessage(QString &name)
{
    ui->message->clear();
    ui->message->setText(name+"向你发送了好友请求");
}
