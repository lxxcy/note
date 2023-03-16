/*
给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。
 

示例 1：

输入：nums = [1,2,3,1]
输出：true

示例 2：

输入：nums = [1,2,3,4]
输出：false

示例 3：

输入：nums = [1,1,1,3,3,4,3,2,4,2]
输出：true

*/

//存在重复的元素（未解决）
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    int binarysearch(int num, vector<int>& v, vector<int>& nums)
    {
        int low = 0, high = v.size() - 1;
        while (low <= high)
        {
            int mid = (low+high)/2;
            if (nums[mid] == num)
                return -1;      //查找到则说明有重复元素
            else if (nums[mid] < num)
                low = mid + 1;
            else high = mid - 1;
        }
        return low; //表明应该在low位置插入（原位置即后面的元素将后移）

    }

    bool containsDuplicate(vector<int>& nums) {
        int pos;
        //暴力破解  超时
        /*
        for(int i=0;i<nums.size();i++){
            pos=nums[i];
            for(int j=i+1;j<nums.size();j++){
                if(pos==nums[j])
                    return true;
            }
        }
        return false;
        */


        //如何提高时间复杂度 如何以空间换时间？
        //考虑用set插入，若某次插入失败，则说明有重复
        //问题是set容器进行自动排序的时间复杂度
        //算法通过，但是运行时间和内存占用很大
        /*
        set<int> s;
        for(auto it=nums.begin();it!=nums.end();it++)
        {
            pair<set<int>::iterator,bool>  pr=s.insert(*it);
            if(pr->second==false)
                return false;
}
       return true;
       */



       //通过判断set容器大小，判断此次有没有插入成功（提交成功）
   /*
   set<int> s;
       for(auto it=nums.begin();it!=nums.end();it++)
       {
   pos=s.size();
      s.insert(*it);
           if(pos==s.size())
               return true;
}
       return false;
    */

    //每查询一个元素，通过二分查找一个数组，若查找成功，则说明有重复元素，若查找失败，则在合适的位置插入该元素
        vector<int> v;
        v.push_back(nums[0]);
        for (auto it = nums.begin() + 1; it != nums.end(); it++)
        {
            pos = binarysearch(*(it), v, nums);
            if (pos == -1)
                return true;
            else
            {
                v.insert(v.begin() + pos,*it);
            }
        }
        return false;
    }

};


void test1()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(9);
    nums.push_back(1);

    Solution s;
    cout << s.containsDuplicate(nums) << endl;

}



int main(void)
{
	test1();

	return 0;
}