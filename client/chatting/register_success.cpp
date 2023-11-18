#include "register_success.h"
#include "ui_register_success.h"
#include<QPainter>
#include "friendchat.h"

register_success::register_success(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_success)
{
    ui->setupUi(this);
    setWindowTitle("结果");
    setFixedSize(281,505);
}

void register_success:: paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    //底下横线
    painter.drawLine(QPoint(105,500),QPoint(185,500));
    //设置文字
    QFont font("Arial", 20); // 设置字体为 Arial，大小为 20 粗体 倾斜
    painter.setFont(font);
    painter.drawText(QRect(60,200,230,300),"恭喜注册成功");
}

register_success::~register_success()
{
    delete ui;
}

//跳转到friendchat界面
void register_success::on_backBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

