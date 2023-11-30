#include "addfrient.h"
#include "ui_addfrient.h"
#include "friendchat.h"
#include "mysocket.h"
#include <QMessageBox>

extern MySocket *mysocket; // 引用全局变量
addfrient::addfrient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfrient)
{
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
    // 获取框内输入内容
    QString accountToAdd = ui->lineEdit->text();

    // 发送好友请求
    emit confirmButtonClicked(mysocket->m_username, accountToAdd);

    // 显示发送成功的消息框
    QMessageBox::information(this, "成功", "好友请求发送成功！");

    // 清空信息
    ui->lineEdit->setText("");

}

