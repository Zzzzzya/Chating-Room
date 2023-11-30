#include "craetgroupname.h"
#include "ui_craetgroupname.h"
#include "creatsuc.h"
#include"mysocket.h"
#include "usersql.h"

extern MySocket *mysocket;
extern UserSql *user;

craetGroupName::craetGroupName(QWidget *parent, QStringList name) :
    QWidget(parent),
    ui(new Ui::craetGroupName)
{
    ui->setupUi(this);
    this->choosedName=name;
    qDebug()<<this->choosedName.size();
    setWindowTitle("群昵称");
    connect(this, &craetGroupName::confirmBtnClicked, mysocket, &MySocket::createGroup);
}

craetGroupName::~craetGroupName()
{
    delete ui;
}

void craetGroupName::on_confirmBtn_clicked()
{
    emit confirmBtnClicked(user->userName,ui->lineEdit->text(),choosedName);
    creatSuc *cr=new creatSuc();
    cr->show();
    this->hide();
}

