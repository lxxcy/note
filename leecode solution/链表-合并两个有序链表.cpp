/*
合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：

输入：l1 = [], l2 = []
输出：[]
示例 3：

输入：l1 = [], l2 = [0]
输出：[0]
 

提示：

两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按 非递减顺序 排列
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

 //【通过】
 //归并算法，从两个链表中分别摘取较小的一个，插入新的链表中，并仅更新刚刚摘取的链表的指针
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *pos1=list1,*pos2=list2;
        if(!pos1&&!pos2) return NULL;//处理两个链表都为空的情况
        ListNode *head=new ListNode;
        ListNode *set=head;
        
        while(pos1!=NULL&&pos2!=NULL)
        {
            if(pos1->val<pos2->val)
            {
                set->val=pos1->val;
                pos1=pos1->next;
            }
            else
            {
                set->val=pos2->val;
                pos2=pos2->next;
            }
            
                set->next=new ListNode;//尾插法
                // //按理说应该将新结点初始化
                // set->next->val=0;
                // set->next->next=NULL;
                set=set->next;
        }
        
        //最后set一定指向一个未初始化的结点
        //上面循环中不使用if判断是否建立新的结点，是考虑到未进入循环时set仍指向head，以统一后面的操作
        //即此时set指向的位置可直接赋值
        //而除非两个链表都为空，否则set在下面两个if语句中执行后，由于加上了if判断，则最后一定指向末尾的结点，而不是一个未初始化的结点
        //对于两个链表都为空的情况，已经在前面进行判断并处理
        if(pos1)
        {
            while(pos1)
            {
                set->val=pos1->val;
                pos1=pos1->next;
                if(pos1)
                {
                    set->next=new ListNode;//尾插法
                    set=set->next;
                }
            }
        }
        if(pos2)
        {
            while(pos2)
            {
                set->val=pos2->val;
                pos2=pos2->next;
                if(pos2)
                {
                    set->next=new ListNode;//尾插法
                    set=set->next;
                }
            }
        }
        set->next=NULL;
        
        return head;
    }
};



//网络获取答案

//c++递归
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head;
        if (l1 && l2)
            if (l1->val < l2->val)
            {
                head = l1;
                head->next = mergeTwoLists(l1->next, l2);
            }
            else 
            {
                head = l2;
                head->next = mergeTwoLists(l1, l2->next);
            }
        else if (l1 == nullptr)
            head = l2;
        else if (l2 == nullptr)
            head = l1;
        return head;
    }
};


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* List1, ListNode* List2) {
     if(List1==nullptr)return List2;
     if(List2==nullptr)return List1;
     ListNode *p=List1->val<List2->val?List1:List2;
     p->next=mergeTwoLists(p->next,p==List1?List2:List1);
     return p;
    }
};



//c++非递归，不采用建立新表，直接链接原表中的结点
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == NULL)   return list2;   //某链表为空，合并结果为另一个链表
        if(list2 == NULL)   return list1;
        ListNode* list = NULL;  //新链表头指针
        ListNode* tail = NULL;  //新链表尾指针
        while(list1 && list2){  //两个链表都为空，每轮比较并从尾部插入较小结点
            ListNode *temp_node;
            if(list1->val > list2->val){
                temp_node = list2;
                list2 = list2->next;
            }else{
                temp_node = list1;
                list1 = list1->next;
            }
            if(list == NULL){
                list=temp_node;
                tail=temp_node;
            }
            else{
                tail->next = temp_node;
                tail = temp_node;
            }
        }
        //连接剩余结点
        if(list1)   tail->next = list1;
        else   tail->next = list2;
        return list;
    }
};



