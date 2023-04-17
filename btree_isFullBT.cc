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
树型DP，拆分为左右子树的子问题

*/
struct TreeInfo
{
    bool isFull;
    int height;
    int count;
    TreeInfo() {}
    TreeInfo(bool full, int h, int c) : isFull(full), height(h), count(c) {}
};

TreeInfo isFullBT2_impl(Node *p)
{
    if (!p)
        return TreeInfo(true, 0, 0);

    TreeInfo left = isFullBT2_impl(p->left);
    TreeInfo right = isFullBT2_impl(p->right);
    
    TreeInfo info;
    info.height = max(left.height, right.height) + 1;
    info.count = left.count + right.count + 1;

    if (left.height != right.height || 
        !left.isFull || 
        !right.isFull)
        info.isFull = false;
    else
    {
        info.isFull = (info.count == (1 << info.height) - 1) ? true : false;
    }

    return info;
}

bool isFullBT2(Node *p)
{
    TreeInfo info = isFullBT2_impl(p);
    cout << "Tree node count: " << info.count << ", height: " << info.height << ", isFull:" << info.isFull << endl;
    return info.isFull;
    // return (info.count == (1 << info.height) - 1) ? true : false;
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
        if (isFullBT(head) != isFullBT2(head))
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finished" << endl;
    return 0;
}

#endif // ALG_TEST