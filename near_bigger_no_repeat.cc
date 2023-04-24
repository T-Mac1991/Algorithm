/*
一个数组中每一个数，得到左边最近的比它大的和右边最近的比它大的数（小的话同理），代价尽量低
*/


#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
using namespace std;

/*
暴力解法
*/
map<int, int[2]> get_near_bigger(const vector<int> &arr)
{
    map<int, int[2]> m; // <index of i, bigger number index[left index, right index]>
    for (int i = 0; i < arr.size(); i++)
    {
        m[i][0] = -1;
        m[i][1] = -1;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i] < arr[j])
            {
                m[i][0] = j;
                break;
            }
        }

        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[i] < arr[j])
            {
                m[i][1] = j;
                break;
            }
        }
    }
    return m;
}



/*
单调栈
使用栈，记录最大值
注意：该方法不能有重复值
*/
map<int, int[2]> get_near_bigger2(const vector<int> &arr)
{
    map<int, int[2]> m; // <index of i, bigger number index[left index, right index]>
    stack<int> s;       // stack 记录arr的索引值index，栈底->栈顶为大->小

    for (int i = 0; i < arr.size(); i++)
    {
        while (!s.empty() && arr[s.top()] < arr[i])
        {
            int idx = s.top();
            s.pop();   // 把栈中小于 arr[i] 的值都pop出去
            // 左边比arr[idx]大的值为arr[s.top]栈顶， 右边比arr[idx]大的值为arr[i]
            m[idx][0] = s.empty() ? -1 : s.top();
            m[idx][1] = i;
        }

        s.push(i);
    }

    while (!s.empty())
    {
        int idx = s.top();
        s.pop();
        m[idx][0] = s.empty() ? -1 : s.top();
        m[idx][1] = -1;
    }

    return m;
}

/*
单调栈
使用栈，记录最大值
该方法可以有重复值，通过在栈中存储一个栈或链表或vector（保证先入后出即可），保存相同的值
*/
map<int, int[2]> get_near_bigger3(const vector<int> &arr)
{
    map<int, int[2]> m; // <index of i, bigger number index[left index, right index]>
    stack<stack<int>> s;       // stack 记录arr的索引值index，栈底->栈顶为大->小

    for (int i = 0; i < arr.size(); i++)
    {
        while (!s.empty() && arr[s.top().top()] < arr[i])
        {
            auto idx = s.top();
            s.pop();   // 把栈中小于 arr[i] 的值都pop出去
            // 左边比arr[idx]大的值为arr[s.top]栈顶， 右边比arr[idx]大的值为arr[i]
            while (!idx.empty())
            {
                m[idx.top()][0] = s.empty() ? -1 : s.top().top();
                m[idx.top()][1] = i;
                idx.pop();
            }
        }

        if (!s.empty() && arr[s.top().top()] == arr[i]) //相同值
        {
            s.top().push(i);
        }
        else
        {
            stack<int> s1;
            s1.push(i);
            s.push(s1);
        }
    }

    while (!s.empty())
    {
        auto idx = s.top();
        s.pop();
        while (!idx.empty())
        {
            m[idx.top()][0] = s.empty() ? -1 : s.top().top();
            m[idx.top()][1] = -1;
            idx.pop();
        }
    }

    return m;
}



#define ALG_TEST
#ifdef ALG_TEST

vector<int> generateRandomArray(int maxSize, int maxValue) {
    int random = rand() % maxSize;
    vector<int> arr(random, 0);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % (maxValue + 1);

#if 1
        if (i % 10 == 0 && i > 0)
            cout << endl;
        cout << arr[i] << " ";
#endif
    }
    cout << endl;
    return arr;
}

bool compare_map(map<int, int[2]> &m1, map<int, int[2]> &m2)
{
    if (m1.size() != m2.size())
        return false;

    for (int i = 0; i < m1.size(); i++)
    {
        if (m1[i][0] != m2[i][0] || m1[i][1] != m2[i][1])
            return false;
    }
    return true;
}

int main()
{
    int testTime = 100000;
    int maxSize = 100;
    int maxValue = 100;
    cout << "test begin" << endl;
    //srand(time(nullptr));
    for (int i = 0; i < testTime; i++)
    {
        vector<int> arr = generateRandomArray(maxSize, maxValue);

        int w = rand() % (arr.size() + 1);
        auto ans1 = get_near_bigger(arr);
        auto ans2 = get_near_bigger3(arr);
        if (compare_map(ans1, ans2) != true) {
            cout << ("Oops!") << endl;
            return 1;
        }
    }
    cout << "test finish" << endl;
    return 0;
}

#endif // ALG_TEST