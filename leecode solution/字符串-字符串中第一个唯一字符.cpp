/*
字符串中的第一个唯一字符
给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 -1 。

 

示例 1：

输入: s = "leetcode"
输出: 0
示例 2:

输入: s = "loveleetcode"
输出: 2
示例 3:

输入: s = "aabb"
输出: -1
 

提示:

1 <= s.length <= 105
s 只包含小写字母
*/



#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <map>








class Solution {
public:
    int firstUniqChar(string s) {
        ////暴力破解，一层一层对比，问题是，如果目标元素在最后一个，之前已经对比过的元素怎么办
        //for (int i = 0; i < s.size(); i++) {
        //    int res = -1;   //标志
        //    for (int j = i + 1; j < s.size(); j++)
        //    {
        //        if (s[i] == s[j])
        //        {
        //            res = j;
        //            break;
        //        }
        //    }
        //    if (!res)   //res未动，表示没有重复
        //    {
        //        return i;
        //    }

        //return -1;


        //暴力破解优化，每次都从开头对比（时间复杂度接近O(n^2)，空间复杂度较低）
        for (int i = 0; i < s.size(); i++)
        {
            bool sig = false;   //标志位
            for (int j = 0; j < s.size(); j++)
            {
                if (j == i)     //防止对比自身
                    continue;

                if (s[i] == s[j])
                {
                    sig = true;
                    break;
                }
            }
            if (!sig)
                return i;
        }
        return -1;


        ////设置一个临时的map容器，value存储出现次数，key存储字符（将时间复杂度降低到O(n)量级，提高一倍的空间复杂度）
        //map<char, int> m;
        //for (int i = 0; i < s.size(); i++)
        //{
        //    if (!m.insert(make_pair(s[i], 1)).second)   //插入失败，则查到该元素并递增value值
        //        m.find(s[i])->second++;
        //}
        //char res = ' ';
        //for (auto it = m.begin(); it != m.end(); it++)
        //{
        //    if (it->second == 1)
        //    {
        //        res = it->first;
        //        return s.find(res);
        //    }
        //}
        ////没有改变res、执行到最后则说明没有不重复的字符（问题是，如何返回“第一个”不重复的字符）
        //return -1;


        //使用自定义数据类型对分别存储字符、字符在字符串中的数组下标、字符出现次数（空间复杂度过大）


        //利用map容器，当加入重复的元素并统计下标，则在map中删除该元素,剩下的元素即为结果（只能处理出现偶数次的字符）



        /*
        class Solution {
        public:
            int firstUniqChar(string s) {
                unordered_map<int, int> hash; // 构建哈希表 知识点1
                for( char ch : s){ // ch 是设的类似原始for循环中的 int i = 0 的i s为要循环的数组或字符串名字
                    ++hash[ch]; // 拿到字符串中的字母作为key值，如果有相同的重复过的字母（个数大于1的）那么会将value的值自动进行+1 知识点2 下面有详解
                }
                for(int i = 0; i < s.size(); ++i){
                    if(hash[s[i]] == 1) { // 拿到key值，来看对应的value值是多少。
                        return i;
                    }
                }
                return -1;
            }
        };

        //本题涉及到哈希映射，因为之前并没有接触到这样的哈希表unordered_map<int, int> hash，所以问了老师和同学，以及查询了资料。后来通过这一句：
        //==把string s数组里面每一个不同的元素放在哈希表中，元素值用key表示，元素出现的次数用value表示，比如：2,3,3这个数组， 哈希表的结构是{{3,2},{2,1}};==
        //只要把这个想明白，弄懂++hash[ch]的意思整道题就非常简单。++hash[ch]就是获得s数组中的字母，并作为key（因为这是固定的语法 hash[key] = value），也就是这个数组下标只能作为key。
        //那么遍历整个数组s，如果出现重复的，value值就会从自增。

        //第二个for循环也很明白——就是说按顺序从头开始遍历循环，那么第一个hash[s[i]]取到的value值等于1的，就是第一个不重复的字母的下标。

        //涉及知识：
        //unordered_map
        //头文件：#include<unordered_map>
        //创建表 unordered_map<key,value> Map_name;
        //插入元素 ①Map_name [key]=value;
        //② Map_name.insert(pair<int,int>(key,value));
        //③ unordered_map<int,int>Map_name={{key1,value1},{key2,value2}};
        //查找键值 table_name.find(key)
        //当已经存在键值的情况返回end()

        //创建迭代器 unordered_map<key,value>::iterator iterator_name;

        //用迭代器访问元素的键值 it->first

        //用迭代器访问元素的键值对应的元素值 it->second

        //for ( char ch:s)
        //{}
        //这是C++11中新增的一种循环写法，对数组(或容器类,如vector和array)的每个元素执行相同的操作，此外string类也支持这种对字符的遍历循环操作。
        //对于string数组的理解
        //string字符串在分配内存的时候，其首地址和数组的首地址一样处理，所以可以将string看成一个数组！

        
        
        */

    }
};







void test1()
{
    Solution s;

    vector<int> v;
    v.push_back(4345);

    string ss = "xiaoliujinnianyidingnengshangan!";
    cout <<s.firstUniqChar(ss);
    
   
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