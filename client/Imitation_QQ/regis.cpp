#include "regis.h"
#include "mainwindow.h"
#include "ui_regis.h"
#include "client.h"
#include <QString>
#include <QMessageBox>

regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    this->setWindowTitle("注册");
    ui->password->setMaxLength(12);
    ui->password_c->setMaxLength(12);
}

regis::~regis()
{
    delete ui;
}

// 跳转回mainwindow界面
void regis::on_btn_register_clicked()
{
    QString str = ui->password->text();
    QString str_c = ui->password_c->text();
    int e = QString::compare(str,str_c);
    if(e != 0){
        QMessageBox::about(this,"错误","两次输入的密码不一致");
        return;
    }

    if(str.length() < 6 || str_c.length() < 6){
        QMessageBox::about(this,"错误","密码应至少为 6 位!");
        return;
    }
    MainWindow *m = new MainWindow();
    m->show();
    this->hide();
}

