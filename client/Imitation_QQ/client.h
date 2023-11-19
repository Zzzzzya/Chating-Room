#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <string>
#include <winsock2.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

enum MsgType {
    Login,          // 登录报文
    Register,       // 注册报文
    Msg,            // 普通信息
    UsrEnter,       // 用户进入
    UsrLeft,         // 用户退出
};

class Client : public QObject
{
public:
    explicit Client(QObject *parent = nullptr);
    Client(const string serverIP, int serverPort);
    ~Client();

    // 向服务器发送 注册/登录 信息
    void sendMessage_special(MsgType type, const string username, const string password, const string serverIP, int serverPort);	// 登录&注册消息

    //  发送其他信息
    void sendMessage_normal(MsgType type, const string username, const string content, int port);	// 一般消息

private:
    WSADATA wsaData;            // Winsock
    SOCKET tcpSocket;           // 套接字
    sockaddr_in serverAddr;     // 存储套接字地址信息
    const string serverIP;       // 服务器ip
    int serverPort;             // 服务器端口号
};






#endif // CLIENT_H
