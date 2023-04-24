/*
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值 。

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

示例 2：

输入：nums = [1], k = 1
输出：[1]

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sliding-window-maximum

*/


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

// 暴力的对数器方法
vector<int> right(vector<int> &arr, int w) {
    if (w == 0)
        return vector<int>();

    if (arr.size() <= 1)
        return arr;

    int N = arr.size();
    vector<int> res(N - w + 1);
    int index = 0;
    int L = 0;
    int R = w - 1;
    while (R < N) {
        int max_val = arr[L];
        for (int i = L + 1; i <= R; i++) {
            max_val = max(max_val, arr[i]);

        }
        res[index++] = max_val;
        L++;
        R++;
    }
    return res;
}

/*
滑动窗口求最大值
使用双向队列实现。
*/
vector<int> max_sliding_window(vector<int> &nums, int k)
{
    if (k == 0)
        return vector<int>();
    if (nums.size() <= 1)
        return nums;

    deque<int> deq;
    vector<int> max_nums;
    for (int i = 0; i < nums.size(); i++)
    {
        while (!deq.empty() && nums[deq.back()] < nums[i])  //deque不为空且deque的末尾值小于nums[i], pop_back
            deq.pop_back();

        deq.push_back(i);  //后端插入索引i
        if ((i - deq.front() + 1) > k) //判断窗口是否超过k
        {
            deq.pop_front(); //窗口超过k, 把左侧值的pop
        }
        if (i >= k - 1) //判断窗口大小是否到达k
            max_nums.push_back(nums[deq.front()]); //deque的左侧值即为最大值
    }
    return max_nums;
}

#define ALG_TEST
#ifdef ALG_TEST

vector<int> generateRandomArray(int maxSize, int maxValue) {
    int random = rand() % maxSize;
    vector<int> arr(random, 0);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % (maxValue + 1);

#if 0
        if (i % 10 == 0 && i > 0)
            cout << endl;
        cout << arr[i] << " ";
#endif
    }
    cout << endl;
    return arr;
}



int main()
{
    int testTime = 100000;
    int maxSize = 100;
    int maxValue = 100;
    cout << "test begin" << endl;
    srand(time(nullptr));
    for (int i = 0; i < testTime; i++)
    {
        vector<int> arr = generateRandomArray(maxSize, maxValue);

        int w = rand() % (arr.size() + 1);
        vector<int> ans1 = max_sliding_window(arr, w);
        vector<int> ans2 = right(arr, w);
        if (ans1 != ans2) {
            cout << ("Oops!") << endl;
            return 1;
        }
    }
    cout << "test finish" << endl;
    return 0;
}

#endif //ALG_TEST