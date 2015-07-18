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
    int addrlen = sizeof(struct sockaddr);
    struct sockaddr_in tmp_addr;
    memset(&tmp_addr, 0, sizeof(struct sockaddr));
    //-----------socket----------------
    //创建一个socket套接字，并用sfd文件描述符指向它
    //第一个参数指定IPV4或者IPV6网络协议
    //第二个指定TCP(SOCK_STREAM)或者UDP(SOCK_DGRAM)
    //第三个是传输协议编号，通常为0
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd)
    {
        perror("socket");
        exit(-1);
    }
    getsockname(sfd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);
    printf("before bind listen socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));
    
    //-----------bind----------------
    //这里是初始化服务器的套接字信息，然后bind将套接字信息与之前创建的套接口socket绑定起来
    struct sockaddr_in my_addr; //定义结构体变量,此结构体专门用于存放套接口信息
    memset(&my_addr, 0, sizeof(struct sockaddr)); //初始化清空
    my_addr.sin_family = AF_INET;   //IPV4
    my_addr.sin_port = htons(8888); //需要指定端口号
    //my_addr.sin_addr.s_addr = inet_addr("120.132.72.182");
    //my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_addr.s_addr = inet_addr("10.136.8.101");
    if (-1 == bind(sfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)))
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }
    getsockname(sfd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);
    printf("after bind listen socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));

    //-----------listen-------------
    //设置之前定义的服务器套接字用于监听，最大连接数为10
    printf("now listen ...\n");
    if (-1 == listen(sfd, 10))
    {
        perror("listen");
        close(sfd);
        exit(-1);
    }

    //-----------accept------------
    //监听到任务之后，新建结构体，accept将产生一个新的套接字，并且新的套接字会?????
    printf("now accept ...\n");
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr));
    int new_fd = accept(sfd, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
    if (-1 == new_fd)
    {
        perror("accept");
        close(sfd);
        exit(-1);
    }
    printf("%s %d success connect\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    //打印本地套接口信息和连接后的套接口信息
    getsockname(new_fd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);
    printf("new socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));
    getsockname(sfd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);
    printf("listen socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));
    getpeername(new_fd, (struct sockaddr*)&tmp_addr, (socklen_t*)&addrlen);
    printf("client socket is %s %d\n", inet_ntoa(tmp_addr.sin_addr), ntohs(tmp_addr.sin_port));

    
    //----------recv--------------
    //从新的套接字获取结果，保存到buf中，最后的flag一般默认为0
    char buf[512] = {0};
    if (-1 == recv(new_fd, buf, sizeof(buf), 0))
    {
        perror("recv");
        close(new_fd);
        close(sfd);
        exit(-1);
    }
    puts(buf);
    
    //-------------send------------
    if (-1 == send(new_fd, "hello", 6, 0))
    {
        perror("send");
        close(new_fd);
        close(sfd);
        exit(-1);
    }
    
    //-------------close------------
    close(sfd);
    close(new_fd);
    
    
    return 0;
}
