#include <iostream>
#include "btree_print.h"

/*
判断是否为满二叉树
*/


/*
方法一：
通过层序遍历获取树高度，判断总数是否==2^n-1
*/
bool isFullBT(Node *p)
{
    if (!p)
        return true;

    queue<Node *> que;
    que.push(p);
    int height = 0;
    int count = 0;
    Node *endnode = p;
    Node *next_endnode = nullptr;
    while (!que.empty())
    {
        p = que.front();
        ++count;
        que.pop();

        if (p->left)
        {
            que.push(p->left);
            next_endnode = p->left;
        }    
        if (p->right)
        {
            que.push(p->right);
            next_endnode = p->right;
        }

        if (p == endnode)
        {
            ++height;
            endnode = next_endnode;
            next_endnode = nullptr;
        }
    }

    int full_count = (1 << height) - 1;
    bool isFull = (full_count == count) ? true : false;
    cout << "count: " << count << "height: " << height << ", Is full: " << isFull << endl;
    return (full_count == count) ? true : false;
}

/*
方法二：
树型DP思路：
1. 分割为左右子树的子问题
2. 采用一个结构体作为返回值，该结构体需要能包括左右子树的结果集

*/
struct TreeInfo
{
    bool isFull; //是否为满二叉树
    int height;  //树高度
    TreeInfo() {}
    TreeInfo(bool full, int h) : isFull(full), height(h) {}
};

TreeInfo isFullBT2_impl(Node *p)
{
    if (!p)
        return TreeInfo(true, 0);

    TreeInfo left = isFullBT2_impl(p->left);
    TreeInfo right = isFullBT2_impl(p->right);
    
    TreeInfo info;
    info.height = max(left.height, right.height) + 1;

    if (left.isFull && right.isFull && left.height == right.height)
        info.isFull = true;
    else
        info.isFull =  false;

    return info;
}

bool isFullBT2(Node *p)
{
    TreeInfo info = isFullBT2_impl(p);
    cout << "height: " << info.height << ", isFull:" << info.isFull << endl;
    return info.isFull;
    // return (info.count == (1 << info.height) - 1) ? true : false;
}


/*
方法三：
树型DP思路：
1. 分割为左右子树的子问题
2. 采用一个结构体作为返回值，该结构体需要能包括左右子树的结果集

*/
struct TreeInfo2
{
    int height; //树高度
    int count;  //节点个数
    TreeInfo2() {}
    TreeInfo2(int h, int c) : height(h), count(c) {}
};

TreeInfo2 isFullBT3_impl(Node *p)
{
    if (!p)
        return TreeInfo2(0, 0);

    TreeInfo2 left = isFullBT3_impl(p->left);
    TreeInfo2 right = isFullBT3_impl(p->right);
    
    TreeInfo2 info;
    info.height = max(left.height, right.height) + 1;
    info.count = left.count + right.count + 1;
    return info;
}

bool isFullBT3(Node *p)
{
    TreeInfo2 info = isFullBT3_impl(p);
    cout << "Tree node count: " << info.count << ", height: " << info.height << endl;
    return (info.count == (1 << info.height) - 1) ? true : false;
}

#ifdef ALG_TEST

int main()
{
    int maxLevel = 5;
    int maxValue = 100;
    int testTimes = 1000000;
    cout << "test start..." << endl;
    for (int i = 0; i < testTimes; i++) {
        Node *head = generateRandomBST(maxLevel, maxValue);
        printTree(head);
        bool isFull1 = isFullBT(head);
        bool isFull2 = isFullBT2(head);
        bool isFull3 = isFullBT3(head);
        if (isFull1 != isFull2 || isFull1 != isFull3)
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finished" << endl;
    return 0;
}

#endif // ALG_TEST