/*
给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。

假设环境不允许存储 64 位整数（有符号或无符号）。
 

示例 1：

输入：x = 123
输出：321
示例 2：

输入：x = -123
输出：-321
示例 3：

输入：x = 120
输出：21
示例 4：

输入：x = 0
输出：0

*/


#include <iostream>
using namespace std;
#include <vector>








class Solution {
public:
    int reverse(long x) {
        //解法1-使用取模运算符和除法运算符
        int temp;
        long res = 0;
        //问题是怎么判断x溢出，采用long接收x
        if ((temp = (int)x) != x)
            return 0;
        while (x != 0)
        {
            temp = x % 10;
            res = 10 * res + temp;
            x /= 10;
        }
        //输出时采用强制转换int，若转换出的结果与原值不同，则说明发生溢出
        if ((temp = (int)res) != res)
            return 0;
        return res;
    }

    /*
    //解法2-辗转除10，再乘以10回去验证是否溢出，c++中可以采用宏进行判断

        int res = 0;
        while(x) {
            int t = x % 10;
            // int newRes = res * 10 + t; //C++ 这样写 res * 10 这里可能就溢出错误了，所以要修改判断逻辑
            // if ((newRes - t) / 10 != res) return 0;
            // res = newRes;
            if (res > INT_MAX / 10 || res < INT_MIN / 10) return 0;
            res = res * 10 + t;
            x /= 10;
        }

        /*
            INT_MAX是代表最大整数值的宏，INT_MIN表示最小整数值
            这些宏在头文件<limits.h>中定义，因此您必须包括它。
        * /

        return res;
        */
};












void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    cout <<s.reverse(v[0]);

    
   
    /*for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }*/
}

int main(void)
{
    test1();

    return 0;
}