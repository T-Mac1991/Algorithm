#include <iostream>
#include <vector>
using namespace std;

/*
计算岛的数量
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:
输入:
11110
11010
11000
00000

输出: 1

示例 2:
输入:
11000
11000
00100
00011

输出: 3


进阶：如何实现并行计算岛数量？
*/

//感染
//把相邻的点都感染成2
void infect(vector<vector<char>> &a, int i, int j)
{
    if (i < 0 || j < 0 || i >= a.size() || j >= a[0].size())
        return;

    if (a[i][j] == '1')
    {
        a[i][j] = '2';
        infect(a, i - 1, j);
        infect(a, i + 1, j);
        infect(a, i, j - 1);
        infect(a, i, j + 1);
    }
}

int number_of_island(vector<vector<char>> a)
{
    if (a.size() == 0)
        return 0;

    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == '1')
            {
                ++count;
                infect(a, i, j);
            }
        }
    }
    return count;
}


/*
进阶：使用并查集
*/
#include "union_find_set.h"
int number_of_island_with_unionfindset(vector<vector<char>> a)
{
    if (a.size() == 0)
        return 0;

    int count = 0;
    UnionFindSet obj(a);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == '1')
            {
                if (i > 0 && a[i-1][j] == '1')
                    obj.Union(i, j, i - 1, j);
                if (j > 0 && a[i][j-1] == '1')
                    obj.Union(i, j, i, j - 1);
            }
                
        }
    }
    return obj.Count();
}

int number_of_island_with_unionfindset2(vector<vector<char>> a)
{
    if (a.size() == 0)
        return 0;

    int count = 0;
    UnionFindSet2 obj(a);
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == '1')
            {
                if (i > 0 && a[i-1][j] == '1')
                    obj.Union(i, j, i - 1, j);
                if (j > 0 && a[i][j-1] == '1')
                    obj.Union(i, j, i, j - 1);
            }
                
        }
    }
    return obj.Count();
}



// int number_of_island_with_unionfindset(vector<vector<char>>& grid) {
//     if (grid.empty()) return 0;

//     int m = grid.size();
//     int n = grid[0].size();
//     int total = 0;

//     UnionFind uf(m * n);

//     for (int i = 0; i < m; ++i) {
//         for (int j = 0; j < n; ++j) {
//             if (grid[i][j] == '1') {
//                 total++;

//                 int p = i * n + j;
//                 if (i > 0 && grid[i-1][j] == '1')
//                     uf.unionElements(p, (i-1) * n + j);
//                 if (i < m - 1 && grid[i+1][j] == '1')
//                     uf.unionElements(p, (i+1) * n + j);
//                 if (j > 0 && grid[i][j-1] == '1')
//                     uf.unionElements(p, i * n + j - 1);
//                 if (j < n - 1 && grid[i][j+1] == '1')
//                     uf.unionElements(p, i * n + j + 1);
//             }
//         }
//     }

//     return uf.getCount();
// }


#define ALG_TEST
#ifdef ALG_TEST

vector<vector<char>> generateRandomMatrix(int row, int col) 
{
    vector<vector<char>> a(row, vector<char>(col));
    srand(time(nullptr));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            a[i][j] = (rand() & 0x0F) < 0x08 ? '1' : '0';
        }
    }
    return a;
}

#include <chrono>
using namespace chrono;

int main()
{
    int arr[] = {5, 10, 50, 100, 1000};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        int row = arr[i];
        int col = arr[i];
        vector<vector<char>> a1 = generateRandomMatrix(row, col);

        cout << "感染方法、并查集(map实现)、并查集(数组实现)的运行结果和运行时间" << endl;
        cout << "随机生成的二维矩阵规模 : " <<  row << " * " << col << endl;
        if (arr[i] <= 10)
        {
            for (int i = 0; i < a1.size(); i++)
            {
                for (int j = 0; j < a1[0].size(); j++) {
                    cout << a1[i][j] << " ";
                }
                cout << endl;
            }
        }


        cout << endl;

        auto start = std::chrono::system_clock::now();
        int count1 = number_of_island(a1);
        cout << "感染方法的运行结果: " << count1 << endl;
        auto end = std::chrono::system_clock::now();
        auto duration = duration_cast<milliseconds>(end - start); // 计算时间差
        cout << "感染方法的运行时间: " << duration.count() << " ms" << endl;
        cout << endl;

        start = chrono::system_clock::now();
        int count2 = number_of_island_with_unionfindset(a1);
        cout << "并查集(数组实现)的运行结果: " << count2 << endl;
        end = chrono::system_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "并查集(数组实现)的运行时间: " << duration.count() << " ms" << endl;
        cout << endl;


        start = chrono::system_clock::now();
        int count3 = number_of_island_with_unionfindset2(a1);
        cout << "并查集(哈希表实现)的运行结果: " << count3 << endl;
        end = chrono::system_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "并查集(哈希表实现)的运行时间: " << duration.count() << " ms" << endl;
        cout << endl;


        if (count1 != count2 || count1 != count3)
        {
            cout << "计算错误" << endl;
            return 1;
        }

        cout << "--------------------------------------------" << endl;
    }

    return 0;
}

#endif // ALG_TEST