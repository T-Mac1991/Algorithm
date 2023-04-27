/*
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你应当 保留 两个分区中每个节点的初始相对位置。

示例 1：
输入：head = [1,4,3,2,5,2], x = 3
输出：[1,2,2,4,3,5]

示例 2：
输入：head = [2,1], x = 2
输出：[1,2]

提示：
链表中节点的数目在范围 [0, 200] 内
-100 <= Node.val <= 100
-200 <= x <= 200

链接：https://leetcode.cn/problems/partition-list
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
    ListNode* partition(ListNode* head, int x) {
        if (!head)
            return nullptr;

        ListNode dummy1, dummy2; //使用虚拟头结点，方便处理（不用考虑节点为null）
        ListNode *p1 = &dummy1; //小于x的链表
        ListNode *p2 = &dummy2; //大于等于x的链表
        ListNode *p = head;
        while (p != nullptr)
        {
            if (p->val < x)
            {
                p1->next = p;
                p1 = p1->next;
            }
            else
            {
                p2->next = p;
                p2 = p2->next;
            }

            // 断开原链表中的每个节点的 next 指针
            ListNode *tmp = p->next;
            p->next = nullptr;
            p = tmp;
        }

        p1->next = dummy2.next;
        return dummy1.next;
    }

/*
注意：两个分区中每个节点的初始相对位置可能会改变。
*/
    ListNode* partition2(ListNode* head, int x) {
        if (!head)
            return nullptr;

        ListNode *i = head; //
        while (i != nullptr)
        {
            // 得到第一个大于等于x的节点
            while (i && i->val < x)
                i = i->next;
            if (i == nullptr)
                break;

            // i节点之后得到第一个小于x的节点
            ListNode *j = i;
            while (j && j->val >= x)
                j = j->next;
            if (j == nullptr)
                break;

            // swap
            int val = i->val;
            i->val = j->val;
            j->val = val;
        }
        return head;
    }
};



// Test
int main()
{
    ListNode p6(2);
    ListNode p5(5, &p6);
    ListNode p4(2, &p5);
    ListNode p3(3, &p4);
    ListNode p2(4, &p3);
    ListNode p1(1, &p2);
    Solution s;
    //ListNode *p = s.partition(&p1, 3);
    ListNode *px = s.partition2(&p1, 3);

    return 0;
}