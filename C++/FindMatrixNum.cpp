//题目:
//  给你一个二维数组，其中二维数组按行从左到右递增，按列从上到下递增
//  传入一个参数num，用于查找此num是否在二维数组中，如果存在返回true
//  否则返回false
//思路:
//  从右上角的点开始查找，这是最优解
bool Find(int* matrix, int rows, int columns, int number)
{
    bool found = false;
    if (matrix == NULL || rows <= 0 || columns <= 0)
        return found;
    int row = 0;
    int column = columns -1;
    while (row < rows && column >= 0)
    {
        if (*(matrix + row * columns + column) == number)
        {
            found = true;
            break;
        }
        if (*(matrix + row * columns + column) > number)
            --column;
        else
            ++row;
    }
    return found;
}
