
#include <iostream>
#include <algorithm>

/*
��һ������Ϊn����������������ֶ���0~n-1�ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�
����֪���м��������ظ��ˣ�Ҳ��֪��ÿ�������ظ��˼��Σ����ҳ�����������һ��
�ظ������֡����磺������볤��Ϊ7������{2��3��1��0��2��5��3}����ô��Ӧ����
�����ظ�������2����3��
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

