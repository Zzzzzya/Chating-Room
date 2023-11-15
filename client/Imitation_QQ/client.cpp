#include "client.h"

Client::Client(QWidget *parent)
    : QMainWindow{parent}
{
    // 创建QTcpSocket对象
    socket = new QTcpSocket(this);

    // 连接readyRead信号到readMessage槽
    connect(socket, &QTcpSocket::readyRead, this, &Client::readMessage);

    // 连接connected信号到connected槽
    connect(socket, &QTcpSocket::connected, this, &Client::connected);

    // 连接disconnected信号到disconnected槽
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);

    // 连接error信号到匿名槽函数，该槽函数发送errorOccurred信号
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(errorOccurred(QAbstractSocket::SocketError)));

}

Client::~Client()
{
    delete socket;
}

void Client::connectToServer(const QString &serverAddress, quint16 port)
{

}

void Client::sendMessage(const QString &message)
{

}

void Client::disconnectFromServer()
{

}

void Client::readMessage()
{

}



