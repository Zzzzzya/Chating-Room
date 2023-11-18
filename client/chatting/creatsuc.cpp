#include "creatsuc.h"
#include "ui_creatsuc.h"
#include "groupchat.h"

creatSuc::creatSuc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::creatSuc)
{
    ui->setupUi(this);
}

creatSuc::~creatSuc()
{
    delete ui;
}

//跳转到groupchat界面
void creatSuc::on_backBtn_clicked()
{
    groupchat *g=new groupchat();
    g->show();
    this->hide();
}

