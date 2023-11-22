#include "mysocket.h"


MySocket::MySocket(QObject *parent) : QObject(parent)
{
    WSADATA data;           // 网络环境初始化
    int ret = WSAStartup(MAKEWORD(2,2), &data);
    if (ret != 0) {
        qDebug() << "初始化网络错误！";
        return;
    }else{
        qDebug() << "初始化网络成功！";
    }

    ret = socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        qDebug() << "创建套接字失败！";
        return;
    }

    // 连接信号和槽
    connect(this, &MySocket::registration_Response, this, &MySocket::registerResponse);
    connect(this, &MySocket::login_Response, this, &MySocket::loginResponse);
    connect(this, &MySocket::addFriend_Response, this, &MySocket::addFriendResponse);
    connect(this, &MySocket::deleteFriend_Response, this, &MySocket::deleteFriendResponse);
    connect(this, &MySocket::friendRequest_Response, this, &MySocket::friendRequestResponse);
    connect(this, &MySocket::friendMessage_Response, this, &MySocket::friendMessageResponse);
    connect(this, &MySocket::groupCreate_Response, this, &MySocket::groupCreateReponse);
    connect(this, &MySocket::joinGroup_Response, this, &MySocket::joinGroupReponse);
    connect(this, &MySocket::leaveGroup_Response, this, &MySocket::leaveGroupReponse);
    connect(this, &MySocket::friendListReceived, this, &MySocket::getFriendListResponse);
    connect(this, &MySocket::groupListReceived, this, &MySocket::getGroupListResponse);
    connect(this, &MySocket::groupMessage_Response, this, &MySocket::groupMessageResponse);

}

MySocket::~MySocket()           // 析构，释放资源
{
    disconnectFromServer();
    disconnect();               // 断开对象的所有连接
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

QJsonObject &MySocket::receiveMessageFromServer()
{
    buffer.clear(); // 清空缓存区
    int ret = recv(socketfd, buffer.data(), buffer.size(), 0);
    if (ret == SOCKET_ERROR) {
            int error = WSAGetLastError();
            qDebug() << "接收失败: " << error;

            // 返回一个空的QJsonObject对象
            static QJsonObject emptyObject;
            return emptyObject;
    }

    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    if (doc.isNull()) {
            qDebug() << "解析JSON失败";

            // 返回一个空的QJsonObject对象
            static QJsonObject emptyObject;
            return emptyObject;
    }

    // 返回解析得到的JSON对象
    static QJsonObject jsonObject = doc.object();
    return jsonObject;
}

bool MySocket::connectToServer()
{
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8000);
    serv_addr.sin_addr.S_un.S_addr = inet_addr("111.229.188.220");
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
    // 发送信号以调用服务器响应函数
    emit registration_Response();
}

void MySocket::registerResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["register"].toString();
    bool success = jsonObject["success"].toBool();

    if(success == true){
        qDebug() << "注册请求成功！";
    }else{
        qDebug() << "注册请求无效！";
    }

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
    // 发送信号以调用服务器响应函数
    emit login_Response();
}

void MySocket::loginResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["login"].toString();
    bool success = jsonObject["success"].toBool();

    if(success == true){
        qDebug() << "登录请求成功！";
    }else{
        qDebug() << "登录请求无效！";
    }

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
    // 发送信号以调用服务器响应函数
    emit friendListReceived();
}

void MySocket::getFriendListResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();
    QJsonArray message = jsonObject["message"].toArray();

    if (success == true)
    {
        emit friendListUpdated(message); // 将传回的好友列表作为参数传递
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
    // 发送信号以调用服务器响应函数
    emit addFriend_Response();
}

void MySocket::addFriendResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit deleteFriend_Response();
}

void MySocket::deleteFriendResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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

}

void MySocket::sendFriendRequest(const QString &friend_account)
{
    // content的内容
    QJsonObject sendfriendContent;
    sendfriendContent["friend_account"] = friend_account;
    sendfriendContent["time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); // 获取当前时间

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "apply_friend";
    messageObject["content"] = sendfriendContent;

    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
    // 发送信号以调用服务器响应函数
    emit friendRequest_Response();
}

void MySocket::friendRequestResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit friendMessage_Response();
}

void MySocket::friendMessageResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit groupListReceived();
}

void MySocket::getGroupListResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();
    QJsonArray message = jsonObject["message"].toArray();

    if (success == true) {

        emit groupListUpdated(message);
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
    // 发送信号以调用服务器响应函数
    emit groupCreate_Response();
}

void MySocket::groupCreateReponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit joinGroup_Response();
}

void MySocket::joinGroupReponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit leaveGroup_Response();
}

void MySocket::leaveGroupReponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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
    // 发送信号以调用服务器响应函数
    emit groupMessage_Response();
}

void MySocket::groupMessageResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

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

}

