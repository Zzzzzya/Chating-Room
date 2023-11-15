#include "set_group.h"
#include "login.h"
#include <QMessageBox>
#include "ui_set_group.h"

Set_group::Set_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_group)
{
    ui->setupUi(this);
    this->setWindowTitle("建立群聊");
}

Set_group::~Set_group()
{
    delete ui;
}

void Set_group::on_btn_group_clicked()
{
    login *l = new login();
    l->show();
    this->hide();
}

void Set_group::on_btn_setgroup_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("建立群聊成功！");
    msgBox.exec();
}

