#include <iostream>
#include <queue>
#include <list>
#include "btree_print.h"

/*
是否为平衡二叉树AVL
平衡二叉搜索树(平衡二叉树)AVL：
1. 可以是空树。
2. 假如不是空树，任何一个结点的左子树与右子树都是平衡二叉树，并且高度之差的绝对值不超过 1。
*/

/*
中序遍历判断是否为二叉搜索树
再判断左右子树高度差是否超过1
*/

void in_order(Node *p, queue<Node*> &que)
{
    if (!p)
        return;
    in_order(p->left, que);
    que.push(p);
    cout << p->val << " ";
    in_order(p->right, que);
}

int judge_height(Node* p)
{
    if (!p)
        return 0;
    int left = judge_height(p->left);
    int right = judge_height(p->right);
    if (left < 0 || right < 0)
        return -1;
    if (abs(left - right) > 1)
        return -1;
    int h = max(left, right) + 1;
    return h;
}

bool isBalanced(Node *p)
{
    if (!p)
        return true;

    // 中序遍历判断是否为二叉搜索树(小->大)
    queue<Node *> que;
    in_order(p, que);
    cout << endl;
    if (que.size() < 2)
        return true;

    int last = que.front()->val;
    que.pop();
    while (!que.empty())
    {
        int val = que.front()->val;
        if (val <= last)
            return false;
        last = val;
        que.pop();
    }

    int h = judge_height(p);
    if (h < 0)
        return false;

    return true;
}

/*
根据isBST(树型DP)函数改造
需要先理解isBST2()的代码
*/
struct TreeInfo
{
    int max;
    int min;
    int height;
    bool isBalanced;
    bool isNull;
    TreeInfo() { isNull = false; }
    TreeInfo(int max_val, int min_val, int h, bool balanced, bool isnull) :
        max(max_val), min(min_val), height(h), isBalanced(balanced), isNull(isnull) {}
};

TreeInfo isBalanced_impl(Node *p)
{
    if (!p)
        return TreeInfo(0, 0, 0, true, true);

    TreeInfo left = isBalanced_impl(p->left);
    TreeInfo right = isBalanced_impl(p->right);

    TreeInfo info;
    info.max = right.isNull ? p->val : right.max;
    info.min = left.isNull ? p->val : left.min;
    info.height = max(left.height, right.height) + 1;
    info.isBalanced = abs(left.height - right.height) < 2 &&   //高度差不超过1
                      left.isBalanced && right.isBalanced &&   //左右子树都为平衡二叉搜索树
                      (left.isNull || left.max < p->val) &&    //左子树为空 或者 左子树中的最大值小于节点值
                      (right.isNull || p->val < right.min);    //右子树为空 或者 右子树中的最小值大于节点值
    return info;
}

bool isBalanced2(Node *p)
{
    if (!p)
        return true;

    TreeInfo info = isBalanced_impl(p);
    cout << "max: " << info.max << ", min: " << info.min << ", height: " << info.height << ", balance: " << info.isBalanced << endl;
    return info.isBalanced;
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

        bool flag1 = isBalanced(head);
        bool flag2 = isBalanced2(head);
        cout << "isAVL: " << flag1 << endl;
        cout << "isAVL2: " << flag2 << endl;

        if (flag1 != flag2)
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finished" << endl;
    return 0;
}


#endif // ALG_TEST