#include "creatgroup.h"
#include "ui_creatgroup.h"
#include "groupchat.h"
#include"online.h"
#include<QCheckBox>

creatGroup::creatGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creatGroup)
{
    ui->setupUi(this);
    setWindowTitle("创建群聊");
    setFixedSize(250,350);
    online on;
    on.getOnlinePersor();
    showMessage(on.onlinePersor);
    showNum(on.onlinePersor.size());
}

creatGroup::~creatGroup()
{
    delete ui;
}

//跳转到groupchat界面
void creatGroup::on_backBtn_clicked()
{
    groupchat *g=new groupchat();
    g->show();
    this->hide();
}

//跳转到creatsuc界面&&将信息存到数据库
void creatGroup::on_creatBtn_clicked()
{
    groupchat *g=new groupchat();
    g->show();
    this->hide();
}

//显示在线人信息
void creatGroup::showMessage(QVector<QString> &onlineperson)
{
    for(int i=0;i<onlineperson.size();i++)
    {

        QCheckBox *btn=new QCheckBox(onlineperson[i]);
        //将按钮添加到listWidget中的方法
        QListWidgetItem *item =new QListWidgetItem();
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,btn);
    }
}

//显示在线人数
void creatGroup::showNum(int cnt)
{
    QString str=QString("%1").arg(cnt);
    ui->numShowBtn->setText(str);
}

