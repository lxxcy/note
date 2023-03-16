/*
最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。


示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
 

提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成

*/
#include <iostream>
using namespace std;
#include <vector>
#include <string>







//class Solution {
//public:
//      //总是超出buffer,查询得知是数组越界访问了
//    string longestCommonPrefix(vector<string>& strs) {
//        int pos = -1, j;
//        for (int i = 0; i < 200; i++)
//        {
//            j = 0;
//            bool sig = true;
//            if (strs.size() == 1) return strs[0];   //处理只有一个字符串的情况
//            for (; j < strs.size()-1; j++)
//            {
//                
//                if (strs[j][i] != strs[j + 1][i])  
//                    //超出buffer原因:需要对越界进行判断，应在该if内添加以下条件 || !strs[j][i] || !strs[j + 1][i]
//                {
//                    sig = false;
//                    break;
//                }
//            }
//            if (sig) pos = i;   //pos最终指向最后一个相同元素
//            else break; //标志位修改说明此次对比到不同元素
//        }
//        if(strs[0].size()>pos+1)
//            strs[0].erase(pos+1);
//        return strs[0];
//    }
//};

////依旧提示buffer溢出，查询原因是数组越界访问了
//class Solution {
//public:
//    string longestCommonPrefix(vector<string>& strs) {
//        string res;
//        if (strs.size() == 1) return strs[0];
//        for (int i = 0; i < 200; i++)
//        {
//            int j = 0;
//            for (; j < strs.size() - 1; j++)
//            {
//                if (strs[j][i] != strs[j + 1][i])
//                    break;
//            }
//            if (j == strs.size() - 1) res.push_back(strs[j][i]);
//            else break;
//        }
//        return res;
//    }
//};

//修改后，增加了对元素是否存在的判断，结果显示成功通过
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        if (strs.size() == 1) return strs[0];   //处理仅有一个字符串的特殊情况
        for (int i = 0; i < 200; i++)
        {
            int j = 0;
            for (; j < strs.size() - 1; j++)
            {
                if (!strs[j][i] || !strs[j + 1][i]) break; //当前对比的两个数组在该纵行不存在该元素，直接退出
                if (strs[j][i] != strs[j + 1][i])
                    break;
            }
            //如果判断到了倒数第二个元素，最后j++导致循环退出说明该纵列所有元素相等，否则说明有不存在或者不等的元素
            if (j == strs.size() - 1) res.push_back(strs[j][i]);
            else break;
        }
        return res;
    }
};


//网上参阅答案

//class Solution {
//public:
//    string longestCommonPrefix(vector<string>& strs) {
//        string ans = "";
//        for (int i = 0; strs[0][i]; i++) {
//            for (int j = 0; j < strs.size() - 1; j++) {
//                if (strs[j][i] != strs[j + 1][i]) {
//                    return ans;
//                }
//            }
//            ans.push_back(strs[0][i]);
//        }
//        return ans;
//    }
//};


////java版本常规解法
//class Solution {
//    public String longestCommonPrefix(String[] strs) {
//        // 纵向扫描
//        if (strs == null || strs.length == 0) {
//            return "";
//        }
//        // 以第一个字符串为基准，进行纵向扫描
//        int length = strs[0].length();
//        // 纵向深度
//        int count = strs.length;
//        for (int i = 0; i < length; i++) {
//            char c = strs[0].charAt(i);
//            // 以第一个字符串第i个进行向下扫描、
//            for (int j = 1; j < count; j++) {
//                //如果其他字符串长度不够，或者不为c，返回第一个数组的部分截取，如第i个不满足条件，就取[0，i-1]即substring(0,i)
//                if (strs[j].length() <= i || strs[j].charAt(i) != c) {
//                    return strs[0].substring(0, i);
//                }
//            }
//        }
//        // 最大不超过第一个字符串
//        return strs[0];
//    }
//}


////C++，取strs里的第一个string，然后逐步遍历即可
//class Solution {
//public:
//    string longestCommonPrefix(vector<string>& strs) {
//        string ans;
//        for (int i = 0; i < strs[0].size(); i++)
//        {
//            ans.push_back(strs[0][i]);
//            for (int j = 1; j < strs.size(); j++)
//            {
//                if (strs[j][i] != ans.back())
//                {
//                    ans.pop_back();
//                    return ans;
//                }
//            }
//        }
//        return ans;
//    }
//};





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


    cout << s.longestCommonPrefix(v2);
}

int main(void)
{
    test1();

    return 0;
}