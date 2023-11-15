#include "l_friend.h"
#include "l_group.h"
#include "add_friend.h"
#include "set_group.h"
#include "new_friend.h"
#include "ui_l_friend.h"

L_friend::L_friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::L_friend)
{
    ui->setupUi(this);
    this->setWindowTitle("好友");
}

L_friend::~L_friend()
{
    delete ui;
}

void L_friend::on_btn_group_clicked()
{
    L_group *lg = new L_group();
    lg->show();
    this->hide();
}


void L_friend::on_btn_addfriend_clicked()
{
    Add_friend *af = new Add_friend();
    af->show();
    this->hide();
}


void L_friend::on_btn_setgroup_clicked()
{
    Set_group *sg = new Set_group();
    sg->show();
    this->hide();
}


void L_friend::on_btn_apfriend_clicked()
{
    New_friend *nf = new New_friend();
    nf->show();
    this->hide();
}

