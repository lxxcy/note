/*
反转链表
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。


输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：


输入：head = [1,2]
输出：[2,1]

输入：head = []
输出：[]
 
提示：

链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000
 

进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

*/

#include <iostream>
using namespace std;
#include <vector>
#include <string>


struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};




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
////【成功】
////修改链接顺序，用了三个变量！
//class Solution {
//public:
//    ListNode* reverseList(ListNode* head) {
//        //直接修改链接顺序即可
//        ListNode* temp=NULL, * pre = head;
//        
//        //while (pre!= NULL)  //死循环!
//        //{
//        //    temp = pre;
//        //    pre = pre->next;  //pre已经到了其后继
//        //    pre->next = temp; //pre的后继改为temp？但是temp是pre，死循环
//        //    
//        //}
//        //head->next = NULL;
//
//        //如果不通过机器调试，很难发现和绕出自己的死逻辑
//        ListNode* back = NULL;  //back为逆转后的需要放在后面的结点
//        while (pre != NULL)
//        {
//            temp = pre;
//            pre = pre->next;
//            temp->next = back;
//            back = temp;
//        }
//
//        return back;
//    }
//};

////【成功】
////建立另一个链表
//class Solution {
//public:
//    ListNode* reverseList(ListNode* head) {
//        ListNode* back = NULL, * scan = head,*pos=NULL;
//        while (scan)
//        {
//            back=new ListNode(scan->val,back);
//            scan = scan->next;
//        }
//        return back;
//    }
//};

//【成功】
//递归解决
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL;
        ListNode* pos = head;
        
        return reverseL(pos, pre);
    }

    ListNode* reverseL(ListNode* pos, ListNode* pre)
    {
        if (pos != NULL)
        {
            ListNode* temp = pos->next; //temp用于临时保存pos的后继
            pos->next = pre;            //更新pos的后继为传入的原前驱
            return reverseL(temp, pos); //迭代传入：以temp为下一个扫描结点，当前扫描结点pos将要作为其前驱
            //此处必然使用return，因为只有达到嵌套结束条件才会返回一个值
        }
        else
            return pre;
    }
    
};



//网络解法

////C++ 栈实现
//#include <stack>
////using namespace std;
//class Solution {
//public:
//    ListNode* reverseList(ListNode* head) {
//        stack <ListNode*> stackp;
//        ListNode* temp = head;
//        while (temp != nullptr) {     //将元素压入栈底
//            stackp.push(temp);
//            temp = temp->next;    
//        }
//        if (stackp.empty())           //处理空链表
//            return NULL;
//        ListNode* tp = stackp.top();
//        head = tp;
//        stackp.pop();
//        while (!stackp.empty()) {     //出栈，实现逆序
//            tp->next = stackp.top();
//            tp = tp->next;
//            stackp.pop();
//        }
//        tp->next = NULL;
//        return head;
//    }
//};


//头插法   实现链表逆置
//双链表求解是把原链表的结点一个个摘掉，每次摘掉的链表都让他成为新的链表的头结点（头插法！），然后更新新链表。
//java解法
//public ListNode reverseList(ListNode head) {
//    //新链表
//    ListNode newHead = null;
//    while (head != null) {
//        //先保存访问的节点的下一个节点，保存起来
//        //留着下一步访问的
//        ListNode temp = head.next;
//        //每次访问的原链表节点都会成为新链表的头结点，
//        //其实就是把新链表挂到访问的原链表节点的
//        //后面就行了
//        head.next = newHead;
//        //更新新链表
//        newHead = head;
//        //重新赋值，继续访问
//        head = temp;
//    }
//    //返回新链表
//    return newHead;
//}



////递归 尾递归
////java实现
////递归调用是要从当前节点的下一个结点开始递归。逻辑处理这块是要把当前节点挂到递归之后的链表的末尾，看下代码
// 
//public ListNode reverseList(ListNode head) {
//    //终止条件
//    if (head == null || head.next == null)
//        return head;
//    //保存当前节点的下一个结点
//    ListNode next = head.next;
//    //从当前节点的下一个结点开始递归调用
//    ListNode reverse = reverseList(next);
//    //reverse是反转之后的链表，因为函数reverseList
//    // 表示的是对链表的反转，所以反转完之后next肯定
//    // 是链表reverse的尾结点，然后我们再把当前节点
//    //head挂到next节点的后面就完成了链表的反转。
//    next.next = head;
//    //这里head相当于变成了尾结点，尾结点都是为空的，
//    //否则会构成环
//    head.next = null;
//    return reverse;
//}
// 
////因为递归调用之后head.next节点就会成为reverse节点的尾结点，我们可以直接让head.next.next = head;
////这样代码会更简洁一些，看下代码
//
// public ListNode reverseList(ListNode head) {
//    if (head == null || head.next == null)
//        return head;
//    ListNode reverse = reverseList(head.next);
//    head.next.next = head;
//    head.next = null;
//    return reverse;
//}
// 
////这种递归往下传递的时候基本上没有逻辑处理，当往回反弹的时候才开始处理，也就是从链表的尾端往前开始处理的。
////我们还可以再来改一下，在链表递归的时候从前往后处理，处理完之后直接返回递归的结果，
////这就是所谓的尾递归，这种运行效率要比上一种好很多
//public ListNode reverseList(ListNode head) {
//    return reverseListInt(head, null);
//}
//
//private ListNode reverseListInt(ListNode head, ListNode newHead) {
//    if (head == null)
//        return newHead;
//    ListNode next = head.next;
//    head.next = newHead;
//    return reverseListInt(next, head);
//}



void test2()
{
    ListNode L5 = ListNode(5, NULL);
    ListNode L4 = ListNode(4, &L5);
    ListNode L3 = ListNode(3, &L4);
    ListNode L2 = ListNode(2, &L3);
    ListNode L1=ListNode(1,&L2);
    ListNode* head = &L1;

    Solution s;
    
    ListNode* pos = s.reverseList(head);
    while (pos != NULL)
    {
        cout << pos->val << " ";
        pos = pos->next;
    }
}


void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "47348342347";
    string tt = "47343432";

    vector<string> v2;
    v2.push_back(ss);
    //v2.push_back(tt);
    
   /* for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }*/



}

int main(void)
{
    test2();

    return 0;
}