#include <iostream>
#include <queue>
#include <algorithm>
#include "btree_print.h"
using namespace std;


int max_width(Node *p)
{
    if (!p)
        return 0;

    queue<Node *> que;
    que.push(p);
    int max_width = 0;
    while (!que.empty())
    {
        int width = que.size();
        if (width > max_width)
            max_width = width;
            
        for (int i = 0; i < width; i++)
        {
            p = que.front();
            que.pop();
            if (p->left)
                que.push(p->left);
            if (p->right)
                que.push(p->right);
        }
    }
}