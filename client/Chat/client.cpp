#include "client.h"
#include <iostream>

void Client:: sendMessage_normal(MsgType type, const string username, const string content, int port)	// 一般消息
{
    // 构造要发送的数据
    string messageData;
    messageData += to_string(type) + " | ";  		// 第一段：类型
    messageData += username + " | ";             	// 第二段：用户名
    messageData += content + "\n";                  // 第三段：具体内容

}

void Client::sendMessage_special(MsgType type, const string username, const string password, const string serverIP, int serverPort)	// 登录&注册消息
{
    std::string messageData;
    messageData += to_string(type) + " | ";  		// 第一段：类型
    messageData += username + " | ";  				// 第二段：用户名
    messageData += password + "\n";        			// 第三段：密码

}
