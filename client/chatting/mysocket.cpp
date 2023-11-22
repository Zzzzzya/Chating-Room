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

    ret = socketfd = socket(AF_INET, SOCK_STREAM, 0);
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

void MySocket::registerResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["register"].toString();
    bool success = jsonObject["success"].toBool();

    if(success == true){
        qDebug() << "注册请求成功！";
    }else{
        qDebug() << "注册请求无效！";
    }

    emit registrationResponse(success);
}

void MySocket::loginIn(const QString &username, const QString &password)
{
    this->m_username = username;
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

void MySocket::loginResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["login"].toString();
    bool success = jsonObject["success"].toBool();

    if(success == true){
        qDebug() << "登录请求成功！";
    }else{
        qDebug() << "登录请求无效！";
    }

    emit loginInResponse(success);
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

void MySocket::getFriendListResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();
    QJsonArray message = jsonObject["message"].toArray();

    if (success == true)
    {
        QList<QString> friendNames;

        for (const QJsonValue& friendValue : message) {
            QString friendName = friendValue.toString();
            friendNames.append(friendName);
        }

        // 发射信号，将好友列表信息传递给 UI
        emit friendListReceived(friendNames);
    }
    else
    {
        qDebug() << "获取好友列表失败!";
    }
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

void MySocket::addFriendResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "添加好友成功!";

        // 请求最新的好友列表
        requestFriendList(this->m_username);
    }
    else
    {
        qDebug() << "添加好友失败! ";
    }

    // 发射添加好友响应信号，将添加结果传递给 UI
    emit addFriendResponse(success);
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

void MySocket::deleteFriendResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "删除好友成功!";

        // 请求最新的好友列表
        requestFriendList(this->m_username);
    }
    else
    {
        qDebug() << "删除好友失败! ";
    }

    // 发射删除好友响应信号，将添加结果传递给 UI
    emit deleteFriendResponse(success);
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

void MySocket::friendRequestResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "申请好友成功!";
    }
    else
    {
        qDebug() << "申请好友失败! ";
    }

    // 发射请求好友响应信号
    emit friendRequestResponse(success);
}

void MySocket::sendFriendMessage(const QString &username, const QString &friendUsername, const QString &content)
{
    // content的内容
    QJsonObject messageContent;
    messageContent["sendername"] = username;
    messageContent["recipientname"] = friendUsername;
    messageContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间
    messageContent["data"] = content;

    QJsonObject messageObject;
    messageObject["type"] = "message";
    messageObject["subtype"] = "text";
    messageObject["content"] = messageContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
}

void MySocket::FriendMessageResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "消息发送成功!";
    }
    else
    {
        qDebug() << "消息发送失败! ";
    }

    // 发射好友消息响应信号
    emit friendMessageResponse(success);
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

void MySocket::getGroupListResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();
    QJsonArray message = jsonObject["message"].toArray();

    if (success == true) {
        QList<QString> groupNames;

        for (const QJsonValue& group : message) {
            QString groupName = group.toString();
            groupNames.append(groupName);
        }

        emit groupListReceived(groupNames);
    }else{
        qDebug() << "获取群组列表失败!";

    }

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

void MySocket::groupCreateReponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "创建群聊成功!";

        // 请求最新的群聊列表
        requestGroupList(this->m_username);
    }
    else
    {
        qDebug() << "创建群聊失败! ";
    }

    // 发射创建群聊响应信号
    emit groupCreateReponse(success);
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

void MySocket::joinGroupReponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "加入群聊成功!";

        // 请求最新的群聊列表
        requestGroupList(this->m_username);
    }
    else
    {
        qDebug() << "加入群聊失败! ";
    }

    // 发射加入群聊响应信号
    emit joinGroupReponse(success);
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

void MySocket::leaveGroupReponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "退出群聊成功!";

        // 请求最新的群聊列表
        requestGroupList(this->m_username);
    }
    else
    {
        qDebug() << "退出群聊失败! ";
    }

    // 发射退出群聊响应信号
    emit leaveGroupReponse(success);
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

void MySocket::groupMessageResponse(const QJsonObject &jsonObject)
{
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success == true)
    {
        qDebug() << "消息发送成功!";
    }
    else
    {
        qDebug() << "消息发送失败! ";
    }

    // 发射好友消息响应信号
    emit groupMessageResponse(success);
}





