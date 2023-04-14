#include <iostream>
#include "btree_print.h"

/*
遍历二叉树：递归方式
*/


//先序遍历：头左右
void btree_pre_traversal(Node *p)
{
    if (!p)
        return;
    std::cout << p->val << " ";
    btree_pre_traversal(p->left);
    btree_pre_traversal(p->right);
}

//中序遍历：左头右
void btree_in_traversal(Node *p) 
{
    if (!p)
        return;
    btree_in_traversal(p->left);
    std::cout << p->val << " ";
    btree_in_traversal(p->right);
}

//后序遍历：左右头
void btree_pos_traversal(Node *p) 
{
    if (!p)
        return;
    btree_pos_traversal(p->left);
    btree_pos_traversal(p->right);
    std::cout << p->val << " ";
}

int main()
{
    Node left2(4, nullptr, nullptr);
    Node right2(5, nullptr, nullptr);
    Node left1(2, &left2, &right2);

    Node left22(6, nullptr, nullptr);
    Node right22(7, nullptr, nullptr);
    Node right1(3, &left22, &right22);

    Node head(1, &left1, &right1);

    // btree:
    //     1
    //   2   3
    //  4 5 6 7

    // 1 2 4 5 3 6 7
    std::cout << "pre traversal: " << std::endl;
    btree_pre_traversal(&head);
    std::cout << std::endl;

    // 4 2 5 1 6 3 7
    std::cout << "in traversal: " << std::endl;
    btree_in_traversal(&head);
    std::cout << std::endl;

    // 4 5 2 6 7 3 1
    std::cout << "pos traversal: " << std::endl;
    btree_pos_traversal(&head);
    std::cout << std::endl;

    return 0;
}