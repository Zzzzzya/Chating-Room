#include "signalChating.h"
#include "ui_signalChating.h"

signalChating::signalChating(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signalChating)
{
    ui->setupUi(this);

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

signalChating::~signalChating()
{
    delete ui;
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
        } else {
            qDebug() << "保存聊天信息失败：" << query.lastError().text();
        }
        db.close(); // 关闭数据库连接
    } else {
        qDebug() << "打开数据库失败：" << db.lastError().text();
    }
}

void signalChating::on_sendBtn_clicked()
{
    // 将信息发送出去
    QString message = ui->messageEdit->toPlainText(); // 获取聊天信息
    socket->write(message);
    socket->flush(); // 确保信息发送完毕
    qDebug() << "发送信息成功";
}
void signalChating ::closeDb(void)
{
    db.close();
}
