#include "online.h"

online::online()
{

}


void online::getAllPersonMessage()
{
    //先向服务器发送要请求所有成员的消息
    //解析出来的名字放在this->gallPersor上,密码放在this->password上,在线与不在线就放在this->onlinePersor上(1表示在线,0表示离线)
    //三个信息为一组解析
}

void online::getGroupPersonCnt()
{
    //先向服务器发送要请求每个群有多少人的信息
    //解析出来的放在this->groupPersonCnt上
}

void online::getgroupPersonMessage()
{
    //先向服务器发送要请求所有群的信息
    //解析出来的群昵称放在 this->groupName上,群成员放在this->groupPerson上
    //根据每个群有多少人设置读取间隔
}



