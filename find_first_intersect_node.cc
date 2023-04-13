#include <iostream>

/*
1. 查找链表的环入口节点，若无环，返回nullptr
2. 两个链表中，查找第一个相交的节点。注意，链表可能有环，也可能是没有环
*/

struct Node
{
    struct Node *next;
    int val;
    Node(int v) : val(v) {}
};

/*
查找链表的环的任一节点，若无环，返回nullptr
*/
Node *find_any_loop_node(Node *head)
{
    if (!head || !head->next || !head->next->next)
        return nullptr;

    Node *fast = head->next->next;
    Node *slow = head->next;
    while (fast)
    {
        if (!fast->next || !fast->next->next)
            return nullptr;
        
        if (fast == slow)
        {
            return fast;
        }

        fast = fast->next->next;
        slow = slow->next;
    }
    return nullptr;
}

/*
查找链表的环入口节点，若无环，返回nullptr
采用快慢指针实现。
示例：
           9<-8<-7  <-快慢指针相遇点7
           |     ^
           v     |
  1->2->3->4->5->6
  |--len---|
                x: 环入口到相遇节点的距离，即4-->7的距离
                y: 相遇节点到环入口的距离，即7-->4的距离
步骤：
 若有环，快慢指针必会在环上相遇。相遇时
   环的长度       roll = x + y     (x: 环入口到相遇节点的距离；y: 相遇节点到环入口的距离)
   慢指针移动距离  slow = len + x   (len: head到环入口的距离)
   快指针移动距离  fast = len + x + n*roll
                  fast = 2*slow = 2*len + 2*x
   可推理得到   len = n*roll - x
                   = (n-1)*roll + roll - x
                   = (n-1)*roll + y
   所以，head到环入口的距离 == 相遇点到环入口点 + (n-1)*roll
        head和相遇点，一步一步next，必会在环入口相遇
*/
Node *find_first_loop_node(Node *head)
{
    if (!head || !head->next || !head->next->next)
        return nullptr;

    Node *fast = head->next->next;
    Node *slow = head->next;
    while (fast)
    {
        if (!fast->next || !fast->next->next)
            return nullptr;
        
        if (fast == slow)
        {
            fast = head;
            while (1)
            {
                if (fast == slow)
                    return fast;
                fast = fast->next;
                slow = slow->next;
            }
        }

        fast = fast->next->next;
        slow = slow->next;
    }
    return nullptr;
}

/*
两个 无环 链表中，查找第一个相交的节点
endnode：结束节点，默认为nullptr
*/
Node *find_first_intersect_node_no_loop(Node *p1, Node *p2, Node *same_endnode = nullptr)
{
    Node *end1 = nullptr;
    Node *end2 = nullptr;
    int n = 0;
    Node *p = p1;
    while (p != same_endnode)
    {
        end1 = p;
        p = p->next;
        ++n;
    }

    p = p2;
    while (p != same_endnode)
    {
        end2 = p;
        p = p->next;
        --n;
    }

    // 注意：当same_endnode不为nullptr时，end1和end2有可能不相等（B.3情况）
    if (!same_endnode && end1 != end2)
        return nullptr;

    Node *longlist = (n > 0) ? p1 : p2;
    Node *shortlist = (n > 0) ? p2 : p1;
    n = abs(n);
    while (n--)
    {
        longlist = longlist->next;
    }

    while (longlist)
    {
        if (longlist == shortlist)
            return longlist;
        longlist = longlist->next;
        shortlist = shortlist->next;
    }
    return nullptr; // not reach
}

/*
两个链表中，查找第一个相交的节点。注意，链表可能有环，也可能是没有环
有如下几种情况：
A. 当无环时
 1. 不相交      2. 相交
 p1  p2      p1 p2
  |  |        | |
  |  |         Y
  |  |         |

B. 当有环时
 1. 不相交     2. 相交点在环外      3.相交点在环内，则两个点都符合要求
 p1    p2      p1 p2                p1     p2
  |    |        | |                  |      |
  |    |         Y                   v      v
  |--| |--|      |--|                |<-<-<-|
  |--| |--|      |--|                v      ^
                                     |->->->|
*/

/*
方法一：
找到环入口点
*/
Node *find_first_intersect_node(Node *p1, Node *p2)
{
    if (!p1 || !p2)
        return nullptr;

    Node *p1loopnode = find_first_loop_node(p1);
    Node *p2loopnode = find_first_loop_node(p2);
    if (p1loopnode && p2loopnode) //都有环
    {
        if (p1loopnode == p2loopnode)
        {
            // B.2情况
            return find_first_intersect_node_no_loop(p1, p2, p1loopnode);
        }
        else
        {
            // 任一环入口点，继续next，若能找到另外一个环入口点，表示相交；
            //                       若重新回到当前环入口点，表示不相交
            Node *tmp = p1loopnode->next;
            while (tmp != p1loopnode)
            {
                if (tmp == p2loopnode)
                    return p1loopnode; // B.3情况
                tmp = tmp->next;
            }
            return nullptr; // B.1情况
        }
    }
    else if (!p1loopnode && !p2loopnode) //都无环
    {
        return find_first_intersect_node_no_loop(p1, p2);
    }
    return nullptr;
}

/*
方法二：
不需要找到环入口点
*/
Node *find_first_intersect_node2(Node *p1, Node *p2)
{
    if (!p1 || !p2)
        return nullptr;

    Node *p1loopnode = find_any_loop_node(p1);
    Node *p2loopnode = find_any_loop_node(p2);
    if (p1loopnode && p2loopnode) //都有环
    {
        /*
        遍历链表1，得到相交点x1(不需要找到环入口)，
        遍历链表2，找到相交点x2(不需要找到环入口)
         1. 若第二次到x1，还未发现等于x2的节点，表示不相交； B.1情况
         2. 发现有等于x2的节点，按无环方式处理（B.2/B.3情况）
        */
        Node *tmp = p1loopnode;
        do
        {
            if (tmp == p2loopnode)
                return find_first_intersect_node_no_loop(p1, p2, tmp);
            tmp = tmp->next;
        } while (tmp != p1loopnode);
        return nullptr;
    }
    else if (!p1loopnode && !p2loopnode) //都无环
    {
        return find_first_intersect_node_no_loop(p1, p2);
    }
    return nullptr;
}


void printlist(Node *p)
{
    while (p)
    {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

int main()
{
    // 1->2->3->4->5->6->7->null
    Node *head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = new Node(7);

    // 0->9->8->6->7->null
    Node *head2 = new Node(0);
    head2->next = new Node(9);
    head2->next->next = new Node(8);
    head2->next->next->next = head1->next->next->next->next->next; // 8->6
    printlist(head1);
    printlist(head2);
    Node *p1 = find_first_intersect_node(head1, head2);
    if (p1)
        std::cout << "p1: " << p1->val << std::endl;
    Node *p2 = find_first_intersect_node2(head1, head2);
    if (p2)
        std::cout << "p2: " << p2->val << std::endl;

    if (p1 != p2)
    {
        std::cout << "something error" << std::endl;
        return 1;
    }
    std::cout << "ok" << std::endl;

    // 1->2->3->4->5->6->7->4->->->
    head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = new Node(7);
    head1->next->next->next->next->next->next = head1->next->next->next; // 7->4

    // 0->9->8->2->->->
    head2 = new Node(0);
    head2->next = new Node(9);
    head2->next->next = new Node(8);
    head2->next->next->next = head1->next; // 8->2
    p1 = find_first_intersect_node(head1, head2);
    if (p1)
        std::cout << "p1: " << p1->val << std::endl;    
    p2 = find_first_intersect_node2(head1, head2);
    if (p2)
        std::cout << "p2: " << p2->val << std::endl;    
    if (p1 != p2)
    {
        std::cout << "something error" << std::endl;
        return 1;
    }
    std::cout << "ok" << std::endl;

    // 0->9->8->6->7->4->5->6->
    head2 = new Node(0);
    head2->next = new Node(9);
    head2->next->next = new Node(8);
    head2->next->next->next = head1->next->next->next->next->next; // 8->6
    p1 = find_first_intersect_node(head1, head2);
    if (p1)
        std::cout << "p1: " << p1->val << std::endl;
    p2 = find_first_intersect_node2(head1, head2);
    if (p2)
        std::cout << "p2: " << p2->val << std::endl;    
    if (p1 != p2)
    {
        std::cout << "something error" << std::endl;
        return 1;
    }
    std::cout << "ok" << std::endl;
    return 0;
}
