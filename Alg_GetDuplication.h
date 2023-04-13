#pragma once
#include <algorithm>

/*��һ������Ϊn����������������ֶ���0~n-1�ķ�Χ�ڡ�������ĳЩ�������ظ��ģ�
����֪���м��������ظ��ˣ�Ҳ��֪��ÿ�������ظ��˼��Σ����ҳ�����������һ��
�ظ������֡����磺������볤��Ϊ7������{2��3��1��0��2��5��3}����ô��Ӧ����
�����ظ�������2����3��*/

bool GetDuplication(int a[], int len, int *out)
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



