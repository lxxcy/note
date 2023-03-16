#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void BubbleSort1(vector<int>& v)
	{
		int len = v.size();
		for (int i = 0; i < len-1; i++)
		{
			bool swapsig = false;
			for (int j = i + 1; j < len; j++)	//大元素往后冒
			{
				if (v[j - 1] > v[j])
				{
					swap(v[j - 1], v[j]);
					swapsig = true;
				}
			}
			
			if (!swapsig)	return;	//本次循环未发生交换，则说明已经全部有序
		}
	}

	void BubbleSort2(vector<int>& v)
	{
		int len = v.size();
		for (int i = 0; i < len - 1; i++)
		{
			bool swapsig = false;
			for (int j = len - 1; j > i; j--)	//小元素往前冒
			{
				if (v[j - 1] > v[j])
				{
					swap(v[j - 1], v[j]);
					swapsig = true;
				}
			}

			if (!swapsig)	return;
		}
	}

	void swap(int& a, int& b)
	{
		int temp = a;
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
	
	//s.BubbleSort1(v);
	s.BubbleSort2(v);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}
