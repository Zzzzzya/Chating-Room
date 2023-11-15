#include "regis.h"
#include "mainwindow.h"
#include "ui_regis.h"

regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
}

regis::~regis()
{
    delete ui;
}

// 跳转回mainwindow界面
void regis::on_btn_register_clicked()
{
    MainWindow *m = new MainWindow();
    m->show();
    this->hide();
}

