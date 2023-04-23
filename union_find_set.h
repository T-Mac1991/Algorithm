#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
/*
并查集：数组实现
Union(a, b): 把元素a和b所在的集合，合并为一个集合
Find(a, b): 查询元素a和b是否在同一个集合

a. a[i] < 0    //表示为头节点, 且abs(值)为set个数
b. a[i] >= 0   //表示父节点的index
*/

#include <iostream>
#include <vector>

using namespace std;

/*
空间复杂度很高
*/
class UnionFindSet
{
public:
    UnionFindSet(vector<vector<char>> v)
    {
        if (v.size() == 0)
            return;

        col = v[0].size();
        row = v.size();
        vec.assign(col * row, -1); //初始化为 -1（a[i] < 0 表示为头节点, 且abs(值)为set个数）
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[0].size(); j++) {
                if (v[i][j] == '1')
                {
                    ++set_size;
                    //vec[i][j] = -1;
                }
            }
        }
    }

    void Union(int row_a, int col_a, int row_b, int col_b)
    {
        if (row_a < 0 || row_b < 0 || 
            col_a < 0 || col_b < 0 || 
            row_a >= row || row_b >= row ||
            col_a >= col || col_b >= col)
        {
            return;
        }

        int a = row_a * col + col_a; // index of vec
        int b = row_b * col + col_b;
        int ha = findHead(a);
        int hb = findHead(b);
        if (ha == hb)
            return;

        assert(vec[ha] != hb);
        assert(vec[hb] != ha);

        if (vec[ha] > vec[hb]) // 因为是负数，集合a数量<集合b数量
        {
            vec[hb] += vec[ha]; //更新hb的set个数
            vec[ha] = hb;  //ha的父节点设为hb;
        }
        else //集合b数量<集合a数量
        {
            vec[ha] += vec[hb]; //更新ha的set个数
            vec[hb] = ha;  //hb的父节点设为ha;
        }

        --set_size;
    }

    int Count() 
    {
        return set_size;
    }

private:
    // return index
    int findHead(int index)
    {
        vector<int> indexs;
        //找到头节点索引index
        while (vec[index] >= 0)
        {
            indexs.push_back(index);
            index = vec[index];
        }

        //压缩路径：设置所有节点的父节点为头节点
        for (auto &it : indexs)
        {
            vec[it] = index;
        }

        return index;
    }

private:
    vector<int> vec;
    int col = 0;
    int row = 0;
    int set_size = 0;
};



/*
使用hashtable实现
效率最低
*/
#include <unordered_map>
class UnionFindSet2
{
public:
    UnionFindSet2(vector<vector<char>> v)
    {
        if (v.size() == 0)
            return;

        col = v[0].size();
        row = v.size();
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[0].size(); j++) 
            {
                if (v[i][j] == '1')
                {
                    ++set_size;
                    int index = i * row + j;
                    parent[index] = -1;
                }
            }
        }
    }

    void Union(int row_a, int col_a, int row_b, int col_b)
    {
        if (row_a < 0 || row_b < 0 || 
            col_a < 0 || col_b < 0 || 
            row_a >= row || row_b >= row ||
            col_a >= col || col_b >= col)
        {
            return;
        }

        int a = row_a * col + col_a; // index of array
        int b = row_b * col + col_b;
        if (parent.find(a) == parent.end() || parent.find(b) == parent.end())
            return;

        int ha = findHead(a);
        int hb = findHead(b);
        if (ha == hb)
            return;


        if (parent[ha] > parent[hb]) // 因为是负数，集合a数量<集合b数量
        {
            parent[hb] += parent[ha]; //更新hb的set个数
            parent[ha] = hb;  //ha的父节点设为hb;
        }
        else //集合b数量<集合a数量
        {
            parent[ha] += parent[hb]; //更新ha的set个数
            parent[hb] = ha;  //hb的父节点设为ha;
        }

        --set_size;
    }

    int Count() 
    {
        return set_size;
    }

private:
    // return index
    int findHead(int index)
    {
        vector<int> indexs;
        //找到头节点索引index
        while (parent[index] >= 0)
        {
            indexs.push_back(index);
            index = parent[index];
        }

        //压缩路径：设置所有节点的父节点为头节点
        for (auto &it : indexs)
        {
            parent[it] = index;
        }

        return index;
    }

private:
    int col = 0;
    int row = 0;
    int set_size = 0;

    //<节点index, 父节点index>，当节点为头节点时，存储了集合节点个数（负数）
    unordered_map<int, int> parent;  
};
