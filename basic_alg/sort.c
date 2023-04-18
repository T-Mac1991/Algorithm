#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    if (a == b)
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void BubbleSort(int a[], int len)
{
    for (int i = len; i > 0; i--)
    {
        int flag = 0; // swap flag
        for (int j = 1; j < i; j++)
        {
            if (a[j] < a[j-1])
            {
                swap(&a[j], &a[j - 1]);
                flag = 1;
            }    
        }

        if (flag == 0)
            return;
    }
}

void InsertSort(int a[], int len)
{
    for (int i = 1; i < len; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[j] > a[j+1])
                swap(&a[j], &a[j + 1]);
            else
                break;
        }
    }
}


/*
快排：
随机选一个数（时间复杂度为O(logN)）作为基准值，和尾数swap 
小于基准值的放前面，大于基准值的放后面，最后把基准值放中间
然后循环左右两部分
*/
void QuickSort_Impl(int a[], int left, int right)
{
    if (left >= right)
        return;

    int idx = left + rand() % (right - left + 1);
    swap(&a[idx], &a[right]);
    printf("select: %d\n", a[right]);

    int i = left - 1;
    for (int j = left; j <= right - 1; j++)
    {
        if (a[j] <= a[right])
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[right]);

    QuickSort_Impl(a, left, i);
    QuickSort_Impl(a, i + 1 + 1, right);
}



int partition(int a[], int low, int high)
{
    if (low >= high)
        return;

    int i = low + (rand() % (high - low + 1));
    swap(&a[i], &a[high]);
    int pivot = a[high];
    i = low - 1;// 小于pivot的边界索引
    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(&a[j], &a[i]);
        }
    }

    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void QuickSort(int a[], int len)
{
    QuickSort_Impl(a, 0, len-1);
}



#define ALG_TEST
#ifdef ALG_TEST


int generateRandomArray(int arr[], int maxSize, int maxValue) {
    int size = 0;
    while (size == 0)
    {
        size = rand() % (maxSize + 1);
    }
    
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (maxValue + 1) - rand() % (maxValue);
        printf("%d ", arr[i]);
    }
    printf("\n");
    return size;
}

int main()
{
    srand(time(NULL));
    int testTime = 500000;
    int maxSize = 20;
    int maxValue = 100;
    int arr[20] = {0};
    for (int i = 0; i < testTime; i++)
    {
        int len = generateRandomArray(arr, maxSize, maxValue);
        // BubbleSort(arr, len);
        // InsertSort(arr, len);
        QuickSort(arr, len);
        for (int i = 1; i < len; i++)
        {
            if (arr[i-1] > arr[i])
            {
                printf("error!\n");
                return 1;
            }
        }
        printf("sort %d ok\n", i);
    }
    printf("finished!\n");
    return 0;
}

#endif // ALG_TEST