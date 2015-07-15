//名字地址的转化

#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    char* ptr;
    char** pptr;
    struct hostent* hptr;
    char str[32] = {'\0'};
    ptr = argv[1];  //这里是需要解析的域名或者主机名，比如www.baidu.com
    //调用gethostbyname()
    if ((hptr = gethostbyname(ptr)) == NULL)
    {
        printf("gethostbyname error for host: %s\n", ptr);
        return 0;
    }
    //打出主机的规范名
    printf("official hostname: %s\n", hptr->h_name);
    
    //打印出所有主机的别名
    for (pptr = hptr->h_aliases; *pptr != NULL; ++pptr)
    {
        printf("alias: %s\n", *pptr);
    }

    //根据地址类型，将地址打印出来
    switch (hptr->h_addrtype)
    {
        case AF_INET:
        case AF_INET6:
            pptr = hptr->h_addr_list;
            //打印出所有的地址
            for (; *pptr != NULL; ++pptr)
            {
                printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
            }
            printf("first address: %s\n", inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
            break;
        default:
            printf("unknown address type\n");
            break;
    }
    return 0;
}

/*
#include <netdb.h>

//将主机名转化为地址,比如将域名(www.baidu.com)或者主机名转成IP地址
struct hostent* gethostbyname(const char* hostname);

//将地址转化为主机名。用于将IP地址转换为主机名或者域名。参数addr是一个
//IP地址，此时这个IP地址不是普通的字符串，而要通过inet_aton把字符串变成
//网络字节序
struct hostent* gethostbyaddr(const char* addr, size_t len, int family);

struct hostent
{
    char* h_name;       //正式主机名
    char** h_aliases;   //主机别名
    int h_addrtype;     //主机IP地址类型，IPV4为AF_INET
    int h_length;       //主机IP地址字节长度，对于IPV4是4字节，即32位
    char** h_addr_list; //主机IP地址列表
        //注意，地址列表里面的地址可以用ntop转换成点分十进制字符串,具体为什么暂时不明。
        //从example1可以看出，ntop可以将网络字节序的那个结构体转化成点分十进制地址，也可以吧这里的char*类型转化成地址
}

#define h_addr h_addr_list[0]   //保存的是IP地址


*/

