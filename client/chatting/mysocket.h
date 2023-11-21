#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <Qstring>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

class MySocket : public QObject
{

    Q_OBJECT

public:
    explicit MySocket(QObject *parent = nullptr);
    ~MySocket();

    bool connectToServer(const char* serverAddress, int port);
    void disconnectFromServer();

    // 注册
    void registerUser(const QString& username, const QString& password);

    // 登录
    void loginIn(const QString& username, const QString& password);

    // 请求好友列表
    void requestFriendList(const QString& username);

    // 添加好友
    void addFriend(const QString& username, const QString& friendUsername);

    // 删除好友
    void deleteFriend(const QString& username, const QString& friendUsername);

    // 发送好友申请
    void sendFriendRequest(const QString& username, const QString& friendUsername, const QString& message);

    // 发送好友消息
    void sendFriendMessage(const QString &username, const QString& friendUsername, const QString& content);

    // 请求群组列表
    void requestGroupList(const QString& username);

    // 创建群组
    void createGroup(const QString &username, const QString& groupName, const QStringList& members);

    // 加入群组
    void joinGroup(const QString& groupId, const QString& username);

    // 退出群组
    void leaveGroup(const QString& groupId, const QString& username);

    // 发送群组消息
    void sendGroupMessage(const QString& groupId, const QString& sender, const QString& content);


private:
    SOCKET socketfd;

    bool sendMessagetoServer(const QByteArray &message);

};

#endif // MYSOCKET_H
