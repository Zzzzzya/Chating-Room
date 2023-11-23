#include "signalchating.h"
#include "ui_signalchating.h"
#include<QColorDialog>
#include "friendchat.h"

signalChating::signalChating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signalChating)
{
    ui->setupUi(this);
    setFixedSize(730,450);
    // 创建数据库连接对象
    db = QSqlDatabase::addDatabase("ithema");
    db.setHostName("localhost"); // 设置主机名
    db.setPort(8088); // 设置端口号
    db.setDatabaseName("chat"); // 设置数据库名
    db.setUserName("root"); // 设置用户名
    db.setPassword("123456"); // 设置密码

    // 创建TCP通信对象
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.100", 8888); // 连接到目标主机，这里的IP和端口需要根据你的实际情况修改
}
}

signalChating::~signalChating()
{
    delete ui;
}

void signalChating::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setCurrentFont(f);
    ui->textEdit->setFocus();
}

void signalChating::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->textEdit->setFontPointSize(arg1.toDouble());
    ui->textEdit->setFocus();
}


void signalChating::on_boldBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    ui->textEdit->setFocus();
}


void signalChating::on_slopeBtn_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}


void signalChating::on_underlineBtn_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}


void signalChating::on_setColorBtn_clicked()
{
    color=QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

void signalChating::on_preserveBtn_clicked()
{
    // 保存聊天信息到数据库
    QString message = ui->messageEdit->toPlainText(); // 获取聊天信息
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间
    QString sql = QString("insert into chat_record (message, time) values ('%1', '%2')").arg(message).arg(time);  //sql语法建立
    if (db.open()) { // 建立连接
        QSqlQuery query;
        if (query.exec(sql)) { // 执行SQL语句
            qDebug() << "保存聊天信息成功";
        }
        else {
            qDebug() << "保存聊天信息失败：" << query.lastError().text();
        }
        db.close(); // 关闭数据库连接
    }
    else {
        qDebug() << "打开数据库失败：" << db.lastError().text();
    }
}


void signalChating::on_clearBtn_clicked()
{
    ui->textBrowser->clear();
}

//要用到socket
void signalChating::on_sendBtn_clicked()
{
    // 将信息发送出去
    QString message = ui->messageEdit->toPlainText(); // 获取聊天信息
    socket->write(message);
    socket->flush(); // 确保信息发送完毕
    qDebug() << "发送信息成功";
}

void signalChating::on_exitBtn_clicked()
{
//    friendChat *f=new friendChat();
//    f->show();
    this->hide();
}

