#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>
#include "btree_print.h"
using namespace std;

/*
二叉树序列化、反序列化

    * 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化，
    * 以下代码全部实现了。
    * 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
    * 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
    * 比如如下两棵树
    *         __2
    *        /
    *       1
    *       和
    *       1__
    *          \
    *           2
    * 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
    *       
    * 
*/


// 先序遍历 序列化, 具体实现
void serialize_pre_impl(Node *p, queue<string> &que)
{
    que.push(p ? to_string(p->val) : "#");
    if (!p)
        return;

    serialize_pre_impl(p->left, que);
    serialize_pre_impl(p->right, que);
}

// 先序遍历 序列化
queue<string> serialize_pre(Node *p)
{
    queue<string> que;
    serialize_pre_impl(p, que);
    queue<string> ret = que;

    cout << "serialize pre: ";
    while (!que.empty())
    {
        cout << que.front() << " ";
        que.pop();
    }
    cout << endl;
    return ret;
}

// 中序遍历 序列化, 具体实现
void serialize_in_impl(Node *p, queue<string> &que)
{
    if (!p)
    {
        que.push("#");
        return;
    }
    serialize_in_impl(p->left, que);
    que.push(to_string(p->val));
    serialize_in_impl(p->right, que);
}

// 中序遍历 序列化
queue<string> serialize_in(Node *p)
{
    queue<string> que;
    serialize_in_impl(p, que);
    cout << "serialize in: ";
    while (!que.empty())
    {
        cout << que.front() << " ";
        que.pop();
    }
    cout << endl;
    return que;
}

// 后序遍历 序列化, 具体实现
void serialize_pos_impl(Node *p, queue<string> &que)
{
    if (!p)
    {
        que.push("#");
        return;
    }
    serialize_pos_impl(p->left, que);
    serialize_pos_impl(p->right, que);
    que.push(to_string(p->val));
}

// 后序遍历 序列化
queue<string> serialize_pos(Node *p)
{
    queue<string> que;
    serialize_pos_impl(p, que);
    queue<string> ret = que;

    cout << "serialize pos: ";
    while (!que.empty())
    {
        cout << que.front() << " ";
        que.pop();
    }
    cout << endl;
    return ret;
}

// 先序 反序列化, 具体实现
Node *reconstruct_btree_with_pre_serialize_impl(queue<string> &que)
{
    if (que.empty())
        return nullptr;

    string val = que.front();
    que.pop();
    if (val == "#")
        return nullptr;
    Node *p = new Node(atoi(val.data()));
    p->left = reconstruct_btree_with_pre_serialize_impl(que);
    p->right = reconstruct_btree_with_pre_serialize_impl(que);
    return p;
}

// 先序 反序列化
Node *reconstruct_btree_with_pre_serialize(queue<string> que)
{
    return reconstruct_btree_with_pre_serialize_impl(que);
}


// 后序 反序列化, 具体实现
Node *reconstruct_btree_with_pos_serialize_impl(stack<string> &s)
{
    if (s.empty())
        return nullptr;

    string val = s.top();
    s.pop();
    if (val == "#")
        return nullptr;

    // 出栈顺序：头右左
    Node *p = new Node(atoi(val.data()));
    p->right = reconstruct_btree_with_pos_serialize_impl(s);
    p->left = reconstruct_btree_with_pos_serialize_impl(s);
    return p;
}

// 后序 反序列化
Node *reconstruct_btree_with_pos_serialize(queue<string> que)
{
    if (que.empty())
        return nullptr;

    stack<string> s;
    // 左右头 -> 头右左。 即把头节点放在最前面，方便处理
    while (!que.empty())
    {
        s.push(que.front());
        que.pop();
    }

    return reconstruct_btree_with_pos_serialize_impl(s);
}


// 层序 序列化
queue<string> serialize_level(Node *p)
{
    queue<string> ret;
    if (!p)
        return ret;

    cout << "serialize level: ";
    queue<Node *> que;
    que.push(p);
    ret.push(to_string(p->val));
    cout << p->val << " ";
    while (!que.empty())
    {
        p = que.front();
        que.pop();

        // process


        if (p->left)
        {
            ret.push(to_string(p->left->val));
            que.push(p->left);
            cout << p->left->val << " ";
        }
        else
        {
            ret.push("#");
            cout << "# ";
        }

        if (p->right)
        {
            que.push(p->right);
            ret.push(to_string(p->right->val));
            cout << p->right->val << " ";
        }
        else
        {
            ret.push("#");
            cout << "# ";
        }
    }
    cout << endl;
    return ret;
}

// 层序 反序列化
Node *reconstruct_btree_with_level_serialize(queue<string> serial)
{
    if (serial.empty())
        return nullptr;

    queue<Node *> que;
    string val = serial.front();
    serial.pop();
    assert(val != "#"); // should not be happen
    Node *head = new Node(atoi(val.data()));
    que.emplace(head);
    while (!que.empty())
    {
        Node *p = que.front();
        que.pop();

        // process
        val = serial.front();
        serial.pop();
        p->left = (val == "#") ? nullptr : new Node(atoi(val.data()));

        val = serial.front();
        serial.pop();
        p->right = (val == "#") ? nullptr : new Node(atoi(val.data()));


        if (p->left)
            que.emplace(p->left);

        if (p->right)
            que.emplace(p->right);
    }

    return head;
}

#define ALG_TEST
#ifdef ALG_TEST

// for test
Node* generate(int level, int maxLevel, int maxValue) {
    int random = rand() % maxValue;

    if (level > maxLevel || random < (maxValue >> 1))
    {
        return nullptr;
    }
    Node *head = new Node(random);
    head->left = generate(level + 1, maxLevel, maxValue);
    head->right = generate(level + 1, maxLevel, maxValue);
    return head;
}

// for test
Node* generateRandomBST(int maxLevel, int maxValue) {
    return generate(1, maxLevel, maxValue);
}

// for test
bool isSameValueStructure(Node *head1, Node *head2) {
    if (head1 == nullptr && head2 != nullptr) {
        return false;
    }
    if (head1 != nullptr && head2 == nullptr) {
        return false;
    }
    if (head1 == nullptr && head2 == nullptr) {
        return true;
    }
    if (head1->val != head2->val) {
        return false;
    }
    return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->right, head2->right);
}

int main() 
{
    int maxLevel = 5;
    int maxValue = 100;
    int testTimes = 1000000;
    cout << "test begin" << endl;
    for (int i = 0; i < testTimes; i++) {
        Node *head = generateRandomBST(maxLevel, maxValue);
        queue<string> pre = serialize_pre(head);
        queue<string> pos = serialize_pos(head);
        queue<string> level = serialize_level(head);
        //printTree(head);
        Node *preBuild = reconstruct_btree_with_pre_serialize(pre);
        Node *posBuild = reconstruct_btree_with_pos_serialize(pos);
        Node *levelBuild = reconstruct_btree_with_level_serialize(level);
        if (!isSameValueStructure(preBuild, posBuild) || !isSameValueStructure(posBuild, levelBuild)) {
            cout << "Oops!" << endl;
            return 1;
        }
        cout << "test ok!" << endl;
    }
    cout << "test finish!" << endl;
    return 0;
}


#endif // ALG_TEST