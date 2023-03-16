/*
外观数列
给定一个正整数 n ，输出外观数列的第 n 项。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。

你可以将其视作是由递归公式定义的数字字符串序列：

countAndSay(1) = "1"
countAndSay(n) 是对 countAndSay(n-1) 的描述，然后转换成另一个数字字符串。
前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
第一项是数字 1 
描述前一项，这个数是 1 即 “ 一 个 1 ”，记作 "11"
描述前一项，这个数是 11 即 “ 二 个 1 ” ，记作 "21"
描述前一项，这个数是 21 即 “ 一 个 2 + 一 个 1 ” ，记作 "1211"
描述前一项，这个数是 1211 即 “ 一 个 1 + 一 个 2 + 二 个 1 ” ，记作 "111221"
要 描述 一个数字字符串，首先要将字符串分割为 最小 数量的组，每个组都由连续的最多 相同字符 组成。然后对于每个组，先描述字符的数量，然后描述字符，形成一个描述组。要将描述转换为数字字符串，先将每组中的字符数量用数字替换，再将所有描述组连接起来。

 

示例 1：

输入：n = 1
输出："1"
解释：这是一个基本样例。
示例 2：

输入：n = 4
输出："1211"
解释：
countAndSay(1) = "1"
countAndSay(2) = 读 "1" = 一 个 1 = "11"
countAndSay(3) = 读 "11" = 二 个 1 = "21"
countAndSay(4) = 读 "21" = 一 个 2 + 一 个 1 = "12" + "11" = "1211"
 

提示：

1 <= n <= 30


*/
#include <iostream>
using namespace std;
#include <vector>
#include <string>







class Solution {
public:
    string countAndSay(int n) {
        //读取n，建立n-1个外观序列
       
        //读取第n-1个外观序列，分析并建立第n个序列
        return buildbody("1", n, 0);
        
        
    }
    //建立序列
    string buildbody(string s, int n, int num)
    {
        string res;
        if (num < n-1) {    //递归出口
            for (int i = 0; i < s.size(); i++)  //形成本层的外观序列
            {
                int len = 1;
                if (i != s.size() - 1)   //如果处理到最后一个元素，证明最后一个元素为单个不连续元素，应防止越界访问
                    while (s[i] == s[i + 1])    //扫描并记录连续的元素，i最终指向当前连续序列尾部
                    {
                        len++;
                        i++;
                    }
                res.push_back(len+48);  //0对应ascii码48
                res.push_back(s[i]);    //s[i]是char类型
            }

            return buildbody(res, n, ++num);      //下一级递归入口
             //此处必须使用返回的原因：
             //1.对于有返回值的函数，编译器要求该函数必须返回一个值
             //2.不使用返回值则发生写入异常
             //3.递归组成之一，因为只有最后一层递归才会返回一个真正的值，然后不断通过这层接口像上层返回那个真正的值
        }
        else
            return s;   //递归出口
        //分析返回从最底层开始，将s不断返回到上一层递归，最后返回到末尾
    }

    
};





void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "-9128342347";
    string tt = "472";
    
   /* for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }*/


    cout << s.countAndSay(5);
}

int main(void)
{
    test1();

    system("pause");
    return 0;
}