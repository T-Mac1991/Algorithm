#include <iostream>
#include <queue>
#include <algorithm>
#include "btree_print.h"
using namespace std;

/*
二叉树最大高度
*/

int max_height(Node *p)
{
    if (!p)
        return 0;

    int left = max_height(p->left);
    int right = max_height(p->right);
    int height = max(left, right) + 1;
    return height;
}

