
#include <iostream>
#include <algorithm>

/*
在一个长度为n的数组里的所有数字都在0~n-1的范围内。数组中某些数字是重复的，
但不知道有几个数字重复了，也不知道每个数字重复了几次，请找出数组中任意一个
重复的数字。例如：如果输入长度为7的数组{2，3，1，0，2，5，3}，那么对应的输
出是重复的数字2或者3。
*/

bool get_duplication(int a[], int len, int *out)
{
    for (int i = 0; i < len; i++)
    {
        while (a[i] != i)
        {
            if (a[i] == a[a[i]])
            {
                *out = a[i];
                return true;
            }
            else
            {
                std::swap(a[i], a[a[i]]);
            }
        }
    }
    return false;
}

int main()
{
    int arr[] = {2, 3, 1, 0, 2, 5, 3};
    int out = 0;
    bool ret = get_duplication(arr, sizeof(arr) / sizeof(arr[0]) , &out);
    std::cout << "duplication num: ";
    if (ret)
        std::cout << out << std::endl;
    else
        std::cout << "null" << std::endl;
    return 0;
}

