#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>

class Client : public QMainWindow
{
    Q_OBJECT
public:
    // 构造函数和析构函数
    explicit Client(QWidget *parent = nullptr);
    ~Client();

// 用于响应与信号相关的事件
public slots:
    // 用于与服务器建立连接
    void connectToServer(const QString &serverAddress, quint16 port);

    // 用于向服务器发送消息
    void sendMessage(const QString &message);

    // 用于与服务器断开连接
    void disconnectFromServer();

private slots:
    // 用于从服务器读取传入消息
    void readMessage();


// 用于在特定事件发生时要发出的信号
signals:
    // 当客户端成功连接到服务器时发出
    void connected();

    // 当客户端与服务器断开连接时发出
    void disconnected();

    // 当从服务器接收到消息时发出
    void messageReceived(const QString &message);

    // 在通信过程中发生错误时发出
    void errorOccurred(const QString &errorString);


private:
    // TCP套接字
    QTcpSocket *socket;
};

#endif // CLIENT_H
