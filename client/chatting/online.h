#ifndef ONLINE_H
#define ONLINE_H
#include<QString>
#include<QVector>


class online
{
public:
    online();
    void getAllPersonMessage();//读取所有成员信息(名称和密码)
    void getgroupPersonMessage();//读取每个群里的成员信息
    void getGroupPersonCnt();//读取每个群有多少人

    QVector<QString>allPersor;//存放所有人昵称
    QVector<QString>groupName;//存放所有群昵称
    QVector<QString> password;//存放所有人密码
    QVector<QString>groupPerson;//存放每个组的成员昵称
    QVector<int>onlinePersor;//存放所有人在线情况(1在线,0不在线)
    QVector<int>groupPersonCnt;//存放每个组有多少人
};

#endif // ONLINE_H
