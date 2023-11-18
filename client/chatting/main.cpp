#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login *l=new login();
    l->show();

    return a.exec();
}
