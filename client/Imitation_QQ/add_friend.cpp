#include "add_friend.h"
#include "login.h"
#include <QMessageBox>
#include "ui_add_friend.h"

Add_friend::Add_friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_friend)
{
    ui->setupUi(this);
    this->setWindowTitle("添加好友");
}

Add_friend::~Add_friend()
{
    delete ui;
}

void Add_friend::on_pushButton_2_clicked()
{
    login *l = new login();
    l->show();
    this->hide();
}


void Add_friend::on_pushButton_clicked()
{
    login *l = new login();
    l->show();
    this->hide();
}


void Add_friend::on_btn_berify_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("发送成功！");
    msgBox.exec();
}

