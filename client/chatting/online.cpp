#include "online.h"

online::online()
{

}

void online::getOnlinePersor()
{
    onlinePersor.resize(10);
    for(int i=0;i<onlinePersor.size();i++)
    {
        this->onlinePersor[i]=QString("hao").toUtf8().data();
    }
}
void online::getgroupName()
{
    groupName.resize(10);
    for(int i=0;i<groupName.size();i++)
    {
        this->groupName[i]=QString("666").toUtf8().data();
    }

}

void online::getTotalCnt()
{
    totalCnt=8;
}

void getAllPerson()
{

}

void getPassword()
{

}
