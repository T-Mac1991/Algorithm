#include <iostream>
#include <queue>
#include <unordered_map>

/*
1. 层序遍历
2. 获取最大层宽
*/

struct Node 
{
    struct Node *left;
    struct Node *right;
    int val;

    Node(int v, Node *l, Node *r) : 
        val(v), left(l), right(r) {}
};

/*
层序遍历, 依赖队列实现
步骤
1. 头节点入队
2. 节点pop，打印(处理)节点
3. 节点的left、right子节点入队
4. goto step 2
*/
void btree_level_traversal(Node *p)
{
    if (!p)
        return;

    std::queue<Node *> que;
    que.push(p);

    while (!que.empty())
    {
        p = que.front();
        que.pop();
        std::cout << p->val << " ";

        if (p->left)
            que.push(p->left);
        if (p->right)
            que.push(p->right);
    }

    std::cout << std::endl;
}

int get_max_width_with_hashtable(Node *p)
{
    if (!p)
        return 0;

    std::unordered_map<Node *, int> maplevel;
    maplevel.emplace(p, 1);
    int max_width = 0;
    int cur_level = 1;
    int cur_level_count = 0;

    std::queue<Node *> que;
    que.push(p);
    while (!que.empty())
    {
        p = que.front();
        std::cout << p->val << " ";
        que.pop();

        int cur_node_level = maplevel.find(p)->second;
        if (p->left)
        {
            que.push(p->left);
            maplevel.emplace(p->left, cur_node_level + 1);
        }
        if (p->right)
        {
            que.push(p->right);
            maplevel.emplace(p->right, cur_node_level + 1);
        }

        // 注意：需要在que.push后
        if (cur_level == cur_node_level)
        {
            ++cur_level_count;
        }
        else
        {
            max_width = std::max(max_width, cur_level_count);
            ++cur_level;
            cur_level_count = 1;
        }
    }

    // 最后一层未判断，所以最后需要判断一次
    max_width = std::max(max_width, cur_level_count);
    std::cout << "\nmax width: " << max_width << std::endl;
    return max_width;
}

int get_max_width_without_hashtable(Node *p)
{
    if (!p)
        return 0;

    std::queue<Node *> que;
    que.push(p);
    Node *cur_level_end = p;
    Node *next_level_end = nullptr;
    int max_width = 0;
    int cur_level_count = 0;
    while (!que.empty())
    {
        p = que.front();
        std::cout << p->val << " ";
        que.pop();

        ++cur_level_count;

        if (p->left)
        {
            que.push(p->left);
            next_level_end = p->left;
        }
        if (p->right)
        {
            que.push(p->right);
            next_level_end = p->right;
        }

        // 注意：需要在que.push后
        if (p == cur_level_end)
        {
            max_width = std::max(cur_level_count, max_width);
            cur_level_count = 0;
            cur_level_end = next_level_end;
            next_level_end = nullptr;
        }
    }
    //max_width = std::max(cur_level_count, max_width); 不需要
    std::cout << "\nmax width: " << max_width << std::endl;
    return max_width;
}


#include <chrono>

// for test
Node* generate(int level, int maxLevel, int maxValue) 
{
    int random = rand() % maxValue;
    if (level > maxLevel || (level > (maxLevel >> 1) && random < (maxValue >> 1)))
    {
        return nullptr;
    }
    Node *head = new Node(random,
                          generate(level + 1, maxLevel, maxValue),
                          generate(level + 1, maxLevel, maxValue));
    return head;
}

Node* generateRandomBT(int maxLevel, int maxValue) {
    srand(time(nullptr));
    return generate(1, maxLevel, maxValue);
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

    std::cout << "level traversal: ";
    btree_level_traversal(&head);
    std::cout << std::endl;

    std::cout << "get max level width test: " << std::endl;
    int maxLevel = 10;
    int maxValue = 100;
    int testTimes = 1000000;
    for (int i = 0; i < testTimes; i++) {
        Node* head = generateRandomBT(maxLevel, maxValue);
        if (get_max_width_with_hashtable(head) != get_max_width_without_hashtable(head)) {
            std::cout << "Oops!" << std::endl;
            return 1;
        }
        std::cout << "test OK" << std::endl;
    }

    std::cout << "finished!" << std::endl;
    return 0;
}