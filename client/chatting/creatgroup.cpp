#include "creatgroup.h"
#include "ui_creatgroup.h"
#include "groupchat.h"

creatGroup::creatGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creatGroup)
{
    ui->setupUi(this);
    setWindowTitle("创建群聊");
    setFixedSize(250,350);
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

