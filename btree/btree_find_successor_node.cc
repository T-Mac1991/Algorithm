#include <iostream>
#include "btree_print.h"
using namespace std;

struct NodeEx : public Node
{
    NodeEx *left;
    NodeEx *right;
    NodeEx *parent;
    NodeEx(int data) : Node(data) {
        parent = nullptr;
    }
};


/*
查找中序遍历，任一节点的后继节点
1. 当节点right!=nullptr时，后继节点为right的最左节点
2. 当节点right==nullptr时，向上找到一个节点（需符合：该节点为其父节点的左孩子），该节点的父节点即为后继节点，否则为nullptr
*/

NodeEx *find_successor_node(NodeEx *p)
{
    if (!p)
        return nullptr;

    if (p->right)
    {
        p = p->right;
        while (p->left)
            p = p->left;
        return p;
    }
    else
    {
        while (p && p->parent)
        {
            if (p == p->parent->left)
                return p->parent;

            p = p->parent;
        }
        return p;

    }
}

void in_order(NodeEx *p)
{
    if (!p)
        return;

    in_order(p->left);
    cout << p->val << " ";
    in_order(p->right);
}

#ifdef ALG_TEST

int main()
{
    NodeEx *head = new NodeEx(6);
    head->parent = nullptr;
    head->left = new NodeEx(3);
    head->left->parent = head;
    head->left->left = new NodeEx(1);
    head->left->left->parent = head->left;
    head->left->left->right = new NodeEx(2);
    head->left->left->right->parent = head->left->left;
    head->left->right = new NodeEx(4);
    head->left->right->parent = head->left;
    head->left->right->right = new NodeEx(5);
    head->left->right->right->parent = head->left->right;
    head->right = new NodeEx(9);
    head->right->parent = head;
    head->right->left = new NodeEx(8);
    head->right->left->parent = head->right;
    head->right->left->left = new NodeEx(7);
    head->right->left->left->parent = head->right->left;
    head->right->right = new NodeEx(10);
    head->right->right->parent = head->right;

    cout << "in order: ";
    in_order(head);
    cout << endl;

    NodeEx *test = head->left->left;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->left->left->right;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->left;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->left->right;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->left->right->right;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->right->left->left;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->right->left;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->right;
    cout << test->val << " next: " << find_successor_node(test)->val << endl;
    test = head->right->right; // 10's next is null
    NodeEx *tmp = find_successor_node(test);
    if (!tmp)
        cout << (test->val + " next: null");
    else
            cout << test->val << " next: " << find_successor_node(test)->val;

    return 0;
}

#endif // ALG_TEST