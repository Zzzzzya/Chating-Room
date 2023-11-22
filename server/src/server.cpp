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
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

void print_log(const char *ip, const char *msg) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm);

    printf("[%s] %s: %s\n", time_str, ip, msg);
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
                
                char buffer[BUFFER_SIZE];
                ssize_t bytes_read;

                while (1) {
                    bytes_read = read(events[i].data.fd, buffer, BUFFER_SIZE);
                    if (bytes_read == 0) {
                        
                        close(events[i].data.fd);

                        
                        char cli_ip[INET_ADDRSTRLEN];
                        inet_ntop(cli_addr.sin_family, &cli_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
                        printf("Client disconnected: %s\n", cli_ip);

                        break;
                    } else if (bytes_read == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            
                            break;
                        }
                        perror("read failed");
                        close(events[i].data.fd);

                        
                        char cli_ip[INET_ADDRSTRLEN];
                        inet_ntop(cli_addr.sin_family, &cli_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
                        printf("Client disconnected: %s\n", cli_ip);

                        break;
                    }

                    
                    buffer[bytes_read] = '\0';
                    char cli_ip[INET_ADDRSTRLEN];
                    inet_ntop(cli_addr.sin_family, &cli_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
                    print_log(cli_ip, buffer);

                    
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

