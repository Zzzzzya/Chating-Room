#include "mainwindow.h"
#include "regis.h"
#include "login.h"
#include "client.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    ui->password->setMaxLength(12);
    ui->password->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 跳转到login界面
void MainWindow::on_btn_login_clicked()
{
    QString str = ui->password->text();

    if(str.length() < 6){
        QMessageBox::about(this,"错误","密码应至少为 6 位!");
        return;
    }
    login *l = new login();
    l->show();
    this->hide();
}

// 跳转到register界面
void MainWindow::on_btn_register_clicked()
{
    regis *r = new regis();
    r->show();
    this->hide();
}

// 显示密码
void MainWindow::on_cbtn_showpwd_clicked(bool checked)
{
    if(checked){
        // 显示密码
        ui->password->setEchoMode(QLineEdit::Normal);
    }else{
        // 密文
        ui->password->setEchoMode(QLineEdit::Password);
    }
}

