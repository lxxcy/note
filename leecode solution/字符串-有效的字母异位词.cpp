/*
有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。

注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

 

示例 1:

输入: s = "anagram", t = "nagaram"
输出: true
示例 2:

输入: s = "rat", t = "car"
输出: false
 

提示:

1 <= s.length, t.length <= 5 * 104
s 和 t 仅包含小写字母
 
*/


#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <set>








class Solution {
public:
    bool isAnagram(string s, string t) {
        ////利用multiset容器，存入s的每个字符，然后扫描t，将相同字符从set容器中删除
        ////（多次采用查找函数并集建立set容器，导致时间复杂度和空间复杂度较高）
        //multiset<char> queue;
        //for (int i = 0; i < s.size(); i++)
        //{
        //    queue.insert(s[i]);
        //}
        //for (int i = 0; i < t.size(); i++)
        //{
        //    auto it = queue.find(t[i]);
        //    if (it == queue.end())
        //        return false;
        //    else
        //    {
        //        queue.erase(it);
        //    }
        //}
        //if (queue.size() != 0)
        //    return false;
        //else
        //    return true;


        //不利用STL，如何实现？
        //设置一个bool数组，保存一个数组的状态，若匹配成功，则修改标志位（超时，时间复杂度过高）
        if (s.size() != t.size()) return false;
        bool* sig = new bool[s.size()];
        for (int i = 0; i < s.size(); i++)//初始化标志数组
        {
            sig[i] = true;
        }
        for (int i = 0; i < s.size(); i++)
        {
            for (int j = 0; j < s.size(); j++)  //内层循环对比t
            {
                if(sig[j])
                    if (s[i] == t[j])//注意细节，只要对比成功，后面就不应该再修改标志了
                    {
                        sig[j] = false;
                        break;
                    }
                        
            }
        }
        for (int i = 0; i < s.size(); i++) {    //查看标志数组
            if (sig[i] == true)
                return false;
        }
        return true;
        delete[] sig;



        //    //用一个宏定义数组长度26，把for循环使用的变量i，j，k定义在函数前面，用时和内存居然都有优化
        //    //C语言：
        //    #define NUM 26
        //    bool isAnagram(char* s, char* t) {
        //    char arr[NUM] = { 0 };
        //    int i, j, k;

        //    for (i = 0; s[i] != '\0'; ++i) {
        //        arr[s[i] - 'a']++;
        //    }
        //    for (j = 0; t[j] != '\0'; ++j) {
        //        arr[t[j] - 'a']--;
        //    }
        //    for (k = 0; k < NUM; k++) {
        //        if (arr[k] != 0) {
        //            return false;
        //        }
        //    }
        //    return true;
        


        ////c++解法：
        //class Solution {
        //public:
        //    bool isAnagram(string s, string t) {
        //        int size = s.size();
        //        if (s.size() != t.size()) return false;
        //        unordered_map<int, int>m;
        //        for (int i = 0; i < size; i++)
        //        {
        //            ++m[s[i]];
        //            --m[t[i]];
        //        }
        //        for (int i = 'a'; i <= 'z'; i++)
        //        {
        //            if (m.find(i) != m.end() && m[i]) return false;
        //        }
        //        return true;
        //    }



    }


};







void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "aacc";
    string tt = "ccac";
    
    cout <<s.isAnagram(ss, tt);
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