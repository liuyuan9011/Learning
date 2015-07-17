















/*
TCP通信基本步骤如下：
服务端：socket-bind-listen-while(1){accept-recv-send-close}-close
客户端：socket----------------------connect-send-recv-------close

服务器端:
1.头文件：
#include <sys/types.h>
#include <sys/socket>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

2.socket函数，生成一个套接口的描述符
原型:   int socket(int domain, int type, int protocol)
参数：  domain: AF_INET:IPV4, AF_INET6: IPV6
        type: tcp:SOCK_STREAM  udp: SOCK_DGRAM              
        protocol: 指定socket所使用的传输协议编号，通常为0
返回值：成功则返回套接口描述符，失败返回-1
常用实例：int sfd = socket(AF_INET, SOCK_STREAM, 0);
          if (sfd == -1) {perror("socket"); exit(-1);}

3.bind函数，用来绑定一个端口号和IP地址，使套接口与指定的端口号和IP地址相关联
原型：  int bind(int sockfd, struct sockaddr* my_addr, int addrlen);
参数：  sockfd：就是前面socket所生成的文件描述符
        my_addr：指向的是struct sockaddr结构体
        struct sockaddr     //此结构体不常用
        {
            unsigned short int sa_family;   //调用socket时的domain参数
            char sa_data[14];   //最多使用14个字符长度
        }
        此结构体会因使用不同的socket domain而有不同结构定义,
        例如使用AF_INET domain，其socketaddr结构定义便为
        struct sockaddr_in  //常用结构体
        {
            unsigned short int sin_family;  //也就是sa_family,AF_INET
            uint16_t sin_port;  //为使用的port编号
            struct in_addr sin_addr;    //为IP地址
            unsigned char sin_zero[8];  //未使用
        }
        struct in_addr
        {
            uint32_t s_addr;    //32位网络字节序IP地址，例：example1
        }
*/















