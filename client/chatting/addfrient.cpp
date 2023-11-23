#include "addfrient.h"
#include "ui_addfrient.h"
#include "friendchat.h"
#include "mysocket.h"

extern MySocket *mysocket; // 引用全局变量
addfrient::addfrient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfrient)
{
//    MySocket *ms = new MySocket(nullptr);
//    connect(this, &addfrient::confirmButtonClicked, ms, &MySocket::sendFriendRequest);
    ui->setupUi(this);
    setWindowTitle("添加好友");
    setFixedSize(340,240);
    connect(this, &addfrient::confirmButtonClicked, mysocket, &MySocket::sendFriendRequest);

}

addfrient::~addfrient()
{
    delete ui;
}

//跳转到friendchat界面
void addfrient::on_backBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//跳转到friendchat界面
void addfrient::on_cancelBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//发送请求&显示发送成功&将信息清空
void addfrient::on_confirmBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    ui->lineEdit->setText("");
    emit confirmButtonClicked(ui->lineEdit->text());
    this->hide();
}

