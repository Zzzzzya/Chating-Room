#include "new_friend.h"
#include "login.h"
#include "l_friend.h"
#include "ui_new_friend.h"

New_friend::New_friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::New_friend)
{
    ui->setupUi(this);
    this->setWindowTitle("好友申请");
}

New_friend::~New_friend()
{
    delete ui;
}

void New_friend::on_btn_back_clicked()
{
    login *l = new login();
    l->show();
    this->hide();
}


void New_friend::on_btn_reject_clicked()
{
    login *l = new login();
    l->show();
    this->hide();
}


void New_friend::on_btn_accept_clicked()
{
    L_friend *lf = new L_friend();
    lf->show();
    this->hide();
}

