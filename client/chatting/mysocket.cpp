#include "mysocket.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDateTime>
MySocket::MySocket(QObject *parent) : QObject(parent)
{
    WSADATA data;           // 网络环境初始化
    int ret = WSAStartup(MAKEWORD(2,2), &data);
    if (ret != 0) {
        qDebug() << "初始化网络错误！";
        return;
    }

    ret = socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ret == -1) {
        qDebug() << "创建套接字失败！";
    }

}

MySocket::~MySocket()           // 析构，释放资源
{
    disconnectFromServer();
    // 清理网络环境：
    WSACleanup();
}

bool MySocket::sendMessagetoServer(const QByteArray& message)
{
    if(socketfd == INVALID_SOCKET)
    {
        qDebug() << "套接字未连接";
        return false;
    }

    int ret = send(socketfd, message.constData(), message.size(), 0);
    if(ret == SOCKET_ERROR){
        int error = WSAGetLastError();
        qDebug() << "发送失败: " << error;
            return false;
    }
    qDebug() << "发送成功！";
    return true;
}

bool MySocket::connectToServer(const char *serverAddress, int port)
{
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.S_un.S_addr = inet_addr(serverAddress);
    if (serv_addr.sin_addr.S_un.S_addr == INADDR_NONE) {
        qDebug() << "无效的IP地址";
        return false;
    }

    int ret = ::connect(socketfd, (sockaddr*)(&serv_addr), sizeof(serv_addr));
    if (ret == SOCKET_ERROR){
        int error = WSAGetLastError();
        qDebug() << "连接失败：" << error;
        return false;
    }

    qDebug() << "连接成功！";
    return true;
}

void MySocket::disconnectFromServer()
{
    if(socketfd != INVALID_SOCKET)
    {
        closesocket(socketfd);
        qDebug() << "成功与服务器断开连接。";
    }
}

void MySocket::registerUser(const QString &username, const QString &password)
{
/*
    QString message = QString("type : request subtype : register content : "
                              "username : %1 password : %2").arg(username).arg(password);
*/
    // content的内容
    QJsonObject registerContent;
    registerContent["username"] = username;
    registerContent["password"] = password;
    registerContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "register";
    messageObject["content"] = registerContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::loginIn(const QString &username, const QString &password)
{
    // content的内容
    QJsonObject loginContent;
    loginContent["username"] = username;
    loginContent["password"] = password;
    loginContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "login";
    messageObject["content"] = loginContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::requestFriendList(const QString &username)
{
    // content的内容
    QJsonObject friendListContent;
    friendListContent["username"] = username;
    friendListContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "get_friend_list";
    messageObject["content"] = friendListContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::addFriend(const QString& username, const QString &friendUsername)
{
    // content的内容
    QJsonObject friendContent;
    friendContent["username"] = username;
    friendContent["friend_username"] = friendUsername;
    friendContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "add_friend";
    messageObject["content"] = friendContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::deleteFriend(const QString &username, const QString &friendUsername)
{
    // content的内容
    QJsonObject delfriendContent;
    delfriendContent["username"] = username;
    delfriendContent["friend_username"] = friendUsername;
    delfriendContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "del_friend";
    messageObject["content"] = delfriendContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::sendFriendRequest(const QString &username, const QString &friendUsername, const QString &message)
{
    // content的内容
    QJsonObject sendfriendContent;
    sendfriendContent["username"] = username;
    sendfriendContent["friend_username"] = friendUsername;
    sendfriendContent["data"] = message;
    sendfriendContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "apply_friend";
    messageObject["content"] = sendfriendContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::sendFriendMessage(const QString &username, const QString &friendUsername, const QString &content)
{
    // content的内容
    QJsonObject messageContent;
    messageContent["username"] = username;
    messageContent["friendUsername"] = friendUsername;
    messageContent["data"] = content;

    QJsonObject messageObject;
    messageObject["type"] = "message";
    messageObject["subtype"] = "text";
    messageObject["content"] = messageContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::requestGroupList(const QString &username)
{
    // content的内容
    QJsonObject GroupListContent;
    GroupListContent["username"] = username;
    GroupListContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "get_group_list";
    messageObject["content"] = GroupListContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::createGroup(const QString &username, const QString &groupName, const QStringList &members)
{
    // content的内容
    QJsonObject contentObject;
    contentObject["username"] = username;
    contentObject["group_name"] = groupName;
    contentObject["members"] = QJsonArray::fromStringList(members);
    contentObject["time"] = QDateTime::currentDateTime().toString(Qt::ISODate); // Get current time

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "create_group";
    messageObject["content"] = contentObject;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::joinGroup(const QString &groupId, const QString &username)
{
    // content的内容
    QJsonObject GroupjoinContent;
    GroupjoinContent["username"] = username;
    GroupjoinContent["groupId"] = groupId;
    GroupjoinContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "join_group";
    messageObject["content"] = GroupjoinContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::leaveGroup(const QString &groupId, const QString &username)
{
    // content的内容
    QJsonObject GroupleaveContent;
    GroupleaveContent["username"] = username;
    GroupleaveContent["groupId"] = groupId;
    GroupleaveContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "leave_group";
    messageObject["content"] = GroupleaveContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::sendGroupMessage(const QString &groupId, const QString &sender, const QString &content)
{
    // content的内容
    QJsonObject messageContent;
    messageContent["sender"] = sender;
    messageContent["groupId"] = groupId;
    messageContent["data"] = content;
    messageContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "message";
    messageObject["subtype"] = "group_message";
    messageObject["content"] = messageContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}





