#include "groupchat.h"
#include "ui_groupchat.h"
#include "friendchat.h"
#include "addfrient.h"
#include "creatgroup.h"
#include "addapply.h"
#include "online.h"
#include<QToolButton>

groupchat::groupchat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupchat)
{
    ui->setupUi(this);
    setFixedSize(250,410);
    showOnlineNum(5);
    //先统计群数,在定义出群名称
    //int cnt=5;
    online on;
    on.getgroupName();
    showOnlineNumber(on.groupName);
}

groupchat::~groupchat()
{
    delete ui;
}

//跳转到friendchat界面
void groupchat::on_friendBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//没动
void groupchat::on_groupBtn_clicked()
{

}

//跳转到addfriend界面
void groupchat::on_addFriendBtn_clicked()
{
    addfrient *a=new addfrient();
    a->show();
    this->hide();
}

//跳转到creatgroup界面
void groupchat::on_creatGroupBtn_clicked()
{
    creatGroup *c=new creatGroup();
    c->show();
    this->hide();
}

//跳转到addapply界面
void groupchat::on_applyBtn_clicked()
{
    addApply *ap=new addApply();
    ap->show();
    this->hide();
}

//打印群在线人数
void groupchat::showOnlineNum(int total)
{
    QString str=QString("%1").arg(total);
    ui->numShowBtn->setText(str);
}

//打印群在线人信息
void groupchat::showOnlineNumber(QVector<QString> &group_name)
{
    QVector<QToolButton *>vToolBtn;
    for(int i=0;i<group_name.size();i++)
    {
        QToolButton *btn=new QToolButton;
        //名字
        btn->setText(group_name[i]);
        //图片加载
        //目前还没定义好
        btn->setAutoRaise(true);  //设置图片透明效果
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置按钮风格，同时显示文字和图标
    }
}




