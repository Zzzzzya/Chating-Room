#ifndef ONLINE_H
#define ONLINE_H
#include<QString>
#include<QVector>


class online
{
public:
    online();
    //参数是数据库里的东西,目前还不知道怎么传
    void getOnlinePersor();
    void getgroupName();
    void getTotalCnt();
    int totalCnt;
    QVector<QString>onlinePersor;
    QVector<QString>groupName;
};

#endif // ONLINE_H
