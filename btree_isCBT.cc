#include <iostream>
#include <queue>
#include <algorithm>
#include "btree_print.h"
using namespace std;
/*
判断是否为完全二叉树
*/

/*
通用解法：采用树型DP思路：分为左右子树的子问题
(感觉不如解法二容易理解)
*/
struct Info
{
    int height; //树高度
    bool isCBT; //是否为完全二叉树
    bool isFull;//是否为满二叉树
    Info(int h = 0, bool cbt = false, bool full = false) : 
        height(h), isCBT(cbt), isFull(full) {}
};

Info isCBT_impl(Node *p)
{
    if (!p)
        return Info(0, true, true);

    Info info;
    Info left = isCBT_impl(p->left);
    Info right = isCBT_impl(p->right);
    info.isFull = (left.isFull && right.isFull && (left.height == right.height));

    info.isCBT = false;
    if (info.isFull)
    {
        info.isCBT = true;
    }
    else
    {
        if ((left.isCBT && right.isCBT) &&
            ((left.isFull && right.isCBT && (left.height == right.height)) ||
             (left.isCBT && right.isFull && (left.height == right.height + 1)) ||
             (left.isFull && right.isFull && (left.height == right.height + 1)))) 
        {
            info.isCBT = true;
        }
    }

    info.height = max(left.height, right.height) + 1;

    return info;
}

bool isCBT(Node *p)
{
    if (!p)
        return true;

    Info info = isCBT_impl(p);
    cout << "isCBT" << info.isCBT << endl;
    return info.isCBT;
}

/*
解法二：
利用queue层序遍历
当 left==null && right!=null时，
   或者leaf标记==true，left或right不为null（左右子树层高大于1）
*/
bool isCBT2(Node *p)
{
    if (!p)
        return true;

    queue<Node *> que;
    que.push(p);
    bool leaf = false;
    while (!que.empty())
    {
        p = que.front();
        que.pop();
        if ((!p->left && p->right) ||        // left为空，right不为空，不符合CBT要求
            (leaf && (p->left || p->right))) // leaf标记==true，left或right不为null（左右子树层高大于1）
        {
            return false;
        }

        if (p->left)
            que.push(p->left);
        if (p->right)
            que.push(p->right);

        if (!p->left || !p->right)
            leaf = true; // p的下一层发现了叶子节点
    }
    cout << "isCBT2: true" << endl;
    return true;
}

#ifdef ALG_TEST

int main()
{
    int maxLevel = 5;
    int maxValue = 100;
    int testTimes = 1000000;
    for (int i = 0; i < testTimes; i++) {
        Node *head = generateRandomBST(maxLevel, maxValue);
        printTree(head);
        if (isCBT(head) != isCBT2(head))
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finish!" << endl;
    return 0;
}

#endif // ALG_TEST
