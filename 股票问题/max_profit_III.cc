/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1:

输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。   
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。   
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
示例 3：

输入：prices = [7,6,4,3,1] 
输出：0 
解释：在这个情况下, 没有交易完成, 所以最大利润为 0。
示例 4：

输入：prices = [1]
输出：0

链接：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
DP:

dp[i][k][0 or 1]: 第i天持有(1)/不持有(0)股票，最多交易k次，该题中k=2
     k只有在买入的时候才变化，卖出是不变

     可能会觉得卖出时k减一，效果一样：这个不对的，因为交易是从buy开始的，如果buy不改变k，则会出现k次买卖+一次买入，即超过交易次数限制

1.第i天不持有股票的最大profit
  dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])
            即  max(不交易, 卖出股票)

2.第i天持有股票的最大profit
  dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])
            即  max(不交易, 买入股票)

状态转移方程为：
  dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i])
  dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i])

3. 初始条件
  dp[0][1][0] = 0;
  dp[0][1][1] = -prices[0];


详解：https://labuladong.gitee.io/algo/di-ling-zh-bfe1b/yi-ge-fang-3b01b/
*/
int max_profit_DP(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    int k = 2;
    vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(k+1, vector<int>(2, 0)));
    dp[0][0][0] = 0;
    dp[0][1][0] = 0;
    dp[0][1][1] = -prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
        for (int k = 1; k < 3; k++)
        {
            dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
            dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
        }
    }
    return dp[prices.size() - 1][2][0];
}

/*
DP(空间复杂度优化)
因为dp数组只和上一个状态相关，所以可以进行空间优化，只记录上一次持有/未持有股票的max值
*/
int max_profit_DP2(vector<int> prices)
{
    if (prices.size() <= 1)
        return 0;

    int dp_k1_0 = 0;  // [k-1][0]
    int dp_k_0 = 0;   // [k][0]
    int dp_k_1 = -prices[0]; // [k][1]
    for (int i = 1; i < prices.size(); i++)
    {
        for (int k = 1; k < 3; k++)
        {
            int tmp1 = max(dp_k_0, dp_k_1 + prices[i]);
            int tmp2 = max(dp_k_1, dp_k1_0 - prices[i]);
            dp_k1_0 = dp_k_0;
            dp_k_0 = tmp1;
            dp_k_1 = tmp2;
        }
    }
    return dp_k_0;
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
        int r1 = max_profit_DP(vec);
        int r2 = max_profit_DP2(vec);
        if (r1 != r2)
        {
            cout << endl
                 << "r1: " << r1 << ", r2: " << r2 << endl;
            cout << "Error" << endl;
            return 1;
        }
        cout << "ret: " << r1 << endl;
    }
    printf("finished!\n");
    return 0;
}

#endif // ALG_TEST
