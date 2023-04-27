/*
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：

输入：lists = []
输出：[]
示例 3：

输入：lists = [[]]
输出：[]
 

提示：

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4

链接：https://leetcode.cn/problems/merge-k-sorted-lists
*/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// struct greater_node
// {
//     bool operator()(ListNode* x, ListNode* y)
//     {
//         return x->val > y->val;
//     }
// };

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;

        ListNode dummy;
        ListNode *p = &dummy;

        //采用大根堆保存
        priority_queue<ListNode*, vector<ListNode*>, function<bool(ListNode*, ListNode*)>> que(
            [] (ListNode* a, ListNode* b) { return a->val > b->val; });
        //priority_queue<ListNode *, vector<ListNode*>, greater_node> que; 
        for (int i = 0; i < lists.size(); i++)
        {
            if (lists[i])
            {
                que.push(lists[i]);
            }
        }

        while (!que.empty())
        {
            ListNode *tmp = que.top();
            p->next = tmp;
            p = p->next;
            que.pop();
            tmp = tmp->next;
            if (tmp)
                que.push(tmp);

            p->next = nullptr;
        }

        return dummy.next;
    }
};



int main()
{
    vector<ListNode *> vec;
   
    // [[1,4,5],[1,3,4],[2,6]]
    ListNode p3(5);
    ListNode p2(4, &p3);
    ListNode p1(1, &p2);

    ListNode p33(5);
    ListNode p22(4, &p33);
    ListNode p11(1, &p22);

    ListNode p222(5);
    ListNode p111(1, &p222);
    vec.push_back(&p1);
    vec.push_back(&p11);
    vec.push_back(&p111);

    Solution s;
    ListNode *p = s.mergeKLists(vec);
    while (p && p->next)
    {
        if (p->val > p->next->val)
        {
            cout << "error" << endl;
            return 1;
        }
        p = p->next;
    }
    cout << "OK" << endl;
    return 0;
}