#include "groupchat.h"
#include "ui_groupchat.h"
#include "friendchat.h"
#include "addfrient.h"
#include "creatgroup.h"
#include "addapply.h"
#include "groupchatting.h"
#include"mysocket.h"
#include "usersql.h"

extern MySocket *mysocket;
extern UserSql *user;

groupchat::groupchat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupchat)
{
    ui->setupUi(this);
    setWindowTitle("群聊");
    setFixedSize(250,410);
    mysocket->requestGroupList(user->userName);
    //获取数有关据库信息
    connect(mysocket,&MySocket::groupListUpdated,this,&groupchat::getGroupMessage);
    showOnlineNumber(user->groupName);
}

groupchat::~groupchat()
{
    delete ui;
}

void groupchat::getGroupMessage(const QJsonArray &groupMessage)
{
    user->groupName.resize(groupMessage.size());
    for(int i=0;i<groupMessage.size();i++)
    {
        user->groupName[i]=groupMessage[i].toString();
    }
}

//跳转到friendchat界面
void groupchat::on_friendBtn_clicked()
{
    friendChat *f=new friendChat();
    f->show();
    this->hide();
}

//没动,不用实现
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

//打印群信息&&群个数
void groupchat::showOnlineNumber(QVector<QString> &groupName)
{
    QString str=QString("%1").arg(groupName.size());
    ui->numShowBtn->setText(str);
    for(int i=0;i<groupName.size();i++)
    {
        ui->listWidget->setIconSize(QSize(30,30));
        QListWidgetItem *item =new QListWidgetItem(QPixmap(":/picture/11.gif"),groupName[i]);
        item->setSizeHint(QSize(250,40));
        ui->listWidget->addItem(item);
    }
}

void groupchat::showGroupChatting()
{
    connect(ui->listWidget,&QListWidget::itemPressed,this,[=]()
    {
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();
        groupChatting *g=new groupChatting(nullptr,selectedItem->text());
        g->setWindowIcon(selectedItem->icon());
        g->setWindowTitle(selectedItem->text());
        g->show();
    });
}






