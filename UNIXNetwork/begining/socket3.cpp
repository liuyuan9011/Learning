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
        addrlen 是sockaddr的结构体长度。通常是计算sizeof(struct sockaddr)
返回值：成功返回0， 失败返回-1
常用实例：  
    struct sockaddr_in my_addr; //定义结构体变量
    memset(&myaddr, sizeof(struct sockaddr));   //将结构体清空
    bzero(&my_addr, sizeof(struct sockaddr));
    my_addr.sin_family = AF_INET;   //表示采用IPV4网络协议
    //htons()用来将指定的16位hostshort转换成网络字符顺序
    my_addr.sin_port = htons(8888); //表示端口号为8888,
    my_addr.sin_addr.s_addr = inet_addr("192.168.0.101");//inet_addr用来将IP地址字符串转换成网络使用的二进制数字，如果为INADDR__ANY，这表示服务器自动填充本机IP地址
    if (bind(sfd, (struct sockaddr*)&my_str, sizeof(struct socketaddr)) == -1)  {perror("bind");close(sfd);exit(-1);}
    //注意，如果将my_addr.sin_port置为0，函数会自动为你选择一个未占用的端口来使用。同样，通过将my_addr.sin_addr.s_addr置为INADDR_ANY，系统会自动填充本机的IP地址。

4.listen函数：是服务器的这个端口和IP处于监听状态，等待网络中某一客户机的连接请求。如果客户端有连接请求，端口就会接受这个请求
原型：  int listen(int sockfd, int backlog);
参数：  sockfd：为前面socket的返回值，也就是sfd
        backlog：指定同时能处理的最大连接请求，通常为10或者5，最大为128
返回值：成功则返回0，失败返回-1
常用实例：if (listen(sfd, 10) == -1) {perror("listen");close(sfd),exit(-1)}

5.accept函数：接受远程计算机的连接请求，建立起与客户机之间的通信连接。服务器处于监听状态时，如果某时刻获得客户机的连接请求，此时并不是立即处理这个请求，而是将这个请求放在等待队列中，当系统空闲时再处理客户机的连接请求。当 accept 函数接受一个连接时，会返回一个新的 socket 标识符，以后的数据传输和读取就要通过这个新的 socket 编号来处理，原来参数中的 socket 也可以继续使用，继续监听其它客户机的连接请求。（也就是说，类似于移动营业厅，如果有客户打电话给 10086，此时服务器就会请求连接，处理一些事务之后，就通知一个话务员接听客户的电话，也就是说，后面的所有操作，此时已经于服务器没有关系，而是话务员跟客户的交流。 对应过来，客户请求连接我们的服务器，我们服务器先做了一些绑定和监听等等操作之后，如果允许连接，则调用 accept 函数产生一个新的套接字，然后用这个新的套接字跟我们的客户进行收发数据。也就是说，服务器跟一个客户端连接成功，会有两个套接字。）
原型： int accept(int s,struct sockaddr * addr,int * addrlen);
参数：  s为前面 socket的返回值.即 sfd
        addr为结构体指针变量，和bind的结构体是同种类型的，系统会把远程主机的信息（远程主机的地址和端口号信息）保存到这个指针所指的结构体中。
        addrlen表示结构体的长度，为整型指针
返回值：成功则返回新的 socket 处理代码 new_fd，失败返回-1
常用实例：  struct sockaddr_in clientaddr;
            memset(&clientaddr, 0, sizeof(struct sockaddr));
            int addrlen = sizeof(struct sockaddr);
            int new_fd = accept(sfd, (struct sockaddr*)&clientaddr, &addrlen);
            if(new_fd == -1)
                {perror("accept");close(sfd);exit(-1);}
            printf("%s %d success connect\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

6. recv函数：用新的套接字来接收远端主机传来的数据，并把数据存到由参数buf指向的内存空间
原型： int recv(int sockfd,void *buf,int len,unsigned int flags);
参数：  sockfd为前面 accept 的返回值.即 new_fd，也就是新的套接字。
        buf:表示缓冲区
        len:表示缓冲区的长度
        flags:通常为0
返回值：成功则返回实际接收到的字符数，可能会少于你所指定的接收长度。失败返回-1
常用实例：  char buf[512] = {0};
            if(recv(new_fd, buf, sizeof(buf), 0) == -1)
                {perror("recv");close(new_fd);close(sfd);exit(-1);}
            puts(buf);

7. send 函数：用新的套接字发送数据给指定的远端主机
原型： int send(int s,const void * msg,int len,unsigned int flags);)}
参数：  s:为前面 accept 的返回值.即 new_fd
        msg:一般为常量字符串
        len:表示长度
        flags:通常为 0
返回值：成功则返回实际传送出去的字符数，可能会少于你所指定的发送长度。失败返回-1
常用实例：  if(send(new_fd, "hello", 6, 0) == -1)
                {perror("send");close(new_fd);close(sfd);exit(-1);}

8. close 函数：当使用完文件后若已不再需要则可使用 close()关闭该文件，并且 close()会让数据写回磁盘，并释放该文件所占用的资源
原型： int close(int fd);
参数： fd:前面sfd, new_fd
返回值：若顺利关闭文件返回0，失败返回-1
常用实例：close(sfd);
          close(new_fd);

客户端：
1. connect 函数：用来请求连接远程服务器，将参数 sockfd 的socket连至参数serv_addr指定的服务器IP 和端口号上去。
原型： int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);
参数：  sockfd:为前面 socket 的返回值，即 sfd
        serv_addr:为结构体指针变量，存储着远程服务器的 IP 与端口号信息。
        addrlen:表示结构体变量的长度
返回值：成功则返回 0，失败返回-1
常用实例：  struct sockaddr_in seraddr;//请求连接服务器
            memset(&seraddr, 0, sizeof(struct sockaddr));
            seraddr.sin_family = AF_INET;
            seraddr.sin_port = htons(8888); //服务器的端口号
            seraddr.sin_addr.s_addr = inet_addr("192.168.0.101"); //服务器的 ip
            if(connect(sfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr)) == -1)
                {perror("connect");close(sfd);}
*/















