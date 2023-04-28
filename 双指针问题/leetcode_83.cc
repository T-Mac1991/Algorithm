/*
删除排序链表中的重复元素

给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。

示例 1：
输入：head = [1,1,2]
输出：[1,2]

示例 2：
输入：head = [1,1,2,3,3]
输出：[1,2,3]
 

提示：

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列

链接：https://leetcode.cn/problems/remove-duplicates-from-sorted-list
*/

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
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head)
            return nullptr;

        ListNode *p1 = head; // p1相同点的第一个节点
        ListNode *p2 = head;
        while (p1 && p1->next)
        {
            // p1相同点的第一个节点
            while (p1 && p1->next && p1->val != p1->next->val)
                p1 = p1->next;
            if (!p1 || !p1->next)
                break;

            p2 = p1->next;
            while (p2 && p2->next && p2->val == p2->next->val)
                p2 = p2->next;

            p1->next = p2 ? p2->next : nullptr;
        }
        return head;
    }

    ListNode* deleteDuplicates2(ListNode* head) {
        if (!head)
            return nullptr;

        ListNode *fast = head; // p1相同点的第一个节点
        ListNode *slow = head;
        while (fast)
        {
            if (fast->val != slow->val)
            {
                slow->next = fast;
                slow = slow->next;
            }

            fast = fast->next;
        }

        if (!fast)
            slow->next = nullptr;
        return head;
    }
};

// Test
int main()
{
    ListNode p8(4);
    ListNode p7(4, &p8);
    ListNode p6(3, &p7);
    ListNode p5(3, &p6);
    ListNode p4(2, &p5);
    ListNode p3(2, &p4);
    ListNode p2(2, &p3);
    ListNode p1(1, &p2);
    Solution s;
    //ListNode *p = s.partition(&p1, 3);
    ListNode *px = s.deleteDuplicates2(&p1);

    return 0;
}