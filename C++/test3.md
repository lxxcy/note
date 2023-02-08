                    //自动类型推导失败，不能推导出T的类型
	func<int>();	//使用显示指定类型方式，即可调用该函数模板
}	

int main() {
	test();

	return 0;
}
```

#### 模板使用实例——选择排序不同类型的数组
```c++
#include <iostream>
#include <string>
using namespace std;
#define MAXSIZE 5

char ch[MAXSIZE] = { 'a','c','b','e','f' };
int numarr[]{ 4,3,6,2,9,10,232,53,1 };

//基于选择排序的函数模板
template<typename T>
void select_sort(T *arr,int len) {
	for (int i = 0; i < len-1; i++) {
		int temp = i;	//提醒：每轮循环从当前第一个未排序的元素开始设置temp
		for (int j = i+1; j < len; j++) {
			if (arr[temp] < arr[j])
				temp = j;
		}
		T swap = arr[temp];
		arr[temp] = arr[i];
		arr[i] = swap;
	}
}

template<typename T>
void Print(T arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void test() {
	select_sort(ch,MAXSIZE);
	select_sort(numarr,sizeof(numarr)/sizeof(int));
	Print(ch, MAXSIZE);
	Print(numarr, sizeof(numarr) / sizeof(int));
}	

int main() {
	test();

	return 0;
}
```
