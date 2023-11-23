#include "creatgroup.h"
#include "ui_creatgroup.h"
#include "groupchat.h"
#include"online.h"
#include<QCheckBox>
#include "craetgroupname.h"

creatGroup::creatGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creatGroup)
{
    ui->setupUi(this);
    setWindowTitle("创建群聊");
    setFixedSize(250,350);
    online on;
    on.getAllPerson();
    showMessage(on.allPersor);
    showNum(on.allPersor.size());
    clickedName();
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
    for(int i=0;i<this->selectedItem.size();i++)
    {
        this->choosedName.push_back(this->selectedItem[i]->text());
    }
    craetGroupName *c=new craetGroupName();
    c->show();
    this->hide();
}

//显示在线人信息
void creatGroup::showMessage(QVector<QString> &allPersor)
{
    for(int i=0;i<allPersor.size();i++)
    {
        for(int i=0;i<allPersor.size();i++)
        {
            ui->listWidget->setIconSize(QSize(30,30));
            QListWidgetItem *item =new QListWidgetItem(QPixmap(":/picture/11.gif"),allPersor[i]);
            item->setSizeHint(QSize(250,40));
            ui->listWidget->addItem(item);
        }
    }
}

//显示在线人数
void creatGroup::showNum(int cnt)
{
    QString str=QString("%1").arg(cnt);
    ui->numShowBtn->setText(str);
}

void creatGroup::clickedName()
{
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,this,[=]()
    {
        this->selectedItem.push_back(ui->listWidget->currentItem());
        qDebug()<<6;
    });
}

