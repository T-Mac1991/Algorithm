/*
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。

 

示例 1：

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。
示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。
示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。
 

提示：

1 <= prices.length <= 3 * 10^4
0 <= prices[i] <= 10^4

链接：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
通过找到波谷和下一个波峰，获取利润，
然后循环，得到最大利润

该方法不通用
*/
int max_profit(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    int val = INT32_MAX; //波谷的前一个值，用于定位波谷
    int i = 0; //波谷位置， p[i] < val && p[i] < p[i+1]
    int profit = 0;
    while (i < prices.size() - 1)
    {
        // 找到波谷i
        while (!(prices[i] < prices[i + 1] && prices[i] < val))
        {
            if (i == prices.size() - 1)
                break;

            // 不是波谷
            i++;
        }

        // 找到波峰 p[j] > p[j-1] && p[j] > p[j+1]
        int j = i;
        for (; j < prices.size() - 1; j++) // j: i的下一个波峰位置
        {
            if (prices[j+1] < prices[j])
                break;
        }

        val = prices[j];

        profit += (prices[j] - prices[i]);

        i = j + 1; //从波峰后继续找波谷
    }
    return profit;
}

/*
DP:

dp[i][k][0 or 1]: 第i天持有(1)/不持有(0)股票，最多交易k次，该题中k不限制次数
     k只有在买入的时候才变化，卖出是不变

     可能会觉得卖出时k减一，效果一样：这个不对的，因为交易是从buy开始的，如果buy不改变k，则会出现k次买卖+一次买入，即超过交易次数限制

1.第i天不持有股票的最大profit
  dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])
            即  max(不交易, 卖出股票)

2.第i天持有股票的最大profit
  dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])
            即  max(不交易, 买入股票)

因为k不限制次数，所以可以忽略k的影响，简化状态转移方程为：
  dp[i][0] = max(dp[i-1][0], dp[i-1][1] + price[i])
  dp[i][1] = max(dp[i-1][1], dp[i-1][0] - price[i])

3. 初始条件
  dp[0][0] = 0;
  dp[0][1] = -prices[0];


详解：https://labuladong.gitee.io/algo/di-ling-zh-bfe1b/yi-ge-fang-3b01b/
*/
int max_profit_DP(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[prices.size() - 1][0];
}

/*
DP(空间复杂度优化)
因为dp数组只和上一个状态相关，所以可以进行空间优化，只记录上一次持有/未持有股票的max值
*/
int max_profit_DP2(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    int dp_0 = 0;
    int dp_1 = -prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        int tmp_dp_0 = max(dp_0, dp_1 + prices[i]);
        dp_1 = max(dp_1, dp_0 - prices[i]);
        dp_0 = tmp_dp_0;
    }
    return dp_0;
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
        printf("%d, ", vec[i]);
    }
    printf("\n");
    return vec;
}


int main()
{
    srand(time(NULL));
    int testTime = 500000;
    int maxSize = 20;
    int maxValue = 20;
    int arr[20] = {0};
    for (int i = 0; i < testTime; i++)
    {
        vector<int> vec = generateRandomArray(maxSize, maxValue);
        int r1 = max_profit(vec);
        int r2 = max_profit_DP(vec);
        int r3 = max_profit_DP2(vec);
        if (r1 != r2 || r1 != r3)
        {
            cout << endl
                 << "r1: " << r1 << ", r2: " << r2 << ", r3: " << r3 << endl;
            cout << "Error" << endl;
            return 1;
        }
        cout << "ret: " << r1 << endl;
    }
    printf("finished!\n");
    return 0;
}

#endif // ALG_TEST
