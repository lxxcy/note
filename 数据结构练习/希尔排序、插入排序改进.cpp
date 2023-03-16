#include <iostream>
#include <vector>
using namespace std;
typedef int ElemType;

class Solution {
public:
	//仍待进一步优化
	void ShellSort(vector<ElemType>& v)
	{
		int len = v.size();
		int d, i, j;
		ElemType min;
		int minsig;
		for (d = len / 2; d > 0; d /= 2)	//d==1时，处理最后一次后，d==0,则不应再处理
		{
			for (i = d-1; i < len; i += d)	//内部是一个以d为间距的插入排序
				//由于d最小为1，考虑数组下标可以为0，故i取d-1
			{
				min = v[i];//不要忘了初始化这两个变量
				minsig = i;
				for (int j = i + d; j < len; j += d)
				{
					if (v[j] < min)	//每轮循环寻找最小的值
					{
						min = v[j];
						minsig = j;
					}
				}
				for (int j = minsig; j>i; j -= d)	//后移元素，选择合适的位置插入最小值
					v[j] = v[j - d];
				v[i] = min;
			}
			//if (d == 1) break;	//另一种结束循环的方式
		}
	}

	//标准插入排序，每扫描到一个小于小于前驱的值，则向前寻找插入位置
	void InsertSort3(vector<ElemType>& v)
	{
		int len = v.size();
		ElemType temp;
		for (int i = 1; i < len; i++)
		{
			if (v[i] < v[i - 1])	//默认i前面的元素已经排好序（即使只有一个元素v[0]时也成立）
			{
				temp = v[i];
				int j = i;
				for (; j > 0 && v[j - 1] > temp; j--)	//j-1锁定第一个<=v[i]的值
					v[j] = v[j - 1];				//不断后移j-1后面的元素
				v[j] = temp;
			}
		}
	}

	//优化版本，优化了插入排序算法
	void SheelSort2(vector<ElemType> &v)
	{
		ElemType temp;
		int len = v.size();
		int i, j, d;
		//更新间距
		for (d = len / 2; d > 0; d/=2)
		{
			//插入排序
			for (i = 2*d - 1; i < len; i += d)
			{
				if (v[i-d]>v[i])	//i前面的元素一定有序，最后一个值i-d为其最大值
				{
					temp = v[i];
					j = i;
					//由于j=i，所以应从j-d开始判断，注意j-d要>=0
					for (; j-d >= 0 && temp<v[j-d]; j -= d)	//j-d最后指向第一个<=temp的值，j即为待插入位置
						v[j] = v[j - d];
					v[j] = temp;
				}
			}
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
	
	//s.ShellSort(v);
	s.SheelSort2(v);
	//s.InsertSort3(v);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}
