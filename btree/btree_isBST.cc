#include <iostream>
#include <queue>
#include <list>
#include "btree_print.h"

/*
判断是否为搜索二叉树
搜索二叉树：一棵二叉树，可以为空；如果不为空，满足以下性质：
  非空左子树的所有键值小于其根结点的键值。 
  非空右子树的所有键值大于其根结点的键值。
  左、右子树都是二叉搜索树。
*/

/*
中序遍历，判断是否符合要求:
若顺序为小->大，则符合BST要求；
否则不是BST
*/
void btree_in_order(Node *p, list<Node*> &lst)
{
    if (!p)
        return;

    btree_in_order(p->left, lst);
    lst.push_back(p);
    btree_in_order(p->right, lst);
}

bool isBST(Node *p)
{
    list<Node *> lst;
    btree_in_order(p, lst);
    if (lst.size() < 2)
        return true;

    auto last = lst.begin();
    auto it = lst.begin();
    cout << (*it)->val << " ";
    it++;
    for (; it != lst.end(); ++it)
    {
        cout << (*it)->val << " ";
        if ((*last)->val >= (*it)->val)
        {
            cout << "BST: 0" << endl;
            return false;
        }
        last = it;
    }

    cout << "BST: 1" << endl;
    return true;
}


/*
树型DP思路
1. 分割为左右子树的子问题
2. 采用一个结构体作为返回值，该结构体需要能包括左右子树的结果集
*/
struct TreeInfo
{
    int max;
    int min;
    bool bst;
    bool isNull;
    TreeInfo() {}
    TreeInfo(int max_val, int min_val, bool flag, bool isnull = false) : max(max_val), min(min_val), bst(flag), isNull(isnull) {}
};

TreeInfo isBST2_impl(Node *p)
{
    if (!p)
        return TreeInfo(0, 0, true, true);

    TreeInfo left = isBST2_impl(p->left);
    TreeInfo right = isBST2_impl(p->right);
    TreeInfo info;
    info.max = right.isNull ? p->val : right.max;
    info.min = left.isNull ? p->val : left.min;
    // 判断是否为BST
    info.bst = (left.bst && right.bst &&                 //左右子树都是BST
                (left.isNull || p->val > left.max) &&    //left为空 或者 节点值大于左子树中的最大值
                (right.isNull || p->val < right.min));   //right为空 或者 节点值小于右子树中的最小值
    info.isNull = false;
    return info;
}

bool isBST2(Node *p)
{
    if (!p)
        return true;

    TreeInfo info = isBST2_impl(p);
    cout << "min: " << info.min << ", max: " << info.max << ", BST: " << info.bst << endl;
    return info.bst;
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
        bool flag = isBST(head);
        bool flag2 = isBST2(head);
        if (flag != flag2)
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finished" << endl;
    return 0;
}

#endif // ALG_TEST