#include "l_group.h"
#include "l_friend.h"

#include "mainwindow.h"
#include "add_friend.h"
#include "set_group.h"
#include "new_friend.h"
#include "ui_l_group.h"

L_group::L_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::L_group)
{
    ui->setupUi(this);
    this->setWindowTitle("群聊");
}

L_group::~L_group()
{
    delete ui;
}

void L_group::on_btn_friend_clicked()
{
    L_friend *lf = new L_friend();
    lf->show();
    this->hide();
}


void L_group::on_btn_addfriend_clicked()
{
    Add_friend *af = new Add_friend();
    af->show();
    this->hide();
}


void L_group::on_btn_setgroup_clicked()
{
    Set_group *sg = new Set_group();
    sg->show();
    this->hide();
}


void L_group::on_btn_apfriend_clicked()
{
    New_friend *nf = new New_friend();
    nf->show();
    this->hide();
}


void L_group::on_btn_logout_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->hide();
}

