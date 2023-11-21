#include "craetgroupname.h"
#include "ui_craetgroupname.h"
#include "creatsuc.h"

craetGroupName::craetGroupName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::craetGroupName)
{
    ui->setupUi(this);
    setWindowTitle("群昵称");
}

craetGroupName::~craetGroupName()
{
    delete ui;
}

void craetGroupName::on_confirmBtn_clicked()
{
    //将群昵称保存到数据库
    creatSuc *cr=new creatSuc();
    cr->show();
    this->hide();
}

