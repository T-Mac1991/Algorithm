#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
计算字符串的最大回文
*/


/*
字符串预处理(使得能够统一处理奇数、偶数回文)：
1221 --> #1#2#2#1#
*/
string pre_process(string s)
{
    string s1;
    for (auto &it : s)
    {
        s1 += "#";
        s1 += it;
    }
    s1 += "#";
    return s1;
}

string pos_process(string s)
{
    string s1;
    for (int i = 1; i < s.size(); i+=2)
    {
        s1 += s[i];
    }
    return s1;
}

/*
计算最大回文：暴力解法
*/
string get_max_palindrome(string s)
{
    if (s.size() < 2)
        return s;

    s = pre_process(s);
    string ret;
    for (int i = 0; i < s.size(); i++)
    {
        int j = 1;
        while (i - j >= 0 && i + j < s.size())
        {
            if (s[i-j] == s[i+j])
            {
                j++;
            }
            else
            {
                break;
            }
        }
        if (ret.size() < (2*j - 1))
        {
            ret = s.substr(i - j + 1, (2*j - 1));
        }
    }

    ret = pos_process(ret);
    return ret;
}

/*
计算最大回文：暴力解法2
不做预处理
*/
string get_max_palindrome_impl(string &s, int i, int j)
{
    while (i >= 0 && j < s.size() && s[i] == s[j])
    {
        i--;
        j++;
    }
    string ret = s.substr(i + 1, j - i - 1);
    return ret;
}

string get_max_palindrome2(string s)
{
    if (s.size() < 2)
        return s;

    string ret;
    for (int i = 0; i < s.size() - 1; i++)
    {
        string s1 = get_max_palindrome_impl(s, i, i);
        string s2 = get_max_palindrome_impl(s, i, i + 1);
        if (s1.size() > s2.size() && s1.size() > ret.size())
            ret = s1;
        else if (s1.size() <= s2.size() && s2.size() > ret.size())
            ret = s2;
    }

    return ret;
}

/*
计算最大回文：Manacher算法
*/
void process(int &r, int &c, int i, int j, string &ret, string &s, vector<int> &arr)
{
    while (i - j >= 0 && i + j < s.size())
    {
        if (s[i-j] == s[i+j])
        {
            j++;
        }
        else
        {
            break;
        }
    }
    if (ret.size() < (2*j - 1))
    {
        ret = s.substr(i - j + 1, (2*j - 1));
    }
    arr[i] = j; //回文半径
    if (r < i + j - 1)
    {
        c = i;
        r = i + j - 1;
    }
}
string get_max_palindrome_Manacher(string s)
{
    if (s.size() < 2)
        return s;

    s = pre_process(s);
    int r = -1; //最大回文右边界
    int c = -1; //center中心点
    vector<int> arr(s.size(), 0); //回文半径数组
    arr[0] = 0;
    string ret;
    for (int i = 0; i < s.size(); i++)
    {
        // [         ]
        // L    C    R   i
        if (i > r) //i点在[L, R]外部，使用暴力解法
        {
            int j = 1;
            process(r, c, i, 1, ret, s, arr);
        }
        else //i点在[L, R]内部
        {
            int i2 = 2 * c - i; // i'

            // [                        ]
            // L   (  i'  ) C (  i  )   R
            // i'的回文在[L, R]内部，此时i的回文也会在[L, R]内部，i点的回文半径等于i'的回文半径，O(1)
            if (i + arr[i2] - 1 < r) 
            {
                arr[i] = arr[2 * c - i]; // arr[i] = arr[i']; // r, c 不变
                
            }
            // [                ]
            // (  i'  ) C (  i  )  
            // L          a     R      
            //i'的回文左边界和L重叠，则[a, R]是回文，然后再判断能否扩大
            else if ((i + arr[i2] - 1) == r) 
            {
                int j = r - i + 1;
                process(r, c, i, j, ret, s, arr);
            }
            //   [                ]
            // ( L i'   ) C (   i R )
            //i'的回文的一部分在[L, R]内部, 则i的回文半径为i-R部分的长度
            else 
            {
                arr[i] = r - i + 1; // r, c 不变
            }
        }
    }

    ret = pos_process(ret);
    return ret;
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

#include <chrono>
using namespace chrono;
int main()
{
    int possibilities = 2;
    int strSize = 100;
    int testTimes = 5000000;
    cout << ("test begin") << endl;
    srand(time(nullptr));
    for (int i = 0; i < testTimes; i++)
    {
        string str = getRandomString(possibilities, strSize);
        cout << "str: " << str << endl;

        auto t1 = chrono::system_clock::now();
        string s1 = get_max_palindrome(str);
        string s2 = get_max_palindrome2(str);
        auto t2 = chrono::system_clock::now();
        auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
        cout << "func1: " << duration.count() << "ms" << endl;
        
        t1 = chrono::system_clock::now();
        string s3 = get_max_palindrome_Manacher(str);
        t2 = chrono::system_clock::now();
        duration = chrono::duration_cast<milliseconds>(t2 - t1);
        cout << "func2: " << duration.count() << "ms" << endl;
        if (s1 != s2 || s1 != s3)
        {
            cout << "s1: " << s1 << endl;
            cout << "s2: " << s2 << endl;
            cout << "s3: " << s3 << endl;
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "test finish" << endl;
    return 0;
}

#endif // ALG_TEST