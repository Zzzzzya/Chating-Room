#include "friendchat.h"
#include "ui_friendchat.h"
#include<QPainter>
#include "groupchat.h"
#include "addfrient.h"
#include "creatgroup.h"
#include "addapply.h"
#include<QToolButton>
#include<QDebug>
#include<QListWidget>
#include <QScrollArea>
#include "signalchating.h"
#include"mysocket.h"
#include "usersql.h"


extern MySocket *mysocket;
extern UserSql *user;

friendChat::friendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendChat)
{
    ui->setupUi(this);
    setWindowTitle("好友");
    setFixedSize(250,410);
    mysocket->requestFriendList(user->userName);
    //获取数有关据库信息
    connect(mysocket,&MySocket::friendListUpdated,this,&friendChat::updateFriendListWidget);
    showOnlineNumber(user->userFriend,user->friendIsOnline);
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

void friendChat::updateFriendListWidget(QList<QPair<QString, int>> friendList)
{
    // 先清空 QListWidget
    ui->friendListWidget->clear();

    // 遍历 friendList，并将其中的好友信息添加到 QListWidget 中
    for (const auto& friendInfo : friendList) {
        QString friendName = friendInfo.first;
        int isOnline = friendInfo.second;

        // 根据在线状态，设置显示的文本
        QString statusText = (isOnline == 1) ? "在线" : "离线";

        // 创建 QListWidgetItem 并设置显示文本
        QListWidgetItem* item = new QListWidgetItem(friendName + " - " + statusText);

        // 将 item 添加到 QListWidget 中
        ui->friendListWidget->addItem(item);
    }
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

//显示在线的成员以及在线人数
void friendChat::showOnlineNumber(QVector<QString> &userFriend,QVector<int>&friendIsOnline)
{
    int cnt=0;
    for(int i=0;i<userFriend.size();i++)
    {
        if(friendIsOnline[i]==1)
        {
            cnt++;
            ui->friendListWidget->setIconSize(QSize(30,30));
            QListWidgetItem *item =new QListWidgetItem(QPixmap(":/picture/11.gif"),userFriend[i]);
            item->setSizeHint(QSize(250,40));
            ui->friendListWidget->addItem(item);
        }
    }
    QString str=QString("%1/%2").arg(cnt).arg(userFriend.size());
    ui->numShowBtn->setText(str);
}

void friendChat::showSignalChatting()
{
    connect(ui->friendListWidget,&QListWidget::itemPressed,this,[=]()
    {
        QListWidgetItem *selectedItem = ui->friendListWidget->currentItem();
        signalChating *s=new signalChating(nullptr,selectedItem->text());
        s->setWindowIcon(selectedItem->icon());
        s->setWindowTitle(selectedItem->text());
        s->show();
    });
}
