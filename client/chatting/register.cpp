#include "register.h"
#include "ui_register.h"
#include<QPainter>
#include "register_success.h"
#include"online.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setFixedSize(281,505);
    setWindowTitle("注册");
    ui->name->setText("输入账号");
    ui->password->setText("输入密码");
    //获取数有关据库信息
    online on;
}

void Register::paintEvent(QPaintEvent* ev)
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
    painter.drawText(QRect(9,60,200,80),"注册");
    painter.drawText(QRect(9,100,400,120),"美好之旅");

}

Register::~Register()
{
    delete ui;
}

//跳转到register_success界面&&将信息存到数据库
void Register::on_registerBtn_clicked()
{
    register_success *rc=new register_success();
    rc->show();
    this->hide();
}

bool Register::checkNameIsSame(QVector<QString> &allPerson)
{

}

