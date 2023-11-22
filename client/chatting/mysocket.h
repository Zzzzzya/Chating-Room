#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <Qstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <QList>
#include <QPair>
using namespace std;

class MySocket : public QObject
{

    Q_OBJECT

public:
    explicit MySocket(QObject *parent = nullptr);
    ~MySocket();

    bool connectToServer(const char* serverAddress, int port);
    void disconnectFromServer();

private slots:

    // 注册
    void registerUser(const QString& username, const QString& password);
    void registerResponse(const QJsonObject &jsonObject);

    // 登录
    void loginIn(const QString& username, const QString& password);
    void loginResponse(const QJsonObject &jsonObject);

    // 请求好友列表
    void requestFriendList(const QString& username);
    void getFriendListResponse(const QJsonObject &jsonObject);

    // 添加好友
    void addFriend(const QString& username, const QString& friendUsername);
    void addFriendResponse(const QJsonObject &jsonObject);

    // 删除好友
    void deleteFriend(const QString& username, const QString& friendUsername);
    void deleteFriendResponse(const QJsonObject &jsonObject);

    // 发送好友申请
    void sendFriendRequest(const QString& username, const QString& friendUsername, const QString& message);
    void friendRequestResponse(const QJsonObject &jsonObject);

    // 发送好友消息
    void sendFriendMessage(const QString &username, const QString& friendUsername, const QString& content);
    void FriendMessageResponse(const QJsonObject &jsonObject);

    // 请求群组列表
    void requestGroupList(const QString& username);
    void getGroupListResponse(const QJsonObject &jsonObject);

    // 创建群组
    void createGroup(const QString &username, const QString& groupName, const QStringList& members);
    void groupCreateReponse(const QJsonObject &jsonObject);

    // 加入群组
    void joinGroup(const QString& groupId, const QString& username);
    void joinGroupReponse(const QJsonObject &jsonObject);

    // 退出群组
    void leaveGroup(const QString& groupId, const QString& username);
    void leaveGroupReponse(const QJsonObject &jsonObject);

    // 发送群组消息
    void sendGroupMessage(const QString& groupId, const QString& sender, const QString& content);
    void groupMessageResponse(const QJsonObject &jsonObject);

signals:
    // 注册响应信号
    void registrationResponse(bool success);

    // 登录响应信号
    void loginInResponse(bool success);

    // 添加好友响应信号
    void addFriendResponse(bool success);

    // 删除好友响应信号
    void deleteFriendResponse(bool success);

    // 发送好友申请响应函数
    void friendRequestResponse(bool success);

    // 发送好友消息响应函数
    void friendMessageResponse(bool success);

    // 创建群聊响应函数
    void groupCreateReponse(bool success);

    // 加入群聊响应函数
    void joinGroupReponse(bool success);

    // 退出群聊响应函数
    void leaveGroupReponse(bool success);

    // 好友列表已接收到的信号
    void friendListReceived(const QList<QString>& friendNames);

    // 群组列表已接收到的信号
    void groupListReceived(const QList<QString>& groupNames);

    // 发送群聊消息响应函数
    void groupMessageResponse(bool success);

private:
    SOCKET socketfd;
    QString m_username;

    bool sendMessagetoServer(const QByteArray &message);

};

#endif // MYSOCKET_H
