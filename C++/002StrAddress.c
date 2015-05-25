//程序说明:
//  字符串数组的地址是构造然后赋值的，所以他们的地址是不一样的
//  但是指针指向字符常量的话，他们指向的就是同一个地址
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    char str1[] = "hello world";
    char str2[] = "hello world";
    
    char* str3 = "hello world";
    char* str4 = "hello world";

    printf("str1 is %s\n", str1);
    printf("str2 is %s\n", str2);
    printf("str3 is %s\n", str3);
    printf("str4 is %s\n", str4);

    printf("str1 = %#X\n", str1);
    printf("str2 = %#X\n", str2);
    printf("str3 = %#X\n", str3);
    printf("str4 = %#X\n", str4);
    
    if (str1 == str2)
        printf("str1 and str2 is the same!\n");
    else
        printf("str1 and str2 is not the same!\n");

    if (str3 == str4)
        printf("str3 and str4 is the same!\n");
    else
        printf("str3 and str4 is not the same!\n");

    return 0;
}
