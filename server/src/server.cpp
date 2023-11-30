#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <stddef.h>
#include <errno.h>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "MysqlConn.h"
#include "ConnectionPool.h"
#include <memory>
#include <random>


#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

void print_log(const char *ip, const char *msg) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm);

    printf("[%s] %s: %s\n", time_str, ip, msg);
}

void read_callback(int fd,int epfd) {
    char buffer[BUFFER_SIZE];
    int len= read(fd, buffer, sizeof(buffer));
    buffer[len] ='\0';
    // 从 epoll 实例中移除客户端文件描述符
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        std::cerr << "failed to remove client socket from epoll instance" << std::endl;
    }
    if (len > 0) {
        // 进行读取操作并对数据进行处理
        std::string request(buffer,len);
        handleJsonRequest(request,fd);
	}else if (len == 0) {
        // 客户端关闭连接，需要进行关闭和清理操作
        std::cout << "client disconnected" << std::endl;
        close(fd);
    }else {
        // 发生错误，需要进行错误处理
        std::cerr << "read() error on fd " << fd << std::endl;
        close(fd);
	}
}


void handleJsonRequest (const std::string& json,int& cfd)
{  
        // 创建一个连接池pool
        ConnectionPool* pool = ConnectionPool::getConnectionPool();
		Json::Value root;
        Json::Reader reader;
        if (!reader.parse(json,root)) {
            std::cerr << "failed to parse JSON" << std::endl;
            // 解析失败，析构pool
            pool->~ConnectionPool();
            return;
        }
        std::string type = root["type"].asString();
        if (type != "request"&&type!= "message") {
            std::cerr << "invalid JSON: type is not 'request' and 'message' " << std::endl;
            // 解析失败，析构pool
            pool->~ConnectionPool();
            return;
        }
        std::string subtype = root["subtype"].asString();
       
	if (type =="request") {
		if (subtype =="login") {
            std::string username = root["username"].asString();
            std::string password = root["password"].asString();
            handleLogin (pool,username,password,subtype,cfd);
        }
        else if (subtype == "register"){
            //以下函数同login一样的格式 获取对应的username 
            handleResister ();
		}
		else if (subtype =="add friend") {
		    handleaddFriend ();
		}		
		else if (subtype =="del friend") {
		    handleDeleteFriend ();
		}
		else if (subtype == "app_friend") {
		    handleappfriend ();
		}
		else if (subtype == "get_friend list") {
		    handleGetRriendList ();
		}

        /*
            XiaoLin's Part
        */
		else if (subtype =="get_group_list"){
            std::string user_name = root["username"].asString();
            std::string password = root["password"].asString();
		    handleGetGroupList (pool, user_name , password);
		}
		else if (subtype =="getgroupmenber_count") {
            std::string group_name = root["groupName"].asString();
		    han_getgroupMember_count(pool , group_name);
		}
		else if (subtype == "create_group" ){
            std::string user_name = root["username"].asString();
            std::string group_name = root["group_name"].asString();
            std::string members = root["member"].asString();
		    handleCreateGroup (pool , user_name , group_name , members);
		}
		else if (subtype ==" join group") {
            std::string user_name = root["username"].asString();
            std::string group_name = root["group_name"].asString();
		    handleJoinGroup (pool ,user_name , group_name);
		}
		else if (subtype == "leave _group") {
            std::string user_name = root["username"].asString();
            std::string group_name = root["group_name"].asString();
		    handleLeaveGroup (pool ,user_name ,group_name);
		}
		else if (type == "group _message") {
            std::string user_name = root["username"].asString();
            std::string group_name = root["sender"].asString();
            std::string time = root["time"].asString();
            std::string data = root["data"].asString();
		    handleGroupMessage (pool , user_name , group_name , time , data);
		}
    }
}

// 因为不会有重复的名字出现，所以可以根据名字得到ID
int getUserId(std::shared_ptr<MysqlConn> conn , const std::string& user_name)
{
    // std::shared_ptr<MysqlConn> conn = pool->getConnection();
    int id;
    std::string sql = "select user_id from users where users.username = " + user_name +";";
    conn->query(sql);

    // 检查用户是否存在
    if (!conn->next()) {
        std::cerr << "Error: Group " << user_name << " does not exist." << std::endl;
        return -1;
    }
    id = std::stoi(conn->value(0));
    return id;
}

int getGroupId(std::shared_ptr<MysqlConn> conn, const std::string& group_name)
{
    // std::shared_ptr<MysqlConn> conn = pool->getConnection();
    int id;

    std::string sql = "SELECT group_id FROM groups WHERE group_name = " + group_name + ";";

    // Execute the query
    conn->query(sql);

    if (!conn->next()) {
        std::cerr << "Error: Group " << group_name << " does not exist." << std::endl;
        return -1;
    }

    // Get the group_id value
    id = std::stoi(conn->value(0));

    return id;
}

void handleGetGroupList(ConnectionPool* pool , const std::string& user_name , const std::string& password)
{
    std::shared_ptr<MysqlConn> conn = pool->getConnection();

    //获取id
    int user_id = getUserId(conn , user_name);

    std::string sql = "select * from groups where \
    JOIN user_groups ON groups.group_id = user_groups.group_id\
    JOIN users ON user_groups.user_id = users.user_id \
    WHERE users.user_id = " + std::to_string(user_id) + ';';

    conn->query(sql);

    // 从结果集中取出一行
    while (conn->next())
    {
        // 打印每行字段值
        std::cout << conn->value(0) << ", "
            << conn->value(1) << ", "
            << conn->value(2) << ", "
            << conn->value(3) << std::endl;
    }
}

void han_getgroupMember_count(ConnectionPool* pool , const std::string& group_name )
{
    std::shared_ptr<MysqlConn> conn = pool->getConnection();

    //获取id
    int group_id = getUserId(conn , group_name);

    std::string sql = R"(select count(*) from groups
    join user_groups on user_groups.group_id = groups.group_id
    where groups.group_id =)"+ std::to_string(group_id) + ';';

    conn->query(sql);

    // 从结果集中取出一行
    while (conn->next())
    {
        // 打印每行字段值
        std::cout << conn->value(0) << ", "
            << conn->value(1) << ", "
            << conn->value(2) << ", "
            << conn->value(3) << std::endl;
    }
}

void handleCreateGroup (ConnectionPool* pool , const std::string& user_name , const std::string& group_name ,const std::string members)
{
    // 检测group_name 是否为空
    if(group_name.empty()) {
        std::cerr << "Error : Group Name cannot be empty" << std::endl;
        return ;
    }

    std::shared_ptr<MysqlConn> conn = pool->getConnection();

    //获取id
    int user_id = getUserId(conn , user_name);

    // 检测user是否存在
    std::string userCheckSQL = "SELECT * FROM users WHERE user_id = " + std::to_string(user_id) +';';
    conn->query(userCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " does not exist." << std::endl;
        return;
    }  

    // Insert the new group
    // group_id是自动生成的不用填入
    std::string groupInsertSQL = "INSERT INTO groups (group_name, group_members) VALUES ('" + group_name + "', '" + members + "');";
    conn->update(groupInsertSQL);

    std::cout << "Group " << group_name << " created successfully." << std::endl;

}

void handleJoinGroup (ConnectionPool* pool , const std::string& user_name , const std::string& group_name)
{
    std::shared_ptr<MysqlConn> conn = pool->getConnection();

    //获取id
    int user_id = getUserId(conn , user_name);
    int group_id = getUserId(conn , group_name);

    // 1.检测user是否存在
    std::string userCheckSQL = "SELECT * FROM users WHERE user_id = " + std::to_string(user_id) + ';';
    conn->query(userCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " does not exist." << std::endl;
        return;
    }  
    // 2.检测group是否存在
    std::string groupCheckSQL = "SELECT * FROM groups WHERE group_id = " + std::to_string(group_id) + ';';
    conn->query(groupCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: Group " << group_name << " does not exist." << std::endl;
        return;
    }

    // 3.检测user是否已经在group中了
    std::string membershipCheckSQL = "SELECT * FROM user_groups WHERE user_id = " + std::to_string(user_id) + " AND group_id = " + std::to_string(group_id) + ";";

    conn->query(membershipCheckSQL);

    if (conn->next()) {
        std::cerr << "Error: User " << user_name << " is already a member of group " << group_name << "." << std::endl;
        return;
    }

    // 4.加入user到群聊
    std::string joinGroupSQL = "INSERT INTO user_groups (user_id, group_id) VALUES (" +
                                std::to_string(user_id) + " , " + std::to_string(group_id) + ");";
    conn->update(joinGroupSQL);

    std::cout << "User " << user_name << " has joined group " << group_name << " successfully." << std::endl;
}   

void handleLeaveGroup (ConnectionPool* pool , const std::string& user_name , const std::string& group_name)
{
    std::shared_ptr<MysqlConn> conn = pool->getConnection();

     //获取id
    int user_id = getUserId(conn , user_name);
    int group_id = getUserId(conn , group_name);

    // 1.检测user是否存在
    std::string userCheckSQL = "SELECT * FROM users WHERE user_id = '" + std::to_string(user_id) + "';";
    conn->query(userCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " does not exist." << std::endl;
        return;
    }  
    // 2.检测group是否存在
    std::string groupCheckSQL = "SELECT * FROM groups WHERE group_id = '" + std::to_string(group_id) + "';";
    conn->query(groupCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: Group " << group_name << " does not exist." << std::endl;
        return;
    }

    // 3.检测user是否在group中了
    std::string membershipCheckSQL = "SELECT * FROM user_groups WHERE user_id = " + std::to_string(user_id) +
                                      " AND group_id = " + std::to_string(group_id) + ";";
    conn->query(membershipCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " is not a member of group " << group_name << "." << std::endl;
        return;
    }

    // 4.user_groups移除该user，同时触发器将groups中的该member删除
    std::string leaveGroupSQL = "DELETE FROM user_groups WHERE user_id = " +
                                 user_name + " AND group_id = " + std::to_string(user_id) + ";";
    conn->update(leaveGroupSQL);

    std::cout << "User " << user_name << " has left group " << group_name << " successfully." << std::endl;

}

void handleGroupMessage (ConnectionPool* pool , const std::string& user_name , const std::string& group_name , const std::string& time , const std::string& data)
{
    std::shared_ptr<MysqlConn> conn = pool->getConnection();

     //获取id
    int user_id = getUserId(conn , user_name);
    int group_id = getUserId(conn , group_name);

    // 1.检测user是否存在
    std::string userCheckSQL = "SELECT * FROM users WHERE user_id = '" + std::to_string(user_id) + "';";
    conn->query(userCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " does not exist." << std::endl;
        return;
    }  
    // 2.检测group是否存在
    std::string groupCheckSQL = "SELECT * FROM groups WHERE group_id = '" + std::to_string(group_id) + "';";
    conn->query(groupCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: Group " << group_name << " does not exist." << std::endl;
        return;
    }

    // 3.检测user是否在group中了
    std::string membershipCheckSQL = "SELECT * FROM user_groups WHERE user_id = " + std::to_string(user_id) +
                                      " AND group_id = " + std::to_string(group_id) + ";";
    conn->query(membershipCheckSQL);

    if (!conn->next()) {
        std::cerr << "Error: User " << user_name << " is not a member of group " << group_name << "." << std::endl;
        return;
    }

     //4.插入群组消息
    std::string insertMessageSQL = "INSERT INTO chat_record (sender_id, receiver_id, chat_content, chat_time) VALUES ("
                                   "(SELECT user_id FROM users WHERE user_id = '" + std::to_string(user_id) + "'), "
                                   "(SELECT group_id FROM groups WHERE group_id = '" +  std::to_string(group_id) + "'), '"
                                   + data + "', '" + time + "');";


    conn->update(insertMessageSQL);

}

int main() {
    int listen_fd, conn_fd, epoll_fd, num_events, i;
    struct sockaddr_in serv_addr, cli_addr;
    struct epoll_event events[MAX_EVENTS], event;

    
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl failed");
        exit(EXIT_FAILURE);
    }

    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    
    if (listen(listen_fd, SOMAXCONN) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1 failed");
        exit(EXIT_FAILURE);
    }

    
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
        perror("epoll_ctl failed");
        exit(EXIT_FAILURE);
    }

    
    while (1) {
        num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("epoll_wait failed");
            exit(EXIT_FAILURE);
        }

        
        for (i = 0; i < num_events; i++) {
            if (events[i].data.fd == listen_fd) {
                
                socklen_t cli_len = sizeof(cli_addr);
                conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);
                if (conn_fd == -1) {
                    perror("accept failed");
                    continue;
                }

                
                if (fcntl(conn_fd, F_SETFL, O_NONBLOCK) == -1) {
                    perror("fcntl failed");
                    close(conn_fd);
                    continue;
                }

                
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = conn_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &event) == -1) {
                    perror("epoll_ctl failed");
                    close(conn_fd);
                    continue;
                }

            
                char cli_ip[INET_ADDRSTRLEN];
                inet_ntop(cli_addr.sin_family, &cli_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
                printf("New client connected: %s\n", cli_ip);
            } else {
                
                    read_callback(events[i].data.fd,epoll_fd)

                    
                    write(events[i].data.fd, buffer, bytes_read);

                
                    print_log("Server", buffer);
                }
            }
        }
    

    close(listen_fd);
    close(epoll_fd);

    return 0;
}

