/*
删除链表中的节点
有一个单链表的 head，我们想删除它其中的一个节点 node。

给你一个需要删除的节点 node 。你将 无法访问 第一个节点  head。

链表的所有值都是 唯一的，并且保证给定的节点 node 不是链表中的最后一个节点。

删除给定的节点。注意，删除节点并不是指从内存中删除它。这里的意思是：

给定节点的值不应该存在于链表中。
链表中的节点数应该减少 1。
node 前面的所有值顺序相同。
node 后面的所有值顺序相同。
自定义测试：

对于输入，你应该提供整个链表 head 和要给出的节点 node。node 不应该是链表的最后一个节点，而应该是链表中的一个实际节点。
我们将构建链表，并将节点传递给你的函数。
输出将是调用你函数后的整个链表。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
//找到应删除结点的前驱，并删除
//oj不认ListNode，故该方式不行
class Solution {
public:
    void deleteNode(ListNode* node) {
        //如何传入head？
        ListNode *head=NULL;
        ListNode *pos=head->next;
        ListNode *pre=head;
        for(;pos->next!=NULL;pre=pos,pos=pos->next)
        {
            if(pos->val==node->val)
            {
                pre->next=pos->next;
                //delete pos;
                break;
            }

        }
    }
};
*/

//直接利用应删除结点的指针，用后面的结点覆盖该结点
class Solution {
public:
    void deleteNode(ListNode* node) {
        //用后面的结点值覆盖该结点
        //理应删除后面那个节点，但考虑题目不要求，故不执行
        node->val=node->next->val;
        //ListNode *temp=list->next;
        node->next=node->next->next;
        //delete temp;
    }
};
