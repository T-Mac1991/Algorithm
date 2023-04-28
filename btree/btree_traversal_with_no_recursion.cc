#include <iostream>
#include <stack>
#include "btree_print.h"

/*
遍历二叉树：非递归方式, 基于栈实现

最好能画一下二叉树的每一步的流程，能很好的帮助理解代码
*/


/*
先序遍历：头左右
目的：出栈顺序为头左右（即先序遍历）
1. 头节点入栈
2. 节点pop出栈，打印(处理)头节点
3. 先右节点入栈，再左节点入栈 （因为栈FILO, 保证左先出栈）
4. goto step 2 循环处理
*/
void btree_pre_traversal(Node *p)
{
    if (!p)
        return;

    std::stack<Node*> s;
    s.push(p);   // step 1
    while (!s.empty())
    {
        p = s.top();
        std::cout << p->val << " ";
        s.pop();      // step 2
        if (p->right)
            s.push(p->right);
        if (p->left)
            s.push(p->left);

    }
    std::cout << std::endl;
}

/*
中序遍历：左头右
目的：出栈顺序为左头右（即中序遍历）
步骤：
  1. 首先把所有左节点入栈
  2. 节点出栈，打印(处理)节点
  3. 右节点入栈，goto step 1 循环处理
*/
void btree_in_traversal(Node *p) 
{
    if (!p)
        return;

    std::stack<Node *> s;
    while (!s.empty() || p)
    {
        if (p)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            std::cout << p->val << " ";
            p = p->right;
        }
    }
    std::cout << std::endl;
}

/*
后序遍历：左右头
目的：出栈顺序为左右头（即后序遍历）
实现方式：通过两个栈实现
主要流程：入栈1(顺序:头入，头出，左入，右入) => 入栈2(顺序:头右左) => 打印栈2
         注（个人理解）：可以从栈2往前梳理栈1的流程
入栈1详细步骤：
  1. 头节点入栈1
  2. 节点出栈1，入栈2
  3. 左节点入栈1，右节点入栈1 （注意结合流程来理解）
  4. goto step 2 循环处理
*/
void btree_pos_traversal(Node *p) 
{
    if (!p)
        return;

    std::stack<Node *> s1;
    std::stack<Node *> s2;
    s1.push(p);     // step 1
    while (!s1.empty())
    {
        p = s1.top();
        s2.push(p); // step 2
        s1.pop();

        if (p->left)
            s1.push(p->left);
        if (p->right)
            s1.push(p->right);
    }

    while (!s2.empty())
    {
        std::cout << s2.top()->val << " ";
        s2.pop();
    }
    std::cout << std::endl;
}

/*
后序遍历：左右头
目的：入栈顺序头右左，出栈顺序为左右头（即后序遍历）
步骤和中序遍历（非递归）有一点类似
  1. 先把所有left节点入栈
  2. 再把top的right节点入栈，重复步骤1
  3. 若无

步骤较难理解，建议结合实际示例，一步一步跟踪来理解
*/
void btree_pos_traversal_with_one_stack(Node *p) 
{
    if (!p)
        return;
    Node *lastOutNode = nullptr;  //上一个出栈的Node
    std::stack<Node *> s;
    s.push(p);
    while (!s.empty())
    {
        Node *cur = s.top();
        // 先判断left节点，
        if (cur->left && 
            cur->left != lastOutNode /*若相等，表示left已被处理过了，不需要再次入栈了*/ && 
            cur->right != lastOutNode /*若相等，表示right已被处理过了（先处理left，再处理right）*/ )
        {
            s.push(cur->left);
        }
        else if (cur->right &&
                 cur->right != lastOutNode /*若相等，表示right已被处理过了，不需要再次入栈了*/)
        {
            s.push(cur->right);
        }
        else
        {
            std::cout << cur->val << " ";
            s.pop();
            lastOutNode = cur;
        }
    }

    std::cout << std::endl;
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

    std::cout << "pos traversal 2: " << std::endl;
    btree_pos_traversal_with_one_stack(&head);
    std::cout << std::endl;

    return 0;
}