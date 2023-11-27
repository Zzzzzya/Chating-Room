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
    char buffer[BUF_SIZE];
    int len= read(fd, buffer, sizeof(buffer));
    buffer[len] ='\0';
    // 从 epoll 实例中移除客户端文件描述符
    if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        cerr << "failed to remove client socket from epoll instance" << endl;
    }
    if (len > 0) {
        // 进行读取操作并对数据进行处理
        string request(buffer,len);
        handleJsonRequest(request,fd);
	}else if (len == 0) {
        // 客户端关闭连接，需要进行关闭和清理操作
        cout << "client disconnected" << endl;
        close(fd);
    }else {
        // 发生错误，需要进行错误处理
        cerr << "read() error on fd " << fd << endl;
        close(fd);
	}
}


void handleJsonRequest (const string& json,int& cfd)
{  
		Json::Value root;
        Json::Reader reader;
        if (!reader.parse(json,root)) {
            cerr << "failed to parse JSON" << endl;
            return;
        }
        string type = root["type"].asString();
        if (type != "request"&&type!= "message") {
            cerr << "invalid JSON: type is not 'request' and 'message' " << endl;
            return;
        }
        string subtype = root["subtype"].asString();
       
	if (type =="request") {
		if (subtype =="login") {
		string username = root["username"].asString();
		string password = root["password"].asString();
		handleLogin (username,password,subtype,cfd);
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
		else if (subtype =="get_group_list"){
		handleGetGroupList ();
		}
		else if (subtype =="getgroupmenber_count") {
		han_getgroupMember_count();
		}
		else if (subtype == "create_group" ){
		handleCreateGroup ();
		}
		else if (subtype ==" join group") {
		handleJoinGroup ();
		}
		else if (subtype == "leave _group") {
		handleLeaveGroup ();
		}
	}
		else if (type == "group _message") {
		handleGroupMessage ();
		}
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
    }

    close(listen_fd);
    close(epoll_fd);

    return 0;
}

