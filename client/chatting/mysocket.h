#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QString>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDateTime>
#include <QList>

class MySocket : public QObject
{

    Q_OBJECT

public:
    explicit MySocket(QObject *parent = nullptr);
    ~MySocket();

    bool connectToServer();
    void disconnectFromServer();

public slots:

    // 注册
    void registerUser(const QString& username, const QString& password);
    void registerResponse();

    // 登录
    void loginIn(const QString& username, const QString& password);
    void loginResponse();

    // 请求好友列表
    void requestFriendList(const QString& username);
    void getFriendListResponse();

    // 添加好友
    void addFriend(const QString& username, const QString& friendUsername);
    void addFriendResponse();

    // 删除好友
    void deleteFriend(const QString& username, const QString& friendUsername);
    void deleteFriendResponse();

    // 发送好友申请
    void sendFriendRequest(const QString& friend_account);
    void friendRequestResponse();

    // 发送好友消息
    void sendFriendMessage(const QString &username, const QString& friendUsername, const QString& content);
    void friendMessageResponse();

    // 请求群组列表
    void requestGroupList(const QString& username);
    void getGroupListResponse();

    // 创建群组
    void createGroup(const QString &username, const QString& groupName, const QStringList& members);
    void groupCreateReponse();

    // 加入群组
    void joinGroup(const QString& groupId, const QString& username);
    void joinGroupReponse();

    // 退出群组
    void leaveGroup(const QString& groupId, const QString& username);
    void leaveGroupReponse();

    // 发送群组消息
    void sendGroupMessage(const QString& groupId, const QString& sender, const QString& content);
    void groupMessageResponse();

signals:
    // 注册响应信号
    void registration_Response();

    // 登录响应信号
    void login_Response();

    // 添加好友响应信号
    void addFriend_Response();

    // 删除好友响应信号
    void deleteFriend_Response();

    // 发送好友申请响应函数
    void friendRequest_Response();

    // 发送好友消息响应函数
    void friendMessage_Response();

    // 创建群聊响应函数
    void groupCreate_Response();

    // 加入群聊响应函数
    void joinGroup_Response();

    // 退出群聊响应函数
    void leaveGroup_Response();

    // 好友列表已接收到的信号
    void friendListReceived();
    // 发送信号通知 UI 更新好友列表
    void friendListUpdated(QJsonArray friendList);

    // 群组列表已接收到的信号
    void groupListReceived();
    // 发送信号通知 UI 更新群聊列表
    void groupListUpdated(QJsonArray friendList);

    // 发送群聊消息响应函数
    void groupMessage_Response();

private:
    SOCKET socketfd;
    QString m_username;
    QByteArray buffer;  // 缓存

    bool sendMessagetoServer(const QByteArray &message);
    QJsonObject& receiveMessageFromServer();
};

#endif // MYSOCKET_H
