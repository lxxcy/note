#include <iostream>
#include <vector>
using namespace std;
typedef int ElemType;

class Solution {
public:
	//选择最小的元素插到前面
	void InsertSort1(vector<ElemType>& v)
	{
		int len = v.size();
		ElemType min = v[0];
		int minsig = 0;
		//外层循环一层一层往后寻找最小值
		for (int i = 0; i < len; i++)		//i代表待插入的位置（即i前面为有序序列）
		{
			min = v[i];		//不要忘了更新min，每次都将该轮扫描范围的第一个元素视为min
			for (int j = i; j < len; j++)	//从后面寻找最小的元素
			{
				if (v[j] < min)
				{
					min = v[j];
					minsig = j;
				}
			}
			for (int t = minsig; t > i; t--)	//后移minsig到i的元素（不包括minsig）
				v[t] = v[t - 1];
			v[i] = min;	//在i处插入最小元素
		}
		//边界分析：v[0]为第一次扫描的最小值的情况，此时minsig=0，min=v[0]，i=0，最后没有变化
	}

	//选择最大的元素插入到后面
	void InsertSort2(vector<ElemType>& v)
	{
		int len = v.size();
		ElemType max = v[len - 1];
		int maxsig = len - 1;
		for (int i = len - 1; i >= 0; i--)
		{
			max = v[i];
			for (int j = i; j >= 0; j--)
			{
				if (v[j] > max)
				{
					max = v[j];
					maxsig = j;
				}
			}
			for (int j = maxsig; j < i; j++)
				v[j] = v[j + 1];
			v[i] = max;
		}
	}


	void swap(ElemType& a, ElemType& b)
	{
		ElemType temp = a;
		a = b;
		b = temp;
	}
};

int main(void)
{
	
	vector<int> v;
	v.push_back(1);
	v.push_back(56);
	v.push_back(5);
	v.push_back(6);
	v.push_back(8);
	v.push_back(13);
	v.push_back(16);
	v.push_back(94);
	v.push_back(39);
	v.push_back(19);
	v.push_back(74);
	v.push_back(32);
	v.push_back(55);
	v.push_back(23);


	Solution s;
	
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	

	s.InsertSort2(v);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}
