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
#include "signalchating.h"

//QList<QListWidgetItem *>vQListWidgetItem;

friendChat::friendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendChat)
{
    ui->setupUi(this);
    setWindowTitle("好友");
    setFixedSize(250,410);
    //获取数有关据库信息
    online on;
    on.getOnlinePersor();
    showOnlineNumber(on.onlinePersor);
    on.getTotalCnt();
    showOnlineNum(on.totalCnt,on.onlinePersor.size());
    showSignalChatting();
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

//点击相当于没动,不用实现
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
        ui->listWidget->setIconSize(QSize(30,30));
        QListWidgetItem *item =new QListWidgetItem(QPixmap(":/picture/11.gif"),onlineperson[i]);
        item->setSizeHint(QSize(250,40));
        ui->listWidget->addItem(item);
//        vQListWidgetItem.push_back(item);
    }
}

void friendChat::showSignalChatting()
{
    connect(ui->listWidget,&QListWidget::itemPressed,this,[=]()
    {
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();
        signalChating *s=new signalChating();
        s->setWindowIcon(selectedItem->icon());
        s->setWindowTitle(selectedItem->text());
        s->show();
    });
}

//vQListWidgetItem[i]->setSizeHint(QSize(vQListWidgetItem[i]->sizeHint().width(), 250));
//vQListWidgetItem[i]->setSizeHint(QSize(vQListWidgetItem[i]->sizeHint().height(), 40));
//QRect ret=ui->listWidget->visualItemRect(vQListWidgetItem[i]);
//QString str=QString("x = %1 y = %2 width = %3 height = %4").arg(ret.x()).arg(ret.y()).arg(width()).arg(height());
//qDebug()<<str;
