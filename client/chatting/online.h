#ifndef ONLINE_H
#define ONLINE_H
#include<QString>
#include<QVector>


class online
{
public:
    online();
    void getOnlinePersor();
    void getgroupName();
    void getTotalCnt();
    void getAllPerson();
    void getPassword();
    void getgroupPerson();
    void getGroupPersonIsOnline();
    int totalCnt;
    QVector<QString>allPersor;
    QVector<QString>onlinePersor;
    QVector<QString>groupName;
    QVector<QString> password;
    QVector<QString>groupPerson;
    QVector<int>groupPersonIsOnline;
};

#endif // ONLINE_H
