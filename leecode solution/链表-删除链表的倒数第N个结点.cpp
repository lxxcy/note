/*
删除链表的倒数第N个节点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

示例 1：

输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]
 

提示：

链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 

进阶：你能尝试使用一趟扫描实现吗？

*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/*
//【成功】
//第一遍扫描获取长度，第二次扫描则确定位置并进行删除
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //获取链表长度sz
        //定位到倒数第n个
        int i=0;
        ListNode *pos=head;
        while(pos!=NULL) 
        {
            i++;
            pos=pos->next;
        }

        if(head->next==NULL && n==1)    //处理只有一个结点的链表
            return NULL;

        pos=new ListNode;
        pos->next=head;         //让pos成为head的前驱，就不需要再对末尾结点进行判断
        for(int j=i+1;j>n+1;j--)
            pos=pos->next;      //定位到倒数第n个结点的前驱
        
        //ListNode *temp=pos->next;
        if(pos->next!=head)
            pos->next=pos->next->next;  //仅用该语句进行删除的缺点：如果删除的是第一个结点head，将导致无法进行下去
        //delete temp;
        else
            return head->next;  //即逻辑删除head结点，使用其后继作为head

        
        return head;
    }
};
*/


/*
//【失败】
//快慢指针，在扫描第n个结点时设置一个新指针开始扫描
//处理只有一个结点的链表，删除出现问题
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *pos=head;
        int sz=1;
        for(;pos->next!=NULL;sz++,pos=pos->next);
        pos=head;
        for(;sz-n>0;sz--)
            pos=pos->next;
        if(pos->next!=NULL)
        {
            pos->val=pos->next->val;
            pos->next=pos->next->next;
    }
        else
        {
            pos=NULL;
        }
        return head;
    }
};
*/


//【成功】
//处理只有一个结点的链表时，删除容易出现问题
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //双指针，在第n次扫描时，加入另一个指针
        ListNode *scan=head;
        ListNode *pos,*pre=NULL;    //用pre保存pos前驱结点
        for(;scan!=NULL;scan=scan->next)
        {
            n--;//注意n--与判断语句的顺序
            if(n==0)        //n递减到0时，若以此时scan扫描到的结点序号为1，则head为倒数第n个结点
                pos=head;
            if(n<0)
            {
                pre=pos;        //pos的前驱
                pos=pos->next;
            }
        }
        if(pos->next!=NULL)     //pos不是最后一个结点时，即使删除head结点，也能进行
        {
            pos->val=pos->next->val;
            pos->next=pos->next->next;
    }
        else                    //处理最后一个结点
        {
            //pos=NULL;//这个判断逻辑不正确，只是将变量pos的指向置空
            
            if(pre==NULL)//也可以用head->next==NULL,处理仅有一个结点的情况
                head=NULL;
            else        //说明结点数大于1，则前驱结点有效，应该删除前驱的后继（最后一个结点）
                pre->next=NULL;
            
        }
        return head;
    }
};



/*

总结：
使用前驱结点进行删除操作，容易忽略删除head结点的问题+结点数为1的问题
使用当前结点被覆盖，需要处理结点数为1的情况
*/