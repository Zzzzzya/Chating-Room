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
    clickedName(on.allPersor.size());
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
    for(int i=0;i<selectedItem.size();i++)
    {
        this->choosedName.push_back(selectedItem[i]->text());
    }
    craetGroupName *c=new craetGroupName(nullptr,this->choosedName);
    c->show();
    this->hide();
}

//显示在线人信息
void creatGroup::showMessage(QVector<QString> &allPersor)
{
    for(int i=0;i<allPersor.size();i++)
    {
        ui->listWidget->setIconSize(QSize(30,30));
        QListWidgetItem *item =new QListWidgetItem(QPixmap(":/picture/11.gif"),allPersor[i]);
        item->setSizeHint(QSize(250,40));
        ui->listWidget->addItem(item);
    }
}

//显示在线人数
void creatGroup::showNum(int cnt)
{
    QString str=QString("%1").arg(cnt);
    ui->numShowBtn->setText(str);
}

void creatGroup::clickedName(int cnt)
{
    connect(ui->listWidget,&QListWidget::itemSelectionChanged,this,[=]()
    {
        QListWidgetItem* item=ui->listWidget->currentItem();
        bool ret=true;
        for(QVector<QListWidgetItem*>::const_iterator it = selectedItem.begin(); it != selectedItem.end(); it++)
        {
            if(*it==item)
            {
                this->selectedItem.erase(it);
                ret=false;
                break;
            }
        }
        if(ret)
        {
            selectedItem.push_back(item);
        }
    });
}

