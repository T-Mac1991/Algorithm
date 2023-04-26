/*
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格，和一个整型 k 。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

 

示例 1：

输入：k = 2, prices = [2,4,1]
输出：2
解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
示例 2：

输入：k = 2, prices = [3,2,6,5,0,3]
输出：7
解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
     随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。
 

提示：

0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000

链接：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
错误思路1：
通过找到波谷和下一个波峰，获取利润，
然后循环，得到最大利润

prices = {18, 1, 12, 3, 2, 20, 15, 1, 15, 16, 15, 19} 
k: 1
时会得到错误答案 18，而正确答案为19


错误思路2：：
通过找到波谷和下一个最大的波峰，获取利润，
然后循环，得到最大利润

prices = {9, 0, 18, 20, 11, 5, 14, 5, 6, 10, 9, 6, 10, 18, 8, 14, 5, 7}
k: 18
仍旧得不到正确答案

结论：
这种通过波峰波谷的方式求解，不具有通用性，和k的次数关联很大，不好分析！
*/
int max_profit_err(vector<int> prices, int k)
{
    if (prices.size() <= 1)
        return 0;

    vector<int> max_price(prices.size(), 0); //i点右侧的最大price的索引index
    max_price[prices.size() - 1] = prices.size() - 1;
    for (int i = prices.size() - 2; i >= 0; i--)
    {
        //i点的最大值 = max(i点右侧的最大值, 当前股票价格)
        max_price[i] = prices[max_price[i + 1]] > prices[i] ? max_price[i + 1] : i;
    }

    int val = INT32_MAX; //波谷的前一个值，用于定位波谷
    int i = 0; //波谷位置， p[i] < val && p[i] < p[i+1]
    vector<int> profit;
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

        // 找到i后的最大波峰 
        val = prices[max_price[i]];

        profit.push_back(val - prices[i]);

        i = max_price[i] + 1; //从波峰后继续找波谷
    }

    //数据小时，使用deque或vector优于list；也可以用堆排序
    sort(profit.begin(), profit.end(), std::greater<int>());

    int max_profit = 0;
    for (int i = 0; i < k && i < profit.size(); i++)
    {
        max_profit += profit[i];
    }
    return max_profit;
}

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
  for (int k = 0; k <= k_max; k++)
  {
      // 处理 base case
      dp[0][k][0] = 0;
      dp[0][k][1] = -prices[0];
  }


详解：https://labuladong.gitee.io/algo/di-ling-zh-bfe1b/yi-ge-fang-3b01b/
*/
int max_profit_DP(vector<int> prices, int k_max)
{
    if (prices.size() <= 1)
        return 0;

    if (k_max > prices.size() / 2) {
        // 复用之前交易次数 k 没有限制的情况
        //return maxProfit_k_inf(prices);
    }

    // 置零
    vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(k_max + 1, vector<int>(2, 0)));

    // 上一行已实现这一步
    // for (int i = 0; i < prices.size(); i++)
    // {
    //     // 处理 base case
    //     dp[i][0][0] = 0;
    //     dp[i][0][1] = 0;  //这个值不会用到
    // }

    for (int k = 1; k <= k_max; k++)
    {
        // 处理 base case
        dp[0][k][0] = 0;
        dp[0][k][1] = -prices[0];
    }

    for (int i = 1; i < prices.size(); i++)
    {
        for (int k = 1; k <= k_max; k++)
        {
            dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
            dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
        }
    }
    return dp[prices.size() - 1][k_max][0];
}


int maxProfit_k_any(vector<int>& prices, int max_k) {
    int n = prices.size();
    if (n <= 0) {
        return 0;
    }

    if (max_k > n / 2) {
        // 复用之前交易次数 k 没有限制的情况
        //return maxProfit_k_inf(prices);
    }

    // base case：
    // dp[-1][...][0] = dp[...][0][0] = 0
    // dp[-1][...][1] = dp[...][0][1] = -infinity
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(max_k + 1, vector<int>(2)));
    // k = 0 时的 base case
    for (int i = 0; i < n; i++) {
        dp[i][0][1] = INT32_MIN;   //这个值不会用到
        dp[i][0][0] = 0;
    }

    for (int i = 0; i < n; i++){ 
        for (int k = max_k; k >= 1; k--) {
            if (i - 1 == -1) {
                // 处理 i = -1 时的 base case
                dp[i][k][0] = 0;
                dp[i][k][1] = -prices[i];
                continue;
            }
            dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
            dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);     
        }
    }
    return dp[n - 1][max_k][0];
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
        for (int k = 1; k <= vec.size() / 2 + 1; k++)
        {
            //int k = rand() % (vec.size() + 1);
            cout << "k: " << k << endl;
            int r1 = max_profit_DP(vec, k);
            int r2 = maxProfit_k_any(vec, k);
            if (r1 != r2)
            {
                cout << endl
                    << "r1: " << r1 << ", r2: " << r2 << endl;
                cout << "Error" << endl;
                return 1;
            }
            cout << "ret: " << r1 << endl;
        }
    }
    printf("finished!\n");
    return 0;
}

#endif // ALG_TEST
