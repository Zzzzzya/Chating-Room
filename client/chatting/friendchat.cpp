#include "friendchat.h"
#include "ui_friendchat.h"
#include<QPainter>
#include "groupchat.h"
#include "addfrient.h"
#include "creatgroup.h"
#include "addapply.h"
#include "online.h"
#include<QToolButton>
#include<QDebug>
#include<QListWidget>
#include <QScrollArea>


friendChat::friendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendChat)
{
    ui->setupUi(this);

    setFixedSize(250,410);
    //先统计在线人数,在定义出在线人数的名字
    online on;
    on.getOnlinePersor();
    showOnlineNumber(on.onlinePersor);
    on.getTotalCnt();
    showOnlineNum(on.totalCnt,on.onlinePersor.size());
}

friendChat::~friendChat()
{
    delete ui;
}

void friendChat::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
}

//点击相当于没动
void friendChat::on_friendBtn_clicked()
{

}

//跳转到groupchat界面
void friendChat::on_groupBtn_clicked()
{
    groupchat *g=new groupchat();
    g->show();
    this->hide();
}

//跳转到addfriend界面
void friendChat::on_addFriendBtn_clicked()
{
    addfrient *a=new addfrient();
    a->show();
    this->hide();
}

//跳转到creatgroup界面
void friendChat::on_creatGroupBtn_clicked()
{
    creatGroup *c=new creatGroup();
    c->show();
    this->hide();
}

//跳转到好友请求界面
void friendChat::on_applyBtn_clicked()
{
    addApply *ap=new addApply();
    ap->show();
    this->hide();
}

//打印在线人数和总人数
void friendChat::showOnlineNum(int total,int online)
{
    QString str=QString("%1/%2").arg(online).arg(total);
    ui->numShowBtn->setText(str);
}

//显示在线的成员
void friendChat::showOnlineNumber(QVector<QString> &onlineperson)
{
    for(int i=0;i<onlineperson.size();i++)
    {

        QToolButton *btn=new QToolButton;
        btn->setText(onlineperson[i]);
        btn->setIcon(QPixmap(":/picture/11.gif"));
        btn->setIconSize(QSize(30,30));
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置按钮风格，同时显示文字和图标
        //将按钮添加到listWidget中的方法
        QListWidgetItem *item =new QListWidgetItem();
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,btn);
    }
}
