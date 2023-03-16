/*
字符串转换整数 (atoi)
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。

函数 myAtoi(string s) 的算法如下：

读入字符串并丢弃无用的前导空格
检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
返回整数作为最终结果。
注意：

本题中的空白字符只包括空格字符 ' ' 。
除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
 

示例 1：

输入：s = "42"
输出：42
解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
第 1 步："42"（当前没有读入字符，因为没有前导空格）
         ^
第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
         ^
第 3 步："42"（读入 "42"）
           ^
解析得到整数 42 。
由于 "42" 在范围 [-231, 231 - 1] 内，最终结果为 42 。
示例 2：

输入：s = "   -42"
输出：-42
解释：
第 1 步："   -42"（读入前导空格，但忽视掉）
            ^
第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
             ^
第 3 步："   -42"（读入 "42"）
               ^
解析得到整数 -42 。
由于 "-42" 在范围 [-231, 231 - 1] 内，最终结果为 -42 。
示例 3：

输入：s = "4193 with words"
输出：4193
解释：
第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
         ^
第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
         ^
第 3 步："4193 with words"（读入 "4193"；由于下一个字符不是一个数字，所以读入停止）
             ^
解析得到整数 4193 。
由于 "4193" 在范围 [-231, 231 - 1] 内，最终结果为 4193 。
 

提示：

0 <= s.length <= 200
s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成

*/
#include <iostream>
using namespace std;
#include <vector>
#include <string>







class Solution {
public:
    int myAtoi(string s) {
        //先处理字符串，再读取


        //不处理字符串，直接扫描
        int i = 0;
        while (s[i]==' ')//忽略前导空格
            i++;
        if (!(s[i] <= '9' && s[i] >= 0) && s[i] != '+' && s[i] != '-')
            return 0;

        //处理符号
        int sig = 1;
        double sum = 0;//用位的double接收，导致出现使用科学计数法而致int类型无法强制转换而溢出
        if (s[i] == '-') {    //扫描是否有符号
            sig = -1;
            i++;
        }
        else if (s[i] == '+')
            i++;
        if (!(s[i] <= '9' && s[i] >= '0')) return 0;//符号后不是数字

        //计算结果
        for (; i < s.size() && s[i] <= '9' && s[i] >= '0';i++) {    //读取出结果
            sum = 10 * sum + s[i]-48;
            //0-9的ascii码为48-57
            //使用to_string();可转为字符
        }
        if (sum*sig > INT_MAX)
        {
            //int sum2=sum;    //超出int范围的内容直接截断（取左边的数字）,但是在提交时仍出错
            //return sum2;
            /*while (sum > INT_MAX) //超出范围的内容，逐步取余（截断）
                sum /= 10;*/
            return INT_MAX;     //向上溢出则直接返回最大值
        }
        else if (sum*sig < INT_MIN)
            return INT_MIN;     //向下溢出则直接返回最小值
        return sum * sig;
    }
};

/*
class Solution {
public:
    int myAtoi(string s) {
        long long sum = 0;
        int sign = 1;
        bool isSign = false;
        for(int i=0;i<s.size();i++)
        {
            if(s[i] == '-')
            {
                if(isSign)//是否已出现过符号
                    break;
                else{
                    sign = -1;
                    isSign = true;
                    continue;
                }
            }
            //是否已出现过符号,若已经出现数字或正负号则不能出现空格
            if(s[i] == ' ' && !isSign)
                continue;
            if(s[i] == '+')
            {
                if(isSign)//是否已出现过符号
                    break;
                else
                {
                    isSign = true;
                    continue;
                }
            }
            if(isdigit(s[i]))
            {
                isSign = true;//若已经出现数字则后面不能出现空格或符号
                sum = sum * 10 + s[i] - '0';
                sum = sign == 1 ? min(sum, (long long)INT_MAX) : min(sum, -(long long)INT_MIN);
            }
            else
            {
                break;
            }
        }
        return sum * sign;
    }
};
*/





void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "-91283472332";
    string tt = "ccac";
    cout << s.myAtoi(ss);
   
   /* for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }*/
}

int main(void)
{
    test1();

    return 0;
}