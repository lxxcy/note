/*
验证回文串
如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。

字母和数字都属于字母数字字符。

给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。

 

示例 1：

输入: s = "A man, a plan, a canal: Panama"
输出：true
解释："amanaplanacanalpanama" 是回文串。
示例 2：

输入：s = "race a car"
输出：false
解释："raceacar" 不是回文串。
示例 3：

输入：s = " "
输出：true
解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
由于空字符串正着反着读都一样，所以是回文串。
 

提示：

1 <= s.length <= 2 * 105
s 仅由可打印的 ASCII 字符组成

*/

#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <set>
#include <ctype.h>







class Solution {
public:
    bool isPalindrome(string s) {
        //先处理原字符串，再进行对比
        for (int i = 0; i < s.size(); i++)
        {
            ////处理方式1：运用字符处理函数，需要包含ctype.h头文件
            //if (isupper(s[i]))
            //    tolower(s[i]);
            
            //处理方式2：利用字符边界
            if ('A' <= s[i] && 'Z' >= s[i])
                s[i] = s[i] + 32; //大小写字符ascii码相差32
             
            ////处理方式3：自动获取大小写距离
            //if (s[i] > 'z')
            //    s[i] += ('A' - 'a');


            if (!(islower(s[i])||('0'<=s[i] && '9'>=s[i])))   //经过大小写处理后，仍不是小写，则说明需要删除（注意之前的处理方式，建议使用isupper函数）
            {
                s.erase(i, 1); //必须指定删除长度，否则将删除pos位置开始的全部字符
                i--;//注意删除i位置的元素后，后面的元素会填补i的位置，而该元素未扫描
            }
                
            
        }
        //另一种方式：采用一个新的string保存处理完的字符，这样节省了删除时移动元素的时间，但空间复杂度提高

        for (int i = 0, j = s.size() - 1; i<j; i++, j--)   //注意结束条件，i==j与i+1==j都是要进行对比的
        {
            if (s[i] != s[j])
                return false;
        }
        return true;


    }
};

//C++双指针
class Solution {
public:
    bool isPalindrome(string s) {
        int size = s.size();
        if (size <= 1) return true;
        for (int i = 0, j = size - 1; i < j; i++, j--)
        {
            while (isalnum(s[i]) == false && i < j)
                ++i;
            while (isalnum(s[j]) == false && i < j)
                --j;
            //上面四行的另一种实现方法
       // while((s[i]<'0'||s[i]>'9')&&(s[i]<'A'||s[i]>'Z')&&(s[i]<'a'||s[i]>'z')&&i<j)
       //     ++i;
       //  while((s[j]<'0'||s[j]>'9')&&(s[j]<'A'||s[j]>'Z')&&(s[j]<'a'||s[j]>'z')&&i<j)
       //     --j;
            if (s[i] != s[j] && (s[i] < 'A' || s[j] < 'A' || abs(s[i] - s[j]) != 32)) return false;
        }
        return true;
    }
};







void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "0P";
    string tt = "ccac";
    
    cout << s.isPalindrome(ss);
   
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