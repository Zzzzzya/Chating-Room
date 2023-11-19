#include "groupchat.h"
#include "ui_groupchat.h"
#include "friendchat.h"
#include "addfrient.h"
#include "creatgroup.h"
#include "addapply.h"
#include "online.h"
#include<QToolButton>
#include<QVBoxLayout>

groupchat::groupchat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupchat)
{
    ui->setupUi(this);
    setFixedSize(250,410);
    online on;
    on.getgroupName();
    showOnlineNumber(on.groupName);
    showOnlineNum(on.groupName.size());
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
    for(int i=0;i<group_name.size();i++)
    {

        QToolButton *btn=new QToolButton;
        //btn->setFixedSize(250,40);
        btn->setText(group_name[i]);
        btn->setIcon(QPixmap(":/picture/11.gif"));
        btn->setIconSize(QSize(30,30));
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置按钮风格，同时显示文字和图标
        //将按钮添加到listWidget中的方法
        QListWidgetItem *item =new QListWidgetItem();
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,btn);

    }

}





