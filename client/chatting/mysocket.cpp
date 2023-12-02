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
    connect(this, &MySocket::friendApply_Response, this, &MySocket::friendApplyResponse);
    connect(this, &MySocket::friendMessage_Response, this, &MySocket::friendMessageResponse);
    connect(this, &MySocket::groupCreate_Response, this, &MySocket::groupCreateReponse);
    connect(this, &MySocket::joinGroup_Response, this, &MySocket::joinGroupReponse);
    connect(this, &MySocket::leaveGroup_Response, this, &MySocket::leaveGroupReponse);    
    connect(this, &MySocket::friendListReceived, this, &MySocket::getFriendListResponse);
    connect(this, &MySocket::groupListReceived, this, &MySocket::getGroupListResponse);
    connect(this, &MySocket::groupMembersCountReceived, this, &MySocket::getGroupMemberCountResponse);
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

    // 如果发送成功，则尝试接收服务器的响应
    QJsonObject response = receiveMessageFromServer();
    if (response.isEmpty()) {
        // 处理接收消息失败的情况
        qDebug() << "接收服务器响应失败";
        return false;
    }
    return true;
}

QJsonObject MySocket::receiveMessageFromServer()
{
    buffer.clear(); // 清空缓存区
    int ret = recv(socketfd, buffer.data(), buffer.size(), 0);
    if (ret == SOCKET_ERROR) {
            int error = WSAGetLastError();
            qDebug() << "接收失败: " << error;

            // 返回一个动态分配的空的QJsonObject对象
            return QJsonObject();
    }else{
            qDebug() << "接收成功!";
            qDebug()<<buffer.size();
    }

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "解析JSON失败" << jsonError.errorString();

        // 返回一个动态分配的空的QJsonObject对象
        return QJsonObject();
    }

    // 返回解析得到的JSON对象
    return doc.object();
}

bool MySocket::connectToServer()
{
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.S_un.S_addr = inet_addr("192.168.21.1");
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
    this->m_username = username;
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
    const QJsonObject& jsonObject = receiveMessageFromServer();     // 从服务器接收到的数据

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    // 需要展现在ui上的数据
    QJsonArray message = jsonObject["message"].toArray();
    // 确保成功获取且数组中有好友信息的成对出现
    if (success && (message.size() % 2 == 0))
    {
        QList<QPair<QString, int>> friendList; //
        for (int i = 0; i < message.size(); ++i) {
            // message的每个元素又都是一个QJsonObject
            QJsonObject friendInfo = message[i].toObject();

            QString friendName = friendInfo["name"].toString();
            int isOnline = friendInfo["isOnline"].toInt();

            // 存储好友信息
            friendList.append(qMakePair(friendName, isOnline));
        }

        // 发送更新后的好友列表信号
        emit friendListUpdated(friendList);
    }
    else
    {
        qDebug() << "获取好友列表失败!";
    }
}

// 添加好友而非申请好友
void MySocket::addFriend(const QString& username, const QString &friendUsername)
{
    // content的内容
    QJsonObject friendContent;
    friendContent["username"] = username;
    friendContent["friend_username"] = friendUsername;

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

void MySocket::sendFriendRequest(const QString &my_name, const QString &friend_account)
{
    // content的内容
    QJsonObject sendfriendContent;
    sendfriendContent["applicant"] = my_name;
    sendfriendContent["friend_account"] = friend_account;

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

void MySocket::requestFriendApplication(const QString &my_name)
{
    QJsonObject requestContent;
    requestContent["username"] = my_name;       // 请求好友列表的人

    QJsonObject messageObject;
    messageObject["type"] = "request";
    messageObject["subtype"] = "friend_Apply_request";
    messageObject["content"] = requestContent;

    // 将消息对象转为JSON文档
    QJsonDocument doc(messageObject);

    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());

    // 发送信号以调用服务器响应函数
    emit friendApply_Response();
}

void MySocket::friendApplyResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();

    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    if (success)
    {
        // 如果处理成功，获取好友申请列表
        QJsonArray friendApply = jsonObject["friend_Apply_List"].toArray();

        // 发送信号将好友申请列表传递给UI
        emit friendApplyReceived(friendApply);
    }
    else
    {
        qDebug() << "好友申请处理失败! ";
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

void MySocket::requestGroupMemberCount(const QString &groupName)
{
    QJsonObject requestObject;
    requestObject["type"] = "request";
    requestObject["subtype"] = "get_groupMembers_count";

    // 创建 content 对象并添加 groupName 字段
    QJsonObject contentObject;
    contentObject["groupName"] = groupName;
    requestObject["content"] = contentObject;

    QJsonDocument doc(contentObject);
    // 发送消息到服务器
    sendMessagetoServer(doc.toJson());
    // 发送信号以调用服务器响应函数
    emit groupMembersCountReceived();
}

void MySocket::getGroupMemberCountResponse()
{
    const QJsonObject& jsonObject = receiveMessageFromServer();
    QString type = jsonObject["type"].toString();
    QString subtype = jsonObject["subtype"].toString();
    bool success = jsonObject["success"].toBool();

    // 获取包含成员信息的 JSON 对象
    QJsonObject message = jsonObject["message"].toObject();

    if (success)
    {
        // 发送信号，将包含成员信息的 JSON 对象作为参数传递
        emit groupMembersCountUpdated(message);
    }
    else
    {
        qDebug() << "获取群成员列表失败!";
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

void MySocket::joinGroup(const QString &groupname, const QString &username)
{
    // content的内容
    QJsonObject GroupjoinContent;
    GroupjoinContent["username"] = username;
    GroupjoinContent["groupname"] = groupname;

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

void MySocket::leaveGroup(const QString &groupname, const QString &username)
{
    // content的内容
    QJsonObject GroupleaveContent;
    GroupleaveContent["username"] = username;
    GroupleaveContent["groupname"] = groupname;

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

void MySocket::sendGroupMessage(const QString &groupname, const QString &sender, const QString &content)
{
    // content的内容
    QJsonObject messageContent;
    messageContent["sender"] = sender;
    messageContent["groupname"] = groupname;
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

void MySocket::processServerMessage(const QJsonObject &message)
{
    QString type = message["type"].toString();
    QString subtype = message["subtype"].toString();

    if (type == "message" && subtype == "text") {
        QJsonObject content = message["content"].toObject();
        QString data = content["data"].toString();

        // 发送信号通知界面显示消息
        emit chatMessageReceived(data);
    }
    if(type == "message" && subtype == "group_message"){
        QJsonObject content = message["content"].toObject();
        QString data = content["data"].toString();

        emit groupMessageReceived(data);
    }
}

