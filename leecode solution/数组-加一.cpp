/*
给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。
*/

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        //直接修改最后一位的值，令其加1
        //该方案不可行，因为可能向上进位
        /*
        digits[digits.size()-1]+=1;
        if(digits[digits.size()-1]==10)
        {
            digits[digits.size()-1]=1;
            digits.push_back(0);
        }
        return digits;
        */


        //（提交成功）
        //从后往前处理最后一位的值，处理进位
        auto it = digits.end() - 1;
        while (*it == 9 &&it!=digits.begin())
            it--;//向前定位到最后一个连续的9前面
                //如果处理到开始迭代器，应判断是否全为9

        if (it == digits.begin() && digits[0] == 9) {   //处理全为9的情况
            {
                digits.insert(digits.begin(), 1);
                it=digits.begin()+1;    //注意这里使用it++会报错，考虑为插入函数会新分配内存
            }
        }
        else    //处理不全为9的情况
        {
            (*it)++;
            it++;
        }

        //向后处理值为9的元素
        for (; it != digits.end(); it++)
        {
            *it = 0;
        }
        return digits;




        //（提交失败）
        //设置一位数，依次叠加，然后再拆分进容器
        //提交表示溢出， 问题来自临时变量无法处理很大的值
        /*
        long res=0;
        int index=1;
        for(int i=digits.size()-1;i>=0;i--)
        {
            res=res+digits[i]*index;
            index*=10;
        }
        res++;
        vector<int> v;
        while(res!=0)
        {
            v.insert(v.begin(),res%10);  //注意vector容器并没有push_front函数，但是有insert函数
            res/=10;
        }
        return v;
        */
    }
};

void test1()
{
    Solution s;

    vector<int> nums;
    nums.push_back(9);
    nums.push_back(9);
    nums.push_back(9);
    nums.push_back(9);
    nums.push_back(9);

    s.plusOne(nums);
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
}

int main(void)
{
    test1();

    return 0;
}