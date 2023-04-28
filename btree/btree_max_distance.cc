#include <iostream>
#include "btree_print.h"

/*
二叉树最大路径
*/

/*
暴力计算任一两个节点的距离
1. 得到所有节点的parent
2. 节点p1到根节点的所有节点ht
3. 节点2向上遍历，判断是否在ht中（找到最小公共祖先）
4. 计算距离
*/
#include <unordered_set>
void get_parents(Node *p, unordered_map<Node *, Node*> &parents)
{
    if (!p)
        return;
    if (p->left)
    {
        parents[p->left] = p;
        get_parents(p->left, parents);
    }   
    if (p->right)
    {
        parents[p->right] = p;
        get_parents(p->right, parents);
    }
}

int get_distance(Node *p, Node *p1, Node *p2, unordered_map<Node *, Node*> &parents)
{
    if (!p1 || !p2)
        return 0;

    unordered_set<Node *> sets;
    Node *pTmp = p1;
    do
    {
        sets.emplace(pTmp);
        pTmp = parents[pTmp];
    } while (pTmp != p);

    pTmp = p2;
    do
    {
        if (sets.find(pTmp) != sets.end())
            break;
        pTmp = parents[pTmp];
    } while (pTmp != p);

    Node *pLowestAncestor = pTmp; // 最小公共祖先

    int count = 1;
    while (p1 != pLowestAncestor)
    {
        count++;
        p1 = parents[p1];
    }
    while (p2 != pLowestAncestor)
    {
        count++;
        p2 = parents[p2];
    }
    return count;
}

int get_max_distance1(Node *p)
{
    if (!p)
        return 0;

    unordered_map<Node *, Node*> parents;
    parents[p] = p;
    get_parents(p, parents);
    int max_distance = 1;
    vector<Node *> vec(parents.size(), nullptr);
    int i = 0;
    for (auto &it1 : parents)
    {
        vec[i++] = it1.first;
    }

    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = i + 1; j < vec.size(); j++)
        {
            max_distance = max(max_distance, get_distance(p, vec[i], vec[j], parents));
        }
    }
        
    return max_distance;
}

/*
树型DP
*/
struct Info
{
    int height;  // 树高度
    int max_dis; // max distance
    Info() : height(0), max_dis(0) {}
};

Info process(Node *p)
{
    if (!p)
        return Info();

    Info left = process(p->left);
    Info right = process(p->right);
    Info info;
    info.height = max(left.height, right.height) + 1;
    info.max_dis = max(left.height + right.height + 1, max(left.max_dis, right.max_dis));
    return info;
}

int get_max_distance(Node *p)
{
    Info i = process(p);
    return i.max_dis;
}



#ifdef ALG_TEST
int main()
{


    int maxLevel = 10;
    int maxValue = 100;
    int testTimes = 100000;
    cout << "test start..." << endl;
    for (int i = 0; i < testTimes; i++) {
        Node *head = generateRandomBST(maxLevel, maxValue);
        printTree(head);
        int r1 = get_max_distance1(head);
        int r2 = get_max_distance(head);
        if (r1 != r2)
        {
            cout << "Oops!" << endl;
            return 1;
        }
    }
    cout << "finished" << endl;
    return 0;
}
#endif // ALG_TEST