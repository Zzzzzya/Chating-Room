#include "mainwindow.h"
#include "regis.h"
#include "login.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 跳转到login界面
void MainWindow::on_btn_login_clicked()
{
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

