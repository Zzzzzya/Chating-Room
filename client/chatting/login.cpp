#include "login.h"
#include "ui_login.h"
#include<QPaintEvent>
#include<QPainter>
#include<QFont>
#include "friendchat.h"
#include "register.h"
#include"online.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setFixedSize(281,505);
    setWindowTitle("凌烟阁聊天室");
    ui->name->setText("输入账号");
    ui->password->setText("输入密码");
    //获取数有关据库信息
    online on;
}

void login::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    //设置背景图
    QPixmap pix;
    pix.load(":/picture/wx.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //底下横线
    painter.drawLine(QPoint(105,500),QPoint(185,500));
    //设置文字
    QFont font("Arial", 20,QFont::Bold,true); // 设置字体为 Arial，大小为 20 粗体 倾斜
    painter.setFont(font);
    painter.drawText(QRect(9,60,200,80),"登录");
    painter.drawText(QRect(9,100,400,120),"美好之旅");

}

login::~login()
{
    delete ui;
}

//跳转到friendchat界面
void login::on_loginBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//跳转到register界面
void login::on_registerBtn_clicked()
{
    Register *r=new Register();
    r->show();
    this->hide();
}

bool login::checkMessage(QVector<QString> &allPerson,QVector<QString> &password)
{

}

