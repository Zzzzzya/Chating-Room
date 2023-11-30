#ifndef USERSQL_H
#define USERSQL_H
#include<Qstring>
#include<QVector>

class UserSql
{
public:
    UserSql();
public:
    //个人信息
    QString userName;
    QString password;
    //好友信息
    QVector<QString>userFriend;
    QVector<int>friendIsOnline;
    //群信息
    int cnt;
    QVector<QString>groupName;
    QVector<QString>groupNumberName;

//public:
//    void getAllUserMessage();//获取所有人信息
//    void getUserFriendMessage();//获取好友的名字和是否在线
//    void getGroupNumberCnt();//获取每个群的人数
//    void getUserGroupMessage();//获取每个群的昵称和每个群的成员名字
};

#endif // USERSQL_H
