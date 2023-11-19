#include "login.h"
#include "client.h"
#include "l_friend.h"
#include "l_group.h"
#include "mainwindow.h"
#include "add_friend.h"
#include "set_group.h"
#include "new_friend.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle(" ");
}

login::~login()
{
    delete ui;
}

void login::on_btn_group_clicked()
{
    L_group *lg = new L_group();
    lg->show();
    this->hide();
}


void login::on_btn_friend_clicked()
{
    L_friend *lf = new L_friend();
    lf->show();
    this->hide();
}


void login::on_btn_addfriend_clicked()
{
    Add_friend *af = new Add_friend();
    af->show();
    this->hide();
}


void login::on_btn_setgroup_clicked()
{
    Set_group *sg = new Set_group();
    sg->show();
    this->hide();
}


void login::on_btn_apfriend_clicked()
{
    New_friend *nf = new New_friend();
    nf->show();
    this->hide();
}


void login::on_btn_logout_clicked()
{
    MainWindow *mw = new MainWindow();
    mw->show();
    this->hide();
}

