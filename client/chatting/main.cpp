#include "login.h"
#include "mysocket.h"
#include "usersql.h"
#include <QApplication>

MySocket *mysocket;
UserSql *user;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mysocket = new MySocket(nullptr);
    mysocket->connectToServer();


    login *l=new login();
    l->show();

    int result = a.exec();

    // 在应用程序退出前,释放资源和关闭网络连接
    delete mysocket;

    return result;
}
