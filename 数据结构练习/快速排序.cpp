#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void QS(vector<int>& v) {
		int low = 0;
		int high = v.size() - 1;
		PivotFind(v, low, high);
	}
	//找到处理先驱
	void PivotFind(vector<int> &A, int low, int high)	//通过引用方式传递，才能修改原数据
	{
		if (low < high) {	//这个判断条件一定不能忘记，否则会出现无限嵌套，导致栈溢出
			//第一次需要传入A，0，A.size()-1
			int pivot = QuickSort(A, low, high);
			PivotFind(A, low, pivot - 1);
			PivotFind(A, pivot + 1, high);
		}
	}
	//算法主体
	int QuickSort(vector<int> &A, int low, int high)
	{
		int pivotdata = A[low];
		while (low < high)
		{
			//由于从low为pivot，故先替换low
			for (; A[high] >= pivotdata && low < high; high--);//从前往后寻找大于pivot的元素
			A[low] = A[high];
			//high位置等待更新下一个元素
			for (; A[low] <= pivotdata && low < high; low++);  //从后往前寻找小于pivot的元素
			A[high] = A[low];
			//low位置等待更新下一个元素
		}
		//最后一定是low==high，此时该位置元素已经被转移到了low+1或low-1的位置
		A[low] = pivotdata;
		return low; //返回pivot位置，以进行嵌套
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
	v.push_back(9);

	Solution s;
	
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	s.QS(v);

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	return 0;
}
