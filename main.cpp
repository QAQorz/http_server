#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <cassert>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>

int main(){
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(server_sock != -1);

    struct sockaddr_in server_address;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(2333);
    server_address.sin_family = PF_INET;

    int ret = bind(server_sock, (struct sockaddr*) &server_address, sizeof(server_address));
    assert(ret != -1);

    ret = listen(server_sock, 1);
    assert(ret != -1);

    while (true){
        struct sockaddr_in client;
        socklen_t client_addrlength = sizeof(client);
        int connfd = accept(server_sock, (struct sockaddr*) &client, &client_addrlength);
        if (connfd < 0){
            printf("error");
            continue;
        }

        // 从socket接收消息
        char request[1024];
        recv(connfd, request, 1024, 0);
        request[strlen(request)+1] = '\0';
        printf("%s\n", request);
        printf("successeful!\n");

        // HTTP响应
        char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
        // 发送响应
        int s = send(connfd,buf,strlen(buf),0);
        // 消息体
        int fd = open("hello.html", O_RDONLY);
        // 零拷贝发送消息体
        sendfile(connfd, fd, NULL, 2500);
        close(fd);
        close(connfd);
    }
}