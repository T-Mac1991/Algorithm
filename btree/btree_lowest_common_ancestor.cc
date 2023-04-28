#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "btree_print.h"
using namespace std;
/*
求两个节点的最小公共祖先lowest common ancestor
*/


//中序遍历，得到所有节点的父节点
void in_order(Node *p, unordered_map<Node *, Node *> &parentmap)
{
    if (!p)
        return;

    in_order(p->left, parentmap);
    if (p->left)
        parentmap.emplace(p->left, p);

    //cout << p->val << " ";

    in_order(p->right, parentmap);
    if (p->right)
        parentmap.emplace(p->right, p);
}

/*
1. 中序遍历一次，使用HashTable所有父节点
2. 记录节点p1的到根节点的路径到unordered_set(Hash Table)
3. 从节点p2到根节点的路径中，判断是否已经在unordered_set中

时间复杂度O(N)，空间复杂度O(N)
*/
Node *get_lowest_common_ancestor_use_hashtable(Node *head, Node *p1, Node *p2)
{
    if (!head || !p1 || !p2)
        return nullptr;

    unordered_map<Node *, Node *> parentmap; // <节点, 父节点>
    unordered_set<Node *> node_path;  // 节点到根节点的路径
    parentmap.emplace(head, head);    // 根节点的parent是本身
    in_order(head, parentmap);        // 中序遍历获取所有节点的父节点

    node_path.emplace(p1);
    do
    {
        node_path.emplace(parentmap[p1]);
        p1 = parentmap[p1];
    } while (p1 != head);

    do
    {
        if (node_path.find(p2) != node_path.end())
            return p2;
        p2 = parentmap[p2];
    } while (p2 != head);

    return head;
}

/*
树型DP思路：
1. 分割为左右子树的子问题
2. 采用一个结构体作为返回值，该结构体需要能包括左右子树的结果集

左神：面试中的大部分树的问题，可以使用树型DP的思想解决

代码比较好理解，直接看代码
*/
struct FindInfo //定义左右子树返回数据的结构体
{
    bool findA;
    bool findB;
    Node *res;
    FindInfo(bool a = false, bool b = false, Node* r = nullptr) :
        findA(a), findB(b), res(r) {}
};

FindInfo process_with_tree_DP(Node *p, Node *p1, Node *p2)
{
    if (!p)
        return FindInfo(false, false, nullptr);

    FindInfo info;
    FindInfo ileft = process_with_tree_DP(p->left, p1, p2);
    FindInfo iright = process_with_tree_DP(p->right, p1, p2);
    info.findA = (p == p1 || ileft.findA || iright.findA) ? true : false;
    info.findB = (p == p2 || ileft.findB || iright.findB) ? true : false;

    // this is not correctly
    // if (info.findA && info.findB) //注意顺序问题：当找到最小祖先res，res的父节点、祖父节点...都会进入这个条件
    //     info.res = p;         //找到res
    // else if (ileft.res)
    //     info.res = ileft.res; //res向上传递
    // else if (iright.res)
    //     info.res = iright.res;//res向上传递

    if (ileft.res)
        info.res = ileft.res; //res向上传递
    else if (iright.res)
        info.res = iright.res;//res向上传递
    else if (info.findA && info.findB) //必须先判断前两个条件
        info.res = p;         //找到res
    return info;
}

Node *get_lowest_common_ancestor_with_tree_DP(Node *head, Node *p1, Node *p2)
{
    return process_with_tree_DP(head, p1, p2).res;
}



/*
递归实现，不依赖hash table实现（代码简洁，但不好理解）
 btree:
          1
       /     \
     2         3
   /  \       / \
  4    5     6   7
 / \  / \   / \
 8 9 10 11 12 13

需要考虑两种情况：
1. p1是p2的祖先 或 p2是p1的祖先
    eg: p1=5, p2=10
    process函数：
        1->2->4->8, 节点8的left和right皆为null，所以节点8也为null。同理节点9也为null => 节点4=null => 
        节点2.left=null     |
        节点2.right==p1(5)  | 根据(left ? left : right) => 节点2=p1 => 节点1.left = p1
        同理，节点1.right可以推导出为null
        节点1.left=p1     |
        节点1.right=null  | 根据(left ? left : right) => 节点1=p1 => 推导结束，祖先=p1

2. p1和p2需要向上查找祖先
    eg: p1=4，p2=13
    proces函数：
        节点1.left=p1     |
        节点1.right=p2    | (left && right) => 直接返回祖先(当前节点)
    祖先=1
*/
Node *process_with_recursion(Node *p, Node *p1, Node *p2)
{
    if (!p || p == p1 || p == p2) //判断条件：发现p1/p2，直接返回，否则返回nullptr
        return p;

    Node *left = process_with_recursion(p->left, p1, p2);    //递归查找左子树
    Node *right = process_with_recursion(p->right, p1, p2);  //递归查找右子树
    if (left && right) // 左右子树分别找到了p1和p2，则当前节点p为最小祖先（对应情况2）
        return p;

    return left ? left : right; //左右子树其中一个找到了p1/p2，另一个未找到(null), 返回找到的p1/p2
}

Node *get_lowest_common_ancestor_with_recursion(Node *head, Node *p1, Node *p2)
{
    // 从head开始，向下查找
    return process_with_recursion(head, p1, p2);
}



#define ALG_TEST
#ifdef ALG_TEST



// for test
void fillPrelist(Node *head, vector<Node*> &arr) {
    if (head == nullptr) {
        return;
    }
    arr.push_back(head);
    fillPrelist(head->left, arr);
    fillPrelist(head->right, arr);
}

// for test
Node* pickRandomOne(Node *head) {
    if (head == nullptr) {
        return nullptr;
    }
    vector<Node*> arr;
    fillPrelist(head, arr);
    int randomIndex = rand() % arr.size();
    return arr[randomIndex];
}

int main() {
    srand(time(NULL)); 
    int maxLevel = 4;
    int maxValue = 100;
    int testTimes = 1000000;
    for (int i = 0; i < testTimes; i++) {
        Node *head = generateRandomBST(maxLevel, maxValue);
        Node *o1 = pickRandomOne(head);
        Node *o2 = pickRandomOne(head);

        Node *p1 = get_lowest_common_ancestor_use_hashtable(head, o1, o2);
        Node *p2 = get_lowest_common_ancestor_with_tree_DP(head, o1, o2);
        Node *p3 = get_lowest_common_ancestor_with_recursion(head, o1, o2);
        if (p1 != p2 || p1 != p3)
        {
            cout << "p1: " << p1->val;
            cout << ", p2: " << p2->val;
            cout << ", p3: " << p3->val << endl;
            cout << "Oops!" << endl;
            return 1;
        }
        cout << "round " << i << ": ok" << endl;
    }
    cout << "finish!";
    return 0;
}
#endif // end of ALG_TESTs