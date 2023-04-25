/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例 1：
   |                     __
   |         __         |  |__    __
   |   __   |  |__    __|  |  |__|  |__
   |__|__|__|__|__|__|__|__|__|__|__|__|

输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水。 
示例 2：

输入：height = [4,2,0,3,2,5]
输出：9


提示：

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105

链接：https://leetcode.cn/problems/trapping-rain-water
*/

#include <vector> 
#include <iostream>
using namespace std;

/*
暴力解法
*/
int trap(vector<int>& height) {
    int n = height.size();
    int res = 0;
    int l_max = height[0];
    for (int i = 1; i < n - 1; i++)
    {
        // 找右边最高的柱子
        int r_max = 0;
        for (int j = i; j < n; j++)
            r_max = max(r_max, height[j]);

        // 找左边最高的柱子
        l_max = max(l_max, height[i]);
        
        // 如果自己就是最高的话，
        // l_max == r_max == height[i]
        res += min(l_max, r_max) - height[i];
    }
    return res;
}

/*
备忘录
时间复杂度O(N)
空间复杂度O(N)
*/
int trap2(vector<int>& height) {
    if (height.size() <= 2)
        return 0;

    vector<int> l_max(height.size(), 0); // left max array
    l_max[0] = height[0];
    vector<int> r_max(height.size(), 0); // right max array
    r_max[height.size() - 1] = height[height.size() - 1];
    for (int i = 1; i < height.size(); i++)
        l_max[i] = max(l_max[i - 1], height[i]);
    for (int i = height.size() - 2; i >= 0; i--)
        r_max[i] = max(height[i], r_max[i + 1]);

    int ret = 0;
    for (int i = 1; i < height.size() - 1; i++)
    {
        int v = (min(l_max[i - 1], r_max[i + 1]) - height[i]);
        if (v > 0)
            ret += v;
    }
    return ret;
}

/*
双指针
详细说明: https://cloud.tencent.com/developer/article/1880920
时间复杂度O(N)
空间复杂度O(1)

初始状态：left->0, right->(n-1)
         l_max = height[0]
         r_max = height[n-1]
l_max, r_max谁小谁向中间移动（Why？ 因为接雨水的量，由矮的边界决定，忽略高的边）
循环
*/
int trap3(vector<int>& height) {
    if (height.size() <= 2)
        return 0;
    int left = 1;
    int right = height.size() - 2;
    int l_max = height[0];
    int r_max = height[height.size() - 1];
    int ret = 0;
    while (left <= right) //注意终止条件，包含=
    {
        if (l_max < r_max) 
        {
            l_max = max(l_max, height[left]); // 更新l_max
            ret += (l_max - height[left]);    // 当l_max小时，以l_max为高度计算雨水量
            left++;  // 向右移动
        }
        else 
        {
            r_max = max(r_max, height[right]); // 更新r_max
            ret += (r_max - height[right]);    // r_max较小，以r_max为高度计算雨水量
            right--; // 向左移动
        }
    }

    return ret;
}

/*
单调栈
时间复杂度O(N)
空间复杂度O(N)

   |                     __
   |         __         |  |__    __
   |   __   |  |__    __|  |  |__|  |__
   |__|__|__|__|__|__|__|__|__|__|__|__|

输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]

*/
#include <stack>
#include <algorithm>
int trap_with_stack(vector<int> height)
{
    if (height.size() <= 2)
        return 0;

    int ret = 0;
    stack<int> s;
    for (int i = 0; i < height.size(); i++)
    {
        while (!s.empty() && height[s.top()] < height[i])
        {
            int index = s.top();
            s.pop();
            if (s.empty()) //左右没有比index位置更高的点，退出循环
                break;

            int h = min(height[s.top()], height[i]);
            int distance = i - s.top() - 1; //两堵墙之间的距离
            ret += ((h - height[index]) * distance);
        }

        s.push(i);
    }
    return ret;
}

#define ALG_TEST
#ifdef ALG_TEST

vector<int> generateRandomArray(int maxSize, int maxValue) {
    int size = 0;
    while (size == 0)
    {
        size = rand() % (maxSize + 1);
    }

    vector<int> vec;
    for (int i = 0; i < size; i++)
    {
        vec.push_back(rand() % (maxValue + 1));
        printf("%d ", vec[i]);
    }
    printf("\n");
    return vec;
}


int main()
{
    srand(time(NULL));
    int testTime = 500000;
    int maxSize = 20;
    int maxValue = 10;
    int arr[20] = {0};
    for (int i = 0; i < testTime; i++)
    {
        vector<int> height = generateRandomArray(maxSize, maxValue);
        int r1 = trap(height);
        int r2 = trap2(height);
        int r3 = trap3(height);
        int r4 = trap_with_stack(height);
        if (r1 != r2 || r1 != r3 || r1 != r4)
        {
            for (int i = 0; i < height.size(); i++)
                cout << height[i] << " ";
            cout << endl
                 << "r1: " << r1 << ", r2: " << r2 << ", r3: " << r3 << ", r4: " << r4 << endl;
            cout << "Error" << endl;
            return 1;
        }
        else
            cout << "OK" << endl;
    }
    printf("finished!\n");
    return 0;
}
#endif // ALG_TEST
