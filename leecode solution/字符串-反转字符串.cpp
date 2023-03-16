/*
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。

不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。

 

示例 1：

输入：s = ["h","e","l","l","o"]
输出：["o","l","l","e","h"]
示例 2：

输入：s = ["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]

*/


#include <iostream>
using namespace std;
#include <vector>








class Solution {
public:
    void reverseString(vector<char>& s) {

        //双指针，交换前后对应的元素
        for (int i = 0, j = s.size() - 1; i != j && i - 1 != j; i++, j--) 
        {
            //结束条件可换为 i<s.size()/2
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }

        /*
        //解法2-使用自带算法reverse
        reverse(s.begin(),s.end());
        */

       /*
       //解法3-递归方式解决（此处为非C++实现）
        public void reverseString(char[] s) {
            if (s == null || s.length == 0)
                return;
            reverseStringHelper(s, 0, s.length - 1);
    }

        public void reverseStringHelper(char[] s, int left, int right) {
            if (left >= right)
                return;
            swap(s, left, right);
            reverseStringHelper(s, ++left, --right);
        }

        private void swap(char[] array, int i, int j) {
            char temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
       */
    }
};












void test1()
{
    Solution s;

    vector<char> v;
    v.push_back('a');
    v.push_back('t');
    v.push_back('i');
    v.push_back('i');
    v.push_back('g');
    v.push_back('d');



    s.reverseString(v);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}

int main(void)
{
    test1();

    return 0;
}