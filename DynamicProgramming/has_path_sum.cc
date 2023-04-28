/*
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点。

 

示例 1：


输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
输出：true
解释：等于目标和的根节点到叶节点路径如上图所示。
示例 2：


输入：root = [1,2,3], targetSum = 5
输出：false
解释：树中存在两条根节点到叶子节点的路径：
(1 --> 2): 和为 3
(1 --> 3): 和为 4
不存在 sum = 5 的根节点到叶子节点的路径。
示例 3：

输入：root = [], targetSum = 0
输出：false
解释：由于树是空的，所以不存在根节点到叶子节点的路径。
 

提示：

树中节点的数目在范围 [0, 5000] 内
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

链接：https://leetcode.cn/problems/path-sum
*/


/**
 * Definition for a binary tree node.
 */

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // DFS, 类似后序遍历
    // 注意targetSum可以为负数，不要以targetSum<0为递归结束点
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root)
            return false;

        //注意判断：必须为叶子结点
        if (targetSum - root->val == 0 && !root->left && !root->right) //base case
            return true;

        bool left = hasPathSum(root->left, targetSum - root->val);
        bool right = hasPathSum(root->right, targetSum - root->val);
        return (left || right) ? true : false;
    }

    // BFS
    bool hasPathSum2(TreeNode* root, int targetSum) {
        if (!root)
            return false;

        tuple<TreeNode *, int> tup = {root, root->val};  //{节点, 到达该节点的路径和}
        queue<tuple<TreeNode *, int>> que;
        que.push(tup);
        while (!que.empty())
        {
            tuple<TreeNode *, int> tup = que.front();
            que.pop();
            if (!get<0>(tup)->left && !get<0>(tup)->right && get<1>(tup) == targetSum)
                return true;

            if (get<0>(tup)->right)
                que.push(tuple<TreeNode *, int>(get<0>(tup)->right, get<1>(tup) + get<0>(tup)->right->val));
            if (get<0>(tup)->left)
                que.push(tuple<TreeNode *, int>(get<0>(tup)->left, get<1>(tup) + get<0>(tup)->left->val));                
        }
        return false;
    }
};


int main()
{
    TreeNode n1(7);
    TreeNode n2(2);
    TreeNode n3(11, &n1, &n2);
    TreeNode n4(4, &n3, nullptr);

    TreeNode n5(1);
    TreeNode n6(4, nullptr, &n5);
    TreeNode n7(13);
    TreeNode n8(8, &n7, &n6);
    TreeNode root(5, &n4, &n8);
    Solution s;
    bool ret = s.hasPathSum2(&root, 22);
    if (!ret)
    {
        cout << "error" << endl;
        return 1;
    }

    TreeNode n9(-3);
    TreeNode r2(-2, nullptr, &n9);
    ret = s.hasPathSum2(&r2, -5);
    if (!ret)
    {
        cout << "error" << endl;
        return 1;
    }

    //[1,-2,-3,1,3,-2,null,-1]
    return 0;
}