/*
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。
*/

#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        //（提交通过）
        //采用每次将一段非0连续元素前移
        
        //int n = 0;  //每一段应该移动的距离
        //auto pos = nums.begin();
        //for (auto it = nums.begin(); it!= nums.end(); it++) {   //结束条件必须是结束迭代器，因为是一段一段往前移动，后面段的元素没有动
        //    if (*it == 0)   //寻找第一个0
        //    {
        //        n++;

        //        for (pos = it + 1; pos!=nums.end(); pos++)  //寻找下一个0
        //            if(*pos==0) break;
        //        //问题：
        //        // 1.pos != nums.end()&&*pos!= 0 逻辑运算符两侧的语句执行顺序可能不一致，可能提前解引用end迭代器
        //        // 2.注意边界，防止迭代器溢出

        //        for (it++; it!= pos; it++)  //将该段连续非0元素前移n位
        //        {
        //            *(it-n) = *it;
        //        }
        //        
        //        //最后it指向pos（下一个0），应该-1以应对循环末尾的i++
        //        it--;
        //    }
        //}
        ////n为也最后统计的0个数
        //for (int i = 0; i < n; i++)
        //{
        //    nums[nums.size() - i-1] = 0;
        //}
        //


        //（提交成功）
        //类似冒泡排序，查到0后，循环将0往后挪
        //int n = 0;
        //for (int i = 0; i < nums.size() - n; i++) //注意结束条件为size-n，因为末尾n位是已经处理过去的0
        //{
        //    if (nums[i] == 0)
        //    {
        //        for (int j = i + 1; j < nums.size() - n; j++)
        //        {
        //            swap(nums[j - 1], nums[j]);
        //        }
        //        n++;
        //        //注意交换完后，i指向的位置数据其实是下一个数据，需要再进行判断，而不是直接递增
        //        i--;
        //    }
        //}

        //双指针，只要遇到非0元素，就往前挪到
        int i = 0;
        for (int j = 0; j < nums.size(); j++)
        {
            if (nums[j] != 0)
            {
                swap(nums[i], nums[j]);//应该交换ij的值，因为i要不就为j本身，要不就为0
                i++;
            }
        }

    }
    void swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
};