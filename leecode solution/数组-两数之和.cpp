/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

 

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]

*/


#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <map>



class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        ////暴力破解，将元素与所有值相加，找到对应的目标
        //vector<int> res;
        //for (int i = 0; i < nums.size(); i++) {
        //    for (int j = i + 1; j < nums.size(); j++)
        //    {
        //        if (nums[i] + nums[j] == target)
        //        {
        //            res.push_back(i);
        //            res.push_back(j);
        //            return res;
        //        }
        //    }
        //}

    

        //优化方案：利用sort排序，对于结果大于target的元素则无需相加直接退出该轮循环
        //注意排序后，原数组元素位置发生改变，返回的值也会改变
        //该方法似乎不可行，可考虑建立一张原表和排序后表的索引表
        /*vector<int> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    res.push_back(i);
                    res.push_back(j);
                    return res;
                }
                else if (nums[i] + nums[j] > target)
                    break;
            }
        }
        return res;*/


        //（提交成功，但效果还不如暴力破解）
        //使用map排序并索引数组下标
        vector<int> res;
        multimap<int, int> m;
        for (int i = 0; i < nums.size(); i++)
        {
            m.insert(make_pair(nums[i], i));
        }

        for (auto i = m.begin(); i != m.end(); i++)
        {
            multimap<int, int>::iterator j = i;
            for (j++; j != m.end(); j++) //map不支持随机访问， 不能使用 迭代器+n
            {
                if (i->first + j->first == target)
                {
                    res.push_back(i->second);
                    res.push_back(j->second);
                    return res;
                }
                else if (i->first + j->first > target)  //和大于目标则说明不用再循环
                    break;
            }
        }
        return res;
        
    }
};





void test1()
{
    Solution s;

    vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(4);
    


    vector<int> v=s.twoSum(nums,6);
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