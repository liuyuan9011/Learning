#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//地址格式的转化

int main(int argc, const char *argv[])
{
    //首先定义一个点分式字符串IP地址
    char ip[] = "192.168.0.101";

    /*struct in_addr*/
    struct in_addr myaddr;

    /*inet_aton*/
    int iRet = inet_aton(ip, &myaddr);
    printf("%x\n", myaddr.s_addr);
    
    /*inet_addr*/
    printf("%x\n", inet_addr(ip));

    /*inet_pton*/
    iRet = inet_pton(AF_INET, ip, &myaddr);
    printf("%x\n", myaddr.s_addr);

    myaddr.s_addr = 0xac100ac4;
    /*inet_ntoa*/
    printf("%s\n", inet_ntoa(myaddr));

    /*inet_ntop*/
    inet_ntop(AF_INET, &myaddr, ip, 16);
    puts(ip);
    
    return 0;
}


/*
    关于结构体in_addr
    struct in_addr
    {
        //32位IPV4地址，网络字节序
        unsigned long int s_addr;     
    }
    头文件<netinet/in.h>
*/
/*
    int inet_aton(const char* straddr, struct in_addr* addrptr)
    第一个参数为传入参数，内容为点分十进制IP地址，第二个参数为传出参数
    ，内容为存放解析后的ip地址结构体
    返回值：如果成功返回1， 不成功返回0

    char* inet_ntoa(struct in_addr addr)
    将结构体形式的网络字节序的32为二进制数字转换为点分十进制的IP地址
    参数为结构体，返回值为IP地址字符串

    (常用)inet_addr(const char* straddr)
    功能跟inet_aton相同，都是把字符串转化成网络地址，不同的是，他把
    网络地址直接作为返回值返回了

    头文件：
    <sys/socket.h>
    <netinet/in.h>
    <arpa/inet.h>
*/
/*
    <arpa/inet.h>
    int inet_pton(int family, const char* src, void* dst) 
    const char* inet_ntop(int family, const void* src, char* dst, socklent_t len)
    函数 inet_pton 跟 inet_aton 实现的功能类似，只是多了 family 参数，该参数指定为 AF_INET，表示是 IPv4 协议，如果是 AF_INET6，表示 IPv6 协议。
    函数 inet_ntop 跟 inet_ntoa 类似，其中 len 表示表示转换之后的长度（字符串的长度）
*/

















