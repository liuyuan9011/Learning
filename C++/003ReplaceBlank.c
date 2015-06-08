//替换字符串中的所有空格为%20, 关键在于另时间复杂度为O(n)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//注意这里传入的length应该是字符串的实际长度而不是包含\0的长度
void replaceBlank(char s[], int length)
{
    if (s == NULL || length <= 0)
        return ;
    //首先数出字符串的实际长度和空格的个数
    int real_num = 0;
    int blank_num = 0;
    int i = 0;
    while (s[i] != '\0')
    {
        ++real_num;
        if (' ' == s[i])
        {
            ++blank_num;
        }
        ++i;
    }
    //计算出新字符串的长度
    int new_length = real_num + blank_num * 2;
    if (new_length > length)
    {
        printf("String length is not enough!\n");
        return;
    }
    int index_of_new = new_length;
    int index_of_old = real_num;
    while (index_of_old >= 0)
    {
        if (' ' != s[index_of_old])
        {
            s[index_of_new--] = s[index_of_old];
        }
        else
        {
            s[index_of_new--] = '0';
            s[index_of_new--] = '2';
            s[index_of_new--] = '%';
        }
        --index_of_old;
    }
    return ;
}

int main(int argc, const char *argv[])
{
    char s[14] = "hello world";
    printf("%s\n", s);
    replaceBlank(s, 13);
    printf("%s\n", s);
    
    return 0;
}
