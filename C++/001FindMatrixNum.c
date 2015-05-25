//题目:
//  给你一个二维数组，其中二维数组按行从左到右递增，按列从上到下递增
//  传入一个参数num，用于查找此num是否在二维数组中，如果存在返回true
//  否则返回false
//思路:
//  从右上角的点开始查找，这是最优解

#include <stdio.h>
#include <stdlib.h>

//注意：c里面没有bool类型
int FindMatrixNum(int* matrix, int rows, int columns, int number)
{
    int found = 0;
    if (matrix == NULL || rows <= 0 || columns <= 0)
        return found;
    int row = 0;
    int column = columns -1;
    while (row < rows && column >= 0)
    {
        if (*(matrix + row * columns + column) == number)
        {
            found = 1;
            break;
        }
        if (*(matrix + row * columns + column) > number)
            --column;
        else
            ++row;
    }
    return found;
}


int main(int argc, const char *argv[])
{
    int matrix[4][4] = {
        {1, 3, 7, 9},
        {2, 6, 8, 10},
        {3, 7, 11, 34},
        {4, 9, 12, 35}
    };
    
    while (1)
    {
        int i;
        scanf("%d", &i);
        if (FindMatrixNum((int*)matrix, 4, 4, i))
        {
            printf("%d\n", i);
        }
        else
        {
            printf("Not found!\n");
        }
    }

    
    return 0;
}



