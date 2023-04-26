/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。


示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
 

提示：

1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4

链接：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
备忘录
记录右侧的最大值
*/
int max_profit(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    vector<int> max_price(prices.size(), 0); //i点右侧的最大price
    max_price[prices.size() - 1] = prices[prices.size() - 1];
    for (int i = prices.size() - 2; i >= 0; i--)
    {
        //i点的最大值 = max(i点右侧的最大值, 当前股票价格)
        max_price[i] = max(max_price[i + 1], prices[i]);
    }

    int max_profit = 0;
    for (int i = 0; i < prices.size(); i++)
    {
        max_profit = max(max_profit, max_price[i] - prices[i]);
    }
    return max_profit;
}


/*
DP: 交易一次

dp[i][k][0 or 1]: 第i天持有(1)/不持有(0)股票，最多交易k次
        注意：只有在买入股票时，k才会减一；
                   卖出股票时，k不变

              可能会觉得卖出时k减一，效果一样：这个不对的，因为交易是从buy开始的，如果buy不改变k，则会出现k次买卖+一次买入，即超过交易次数限制

1. 第i天未持有股票的最大profit, 二维中的1/0分别表示最大交易次数1/0
  dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
             即 max(第i天未交易, 第i天卖出股票)
  dp[i][0][0] = 0  //最大交易次数为0，所以最大profit也为0

2. 第i天持有股票的最大profit：
  dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])
             即 max(第i天未交易, 第i天买入股票)  
             这里在i天买入股票（一次交易），则第i-1天最多交易次数k = 第i天最多交易次数(1) - 1次 = 0
  因为dp[i][0][0] = 0，所以：
  dp[i][1][1] = max(dp[i-1][1][1], 0 - prices[i])


最终状态转移方程：
  dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
  dp[i][1][1] = max(dp[i-1][1][1], -prices[i])

  可以发现，现在发现 k 都是 1，不会改变，即 k 对状态转移已经没有影响了，进一步简化为：
    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
    dp[i][1] = max(dp[i-1][1], -prices[i])

3. 初始状态：
  dp[0][0] = 0
  dp[0][1] = -prices[0]


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
        dp[i][1] = max(dp[i - 1][1], -prices[i]);
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
        dp_1 = max(dp_1, -prices[i]);
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
            for (int i = 0; i < vec.size(); i++)
                cout << vec[i] << " ";
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
