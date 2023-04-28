/*
最长回文子串
*/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:

    string longestPalindrome_process(string s, int i, int j) {
        while (i >= 0 && j < s.size() && s[i] == s[j])
        {
            i--;
            j++;
        }
        return s.substr(i + 1, j - i - 1);
    }

    //双指针算法
    string longestPalindrome(string s) {
        string ret;
        for (int i = 0; i < s.size(); i++)
        {
            string s1 = longestPalindrome_process(s, i, i);
            string s2 = longestPalindrome_process(s, i, i + 1);
            string &s3 = s1.size() > s2.size() ? s1 : s2;
            if (ret.size() < s3.size())
                ret = s3;
        }
        return ret;
    }


    string pre_process(string s)
    {
        string ret = "#"; 
        for (auto &it : s)
        {
            ret += it;
            ret += "#";
        }
        return ret;
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

    //返回回文半径
    int longestPalindrome_process2(string s, int i, int offset = 0) {
        int j = i;
        while ((i - offset) >= 0 && (j + offset) < s.size() && s[i - offset] == s[j + offset])
        {
            i--;
            j++;
        }
        return (j - i) / 2;
    }
    /* 
    Manacher算法
    right: 回文最大右边界
    centre: 回文最大中点
    arr[i]: 回文半径数组, 第i点的回文半径
    i' : i点基于centre的对称点
    */
    string longestPalindrome_Manacher(string s) {
        int right = -1;  //最大回文右边界
        int centre = -1; //最大回文中点
        s = pre_process(s);
        vector<int> arr(s.size(), 1); //回文半径数组
        string pal; //longest Palindrome

        for (int i = 0; i < s.size(); i++)
        {
            // i 在 right 右边
            if (i > right)
            {
                int tmp = longestPalindrome_process2(s, i);
                if (tmp + i > right)
                {
                    //update
                    right = tmp + i - 1;
                    centre = i;
                }
                arr[i] = tmp;

                if (pal.size() < (tmp * 2 - 1))
                {
                    pal = s.substr(i - tmp + 1, tmp * 2 - 1);
                }
            }

            else 
            {
                int i2 = 2 * centre - i; // (i' + i)/2 == C
                int left = 2 * centre - right;
                // i'的回文在最大回文内部, i的回文半径=arr[i']
                // [ (  i' )     (  i  ) ]
                // L          C          R
                //if (i + arr[i2] - 1 < right) 
                if (i2 - arr[i2] + 1 > left)
                {
                    arr[i] = arr[i2];
                }
                // i'的回文有一部分在最大回文外部, i的回文半径=[i~R]
                //( [  i'   )     (    i   ] )
                //  L          C           R                
                else if (i2 - arr[i2] + 1 < left)
                {
                    arr[i] = right - i + 1;
                }
                //i'的回文左边界和L重叠，则[a, R]是回文，然后再判断能否扩大
                // [                ]
                // (  i'  ) C (  i  )  
                // L          a     R      
                else
                {
                    arr[i] = right - i + 1;
                    int tmp = longestPalindrome_process2(s, i, right - i);
                    if (tmp + i > right)
                    {
                        //update
                        right = tmp + i - 1;
                        centre = i;
                    }
                    arr[i] = tmp;

                    if (pal.size() < (tmp * 2 - 1))
                    {
                        pal = s.substr(i - tmp + 1, tmp * 2 - 1);
                    }
                }
            }

        }

        pal = pos_process(pal);
        return pal;
    }
};



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
#include <iostream>
using namespace chrono;
int main()
{
    int possibilities = 2;
    int strSize = 100;
    int testTimes = 5000000;
    cout << ("test begin") << endl;
    srand(time(nullptr));
    Solution s;
    for (int i = 0; i < testTimes; i++)
    {
        string str = getRandomString(possibilities, strSize);
        cout << "str: " << str << endl;
        auto t1 = chrono::system_clock::now();
        string s1 = s.longestPalindrome(str);
        auto t2 = chrono::system_clock::now();
        auto duration = chrono::duration_cast<milliseconds>(t2 - t1);
        cout << "func1: " << duration.count() << "ms" << endl;
        
        t1 = chrono::system_clock::now();
        string s2 = s.longestPalindrome_Manacher(str);
        t2 = chrono::system_clock::now();
        duration = chrono::duration_cast<milliseconds>(t2 - t1);
        cout << "func2: " << duration.count() << "ms" << endl;
        if (s1 != s2)
        {
            cout << "s1: " << s1 << endl;
            cout << "s2: " << s2 << endl;
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "test finish" << endl;
    return 0;
}

#endif // ALG_TEST