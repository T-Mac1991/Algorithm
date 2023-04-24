#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

/*
求子串位置: 暴力解法
*/

int findsubstr(string s, string sub)
{
    if (s.empty() || sub.empty() || s.length() < sub.length())
        return -1;

    for (int i = 0; i < s.length() - sub.length() + 1; i++)
    {
        if (strncmp(&s[i], &sub[0], sub.length()) == 0)
            return i;
    }
    return -1;
}

/*
求子串位置: KMP算法
*/

// 获取next数组
// next数组元素：i位置之前的字符串，最大的 (前缀==后缀) 的长度
// 0 1 2 3 4 5
// a b a b c d
// next[4]的长度=2，即最大前缀/最大后缀="ab"
void get_next_arr(string &pat, vector<int> &next)
{
    next[0] = -1;
    if (pat.length() <= 1)
        return;

    next[1] = 0;
    int i = 2;  // 目前在哪个位置上求next数组的值
    int cn = 0; // 当前是pat的哪个位置的值在和i-1位置的字符比较

    // 状态转移方程
    // 初始设置i= 2； 
    // 当前pat开始比较的位置：cn = next[i-1] = next[1], 即0
    // next[i] = | 当pat[i-1] == pat[cn]时, next[i] = cn + 1
    //           | 当pat[i-1] != pat[cn]时, |  当cn > 0时，cn设置为next[cn], 然后再循环比较
    //                                      |  当cn == 0, 表示next[i]的最大前缀为0
    while (i < pat.length())
    {
        if (pat[i-1] == pat[cn]) //pat[i-1] == pat[cn]
        {
            next[i++] = ++cn; // next[i] = cn + 1; i++
        }
        else if (cn > 0) //当cn > 0时，cn设置为next[cn], 然后再循环比较
        {
            cn = next[cn];
        }
        else //当cn == 0, 表示next[i]的最大前缀为0
        {
            next[i++] = 0;
        }
    }
}

int findsubstr_with_KMP(string s, string pat)
{
    if (s.empty() || pat.empty() || s.length() < pat.length())
        return -1;

    vector<int> next(pat.length(), 0);
    get_next_arr(pat, next);

    int x = 0;
    int y = 0;
    while (x < s.length() && y < pat.length())
    {
        if (s[x] == pat[y]) // 相等，匹配下一个字符
        {
            x++;
            y++;
        }
        else if (next[y] == -1) //pat的第一个字符都不等于s[x], x右移一位
        {
            x++;
        }
        else // next[y] >= 0
        {
            y = next[y];   //下一次 从next[y]位置开始和s[x]比较  
        }
    }
    return y == pat.length() ? (x - y) : -1;
}


#define ALG_TEST
#ifdef ALG_TEST

string getRandomString(int possibilities, int size) {
    string ans((rand() % size) + 1, 0);
    for (int i = 0; i < ans.length(); i++) {
        ans[i] = (char) ((rand() % possibilities) + 'a');
    }
    return ans;
}

int main()
{
    int possibilities = 5;
    int strSize = 20;
    int matchSize = 5;
    int testTimes = 5000000;
    cout << "test begin" << endl;
    srand(time(nullptr));
    for (int i = 0; i < testTimes; i++)
    {
        string str = getRandomString(possibilities, strSize);
        string match = getRandomString(possibilities, matchSize);

        size_t pos1 = str.find(match);
        int pos2 = findsubstr_with_KMP(str, match);
        int pos3 = findsubstr(str, match);
        cout << "str: " << str << endl;
        cout << "match: " << match << endl;
        if (pos1 != pos2 || pos1 != pos3)
        {
            cout << pos1 << ", " << pos2 << ", " << pos3 << endl;
            cout << "Oops!" << endl;
            return 1;
        }
        cout << "ok" << endl;
    }
    cout << "test finish" << endl;
    return 0;
}
#endif // ALG_TEST