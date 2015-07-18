#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    //----------socket-------------
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd)
    {
        perror("socket");
        exit(-1);
    }

    //----------connect------------
    struct sockaddr_in seraddr; 
    memset(&seraddr, 0, sizeof(struct sockaddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8888); //服务器的端口号
    seraddr.sin_addr.s_addr = inet_addr("10.136.8.101");//服务器地址
    if (-1 == connect(sfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr)))
    {
        perror("connect");
        close(sfd);
        exit(-1);
    }
    //打印本地和链接后的套接口信息
    int addrlen = sizeof(struct sockaddr);
    struct sockaddr_in tmp_addr;
    memset(&tmp_addr, 0, sizeof(struct sockaddr));
    getpeername(sfd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);                                                   
    printf("server socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));
    getsockname(sfd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);                                                   
    printf("client socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));
    
    //-----------send-------------
    printf("please input to send...");
    getchar();
    if (-1 == send(sfd, "hello server", 13, 0))
    {
        perror("send");
        close(sfd);
        exit(-1);
    }

    //-----------recv-------------
    char buf[512] = {0};
    if (-1 == recv(sfd, buf, sizeof(buf), 0))
    {
        perror("recv");
        close(sfd);
        exit(-1);
    }
    puts(buf);

    //-------------close------------
    close(sfd);

    return 0;
}
