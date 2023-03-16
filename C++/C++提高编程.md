# C++提高编程
## 目录
[TOC]

## [模板](#目录)
模板即建立通用的模具(将类型参数化)，大大提高复用性
模板的特点：
* 模板不可以直接使用，它只是一个框架
* 模板的通用并不是万能的

C++提供另一种编程思想——**泛型编程**，主要利用的技术就是**模板**
C++提供两种模板机制：
* **函数模板**
* **类模板** 
### 函数模板
函数模板作用：建立一个通用函数，其返回值类型和形参类型可以不具体制定，用一个**虚拟的类型**来代表

函数模板语法：
`template<typename T>`
`函数声明 或 定义`
解释：
template----声明创建模板
typename----表明其后面的符号是一种数据类型，可以用class代替
T----通用的数据类型，名称可替换，通常为大写字母

函数模板的两种使用方式：
1. 自动类型推导 `函数名(参数1,参数2...)`
2. 显示指定类型 `函数名<数据类型>(参数1,参数2...)`
```c++
#include <iostream>
using namespace std;

void swap1(int& a, int& b) {
	int temp=a;
	a = b;
	b = temp;
}

//函数模板
template<typename T>	//声明一个模板，告诉编译器后面的代码中紧跟着的T不要报错，T为一个通用数据类型
void swap2(T &a,T &b) {
	T temp = a;
	a = b;
	b = temp;
}

void test01() {
	int a = 1;
	int b = 2;
	swap1(a, b);	//普通的交换函数，如果要实现另一种类型的交换，则必须利用重载或者新写一个函数实现
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;

	//基于函数模板的交换函数
	//函数模板有两种使用方法：
	//1.自动类型推导
	swap2(a, b);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	//2.显示指定类型
	swap2<int>(a, b);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
}

int main() {
	test01();

	return 0;
}
```

#### 函数模板使用的注意事项
注意事项：
* 自动类型推导，必须推导出**一致的数据类型T**，才可以使用
* 模板**必须确定出T的类型**，才可以使用
  (可使用显示指定类型使用该类模板)

```c++
#include <iostream>
#include <string>
using namespace std;

template<typename T>
void swap1(T& a, T& b) {
	T temp=a;
	a = b;
	b = temp;
}

template<class T>
void func() {
	cout << "func调用" << endl;
}

void test() {
	int a = 10;
	int b = 20;
	char c = 'c';
	swap1(a, b);
	swap1(a, c);	//报错！自动类型推导，要求推导出一致的数据类型

	func();	        //报错！func()并未用到模板中的参数T，
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

#### 函数模板和普通函数的区别
普通函数与函数模板的区别：
* 普通函数调用时，可以发生自动类型转换(隐式类型转换)
* 函数模板调用时，
  * 如果使用自动类型推导方式，**不会**发生隐式类型转换（会报错了，因为编译器无法推导出一致的数据类型T）
  * 如果使用显示指定类型方式，可以发生隐式类型转换

Tips：建议使用显示指定类型的方式，调用函数模板，因为一般自己可以确定通用类型T

#### 普通函数与函数模板的调用规则
调用规则：
1. 如果函数模板和普通函数都可以实现，优先调用**普通函数**
2. 可以通过**空模板参数列表**来强制调用函数模板
3. 函数模板也可以发生重载
4. 如果函数模板可以产生更好的匹配，优先调用**函数模板**

注意：即使仅有函数声明，若模板定义和函数声明一致（即表明用模板或函数都能实现），编译器仍然会调用函数，只是最后会报错

Tips：既然提供了函数模板，就不要提供普通函数，否则很容易出现二义性
```c++
#include <iostream>
#include <string>
using namespace std;

void Print(int a, int b) {
	cout << "函数调用" << endl;
}

template<class T>
void Print(T a, T b) {
	cout << "函数模板调用" << endl;
}

template<typename T>
void Print(T a, T b, T c) {
	cout << "函数模板重载的调用" << endl;
}

void test() {
	int a = 10;
	int b = 20;

	Print(a, b);	//由于模板和函数实现是一致的，优先调用函数
	//注意，即使仅保留函数声明，也会优先调用函数，只是会报错，因为没有函数声明
	Print<>(a, b);	//想要强制调用函数模板，必须使用 空模板参数列表

	Print(a, b,1);	//函数模板可以发生重载

	char c = 'c';
	char d = 'd';
	Print(c, d);	//此时调用模板，因为c,d为char型，能更好的与模板匹配
					//而调用函数需要进行自动类型转换
}	

int main() {
	test();

	return 0;
}
```

#### 模板的局限性
模板的通用性并不是万能的
（如不能在函数模板中直接实现自定义数据类型的比较）

C++为了解决这种问题，提供**模板的重载**，可以为这些**特定的类型**提供**具体化的模板**

注意：
1. 利用具体化的模板，可以解决自定义数据类型的通用化
   （也可以使用运算符重载）
2. 学习模板不是为了写模板，而是能在STL中能运用系统提供的模板
```c++
#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	Person(int age,string name) {
		this->m_Age = age;
		this->m_Name = name;
	}
	int m_Age;
	string m_Name;
};

template<typename T>
bool IsEqual(T& a, T& b) {
	if (a == b)
		return true;
	else return false;
}

//可以采用运算符重载实现比较自定义数据类型
//也可以使用具体化的模板来拓展自定义数据类型的通用性
template<> bool IsEqual(Person& a, Person &b) {
	if (a.m_Age == b.m_Age && a.m_Name == b.m_Name)
		return true;
	else return false;
}

void test() {
	Person a(18, "Tom");
	Person b(18, "Tom");
	if (IsEqual(a, b))		//若不写具体化的模板，仅调用函数模板，
							//虽然编译器检查不出语法错误，但该代码实际上不能运行
		cout << "a==b" << endl;
	else
		cout << "a!=b" << endl;
}	

int main() {
	test();

	return 0;
}
```

### 类模板
作用：建立一个通用的类，类中成员的**数据类型**可以不具体制定，用一个**虚拟的类型**来代表

语法：
`template<typename T>`
`类`
解释：
template---声明创建一个模板
typename---表明其后面是一个数据类型，可以用class代替
T---通用数据类型，名称可替换，通常为大写字母

```c++
#include <iostream>
#include <string>
using namespace std;

//类模板
template<typename NameType,typename AgeType>	//使用两个通用化参数
class Person {
public:
	Person(NameType name,AgeType age) {
		this->m_Age = age;
		this->m_Name = name;
	}

	void Print() {
		cout << this->m_Age << "岁的" << this->m_Name << endl;
	}

	AgeType m_Age;
	NameType m_Name;
};

void test() {
	Person<string,int> p("孙悟空",999);
	p.Print();
}	

int main() {
	test();

	return 0;
}
```

#### 类模板和函数模板的区别
类模板和函数模板主要有两种区别：
1. 类模板没有自动类型推导的使用方式
2. 类模板在模板参数列表中，可以有默认参数

```c++
#include <iostream>
#include <string>
using namespace std;

//类模板
template<typename NameType,typename AgeType>
class Person {
public:
	Person(NameType name, AgeType age) {
		this->m_Age = age;
		this->m_Name = name;
	}

	void ShowInfo() {
		cout << this->m_Name << "有" << this->m_Name << "岁" << endl;
	}

	NameType m_Name;
	AgeType m_Age;
};

template<typename NameType, typename AgeType=int>	//采用默认参数的模板
class Person2 {
public:
	Person2(NameType name, AgeType age) {
		this->m_Age = age;
		this->m_Name = name;
	}

	void ShowInfo() {
		cout << this->m_Name << "有" << this->m_Name << "岁" << endl;
	}

	NameType m_Name;
	AgeType m_Age;
};

void test() {
	Person p1("孙悟空", 1000);	//报错，因为必须指定类型，类模板不能自动类型推导
	Person<string, int> p1("孙悟空", 1000);	//正确的做法

	Person2<string> p2("猪八戒", 999);		//使用默认参数的类模板使用
}	

int main() {
	test();

	return 0;
}
```

#### 类模板中成员函数的创建时机
类模板中成员函数和普通普通类中成员函数的创建时机是有区别的：
* 普通类的成员函数一开始就可以创建
* 类模板中的成员函数，在**调用时**才创建

```c++
#include <iostream>
#include <string>
using namespace std;

class Person1 {
public:
	void show_Person1() {
		cout << "Person1的调用" << endl;
	}
};

class Person2{
public:
	void show_Person2() {
		cout << "Person2的调用" << endl;
	}
};

//类模板
template<typename T>
class testclass{
public:
	T obj;

	void func1() {
		obj.show_Person1();
	}

	void func2() {
		obj.show_Person2();
	}
};

void test() {
	testclass<Person1>	p1;
	p1.func1();
	p1.func2();		//编译器并不会报错，但是运行时会出错，因为p1实际上没有show_Person2()成员函数
					//因为类模板的成员函数在  调用时  才创建
					//故运行前，编译器检查不出类模板中的错误
}	

int main() {
	test();

	return 0;
}
```

#### 类模板对象做函数参数
类模板对象作为函数参数，一共有三种传入方式：
1. **指定传入的类型**---直接显示对象的数据类型（**使用最广泛**）
2. **参数模板化**---将对象中的参数变为模板进行传递
3. **整个类模板化**---将这个对象 模板化 进项传递

```c++
#include <iostream>
#include <string>
using namespace std;

template<typename NameType,typename AgeType>
class Person {
public:
	Person(NameType name, AgeType age) {
		this->name = name;
		this->age = age;
	}

	NameType name;
	AgeType age;
};

//指定传入的类型（最常用）
void test01(Person<string ,int> &p) {
	cout << "第一种传入方式" << p.name << p.age << "岁" << endl;
}	

//参数模板化（实际上就是结合函数模板和类模板，让编译器推导传入的类模板的参数）
template<typename T1,typename T2>
void test02(Person<T1, T2>& p) {
	cout << "第二种传入方式" << p.name << p.age << "岁" << endl;
	//查看通用参数的类型
	cout << typeid(T1).name() << endl;	//注意加括号，因为这是一个成员函数
	cout << typeid(T2).name() << endl;
}

//整个类模板化（实际上就是结合函数模板和类模板，让编译器推导出类模板，并推导出其参数类型）
template<class T>
void test03(T& p) {
	cout <<"第三种传入方式" << p.name << p.age << "岁" << endl;
	//查看通用参数的类型
	cout << typeid(T).name() << endl;
}

void test() {
	Person<string, int> p1("孙悟空",1000);
	test01(p1);
	test02(p1);
	test03(p1);
}

int main() {
	test();

	return 0;
}
```
#### 类模板与继承
当类模板遇到继承时，需要注意以下几点：
* 当子类继承的父类是一个类模板时，子类在声明时，要指出父类中T的类型
* 如果不指定，编译器无法给子类分配内存
* 如果想灵活指定出父类中T的类型，子类也需要变成模板
```c++
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Base {
public:
	T data;
};

//class Son1 :public Base		//将会出错，因为编译器不知道Base中T的类型，无法为Son1分配内存
class Son1:public Base<int>		//继承模板，在子类声明时，需要指出父类模板中T的类型
{
public:

};

//若要灵活指定父类中T的类型，子类也需要变成模板（创建一个通用参数来指定父类的参数类型）
template<typename T1,typename T2>
class Son2 :public Base<T2>
{
public:
	void showdatatype() {
		cout <<"T1的类型：" << typeid(T1).name() << endl;
		cout << "T2的类型：" << typeid(T2).name() << endl;
	}
	T1 sondata;
};

void test() {
	Son1 son1;
	Son2<int,char> son2;
	son2.showdatatype();
}

int main() {
	test();

	return 0;
}
```

#### 类模板成员函数的类外实现
类模板中成员函数类外实现时，需要在**类名后、::前**加上**模板参数列表**
为了让编译器认识模板参数，实现前仍需要使用template关键字
```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T>
class Base {
public:
	T data;
};

//class Son1 :public Base		//将会出错，因为编译器不知道Base中T的类型，无法为Son1分配内存
class Son1:public Base<int>		//继承模板，在子类声明时，需要指出父类模板中T的类型
{
public:

};

//若要灵活指定父类中T的类型，子类也需要变成模板（创建一个通用参数来指定父类的参数类型）
template<typename T1,typename T2>
class Son2 :public Base<T2>
{
public:
	void showdatatype() {
		cout <<"T1的类型：" << typeid(T1).name() << endl;
		cout << "T2的类型：" << typeid(T2).name() << endl;
	}
	T1 sondata;
};

void test() {
	Son1 son1;
	Son2<int,char> son2;
	son2.showdatatype();
}

int main() {
	test();

	return 0;
}
```

#### 类模板分文件编写
问题：类模板中，成员函数的创建时机是在调用阶段，故编译阶段会忽视其定义和声明，导致分文件编写时链接不到

解决：
* 解决方案1：直接包含.cpp源文件
* 解决方式2：将声明和实现写到同一个文件中，并更改其后缀名为.hpp
  （.hpp是约定速成的名称，并不是强制）

#### 类模板与友元
类模板配合友元函数的类内实现和类外实现
* 全局函数类内实现---直接在类内声明友元即可
* 全局函数类外实现---需要提前让编译器知道全局函数的存在

注意：建议全局函数做**类内实现**，用法简单，而且编译器可直接识别

```c++
#include <iostream>
#include <string>
using namespace std;

//步骤3.由于类外全局函数中使用了类模板Person，故其前面要先有一个声明才能使用
template<class T1,class T2>
class Person;

//步骤2.全局函数（友元），类外实现，需要写在类模板前面，让编译器知道该函数的存在
template<typename T1,typename T2>
void ShowPerson2(Person<T1, T2> p) {
	cout << p.m_Name << "有" << p.m_Age << "岁" << endl;
}

template<class T1,class T2>
class Person {
	friend void ShowPerson2(Person<T1, T2> p);		//步骤1.全局函数（友元），类外实现，这里表明是友元
													//但前提是让编译器知道该函数已经存在，否则会报错

	friend void ShowPerson(Person<T1, T2> p) {		//全局函数（友元），类内实现
		cout << p.m_Name << "有" << p.m_Age<<"岁" << endl;
	}
public:
	Person(T1 name, T2 age) {
		this->m_Name = name;
		this->m_Age = age;
	}
private:
	T1 m_Name;
	T2 m_Age;
};

void test() {
	Person<string, int> p("Tom", 18);
	ShowPerson(p);
}

int main() {
	test();

	return 0;
}
```

### 模板案列——自定义数组
描述：实现一个通用的数组类，要求：
* 可以对内置数据类型或自定义数据类型的数据进行存储
* 将数组中的数据存储到堆区
* 构造函数中可以传入数组的容量
* 提供对应的拷贝构造函数，以及operator=防止浅拷贝带来的问题
* 提供尾插法和尾删法，对数组中的数据进行增加和删除
* 可以通过下标方式访问数组中的元素
* 可以获取数组中当前元素个数和数组的容量

Tips:
1. 读懂需求，思考怎么实现，尽量避免理解错误
2. 对仅做读取的数据，特别是引用类型，加const防止对原参数的修改
3. 构造函数要实现的功能：
   * 初始化属性、
   * 申请空间、
   * 如果涉及文件可能需要读取文件内容要内存（以便实现操作）
4. 析构函数要实现的功能
   * 清理所使用的堆区数据
   * 将属性初始化为原状态
5. 时刻注意浅拷贝深拷贝问题
6. 若考虑链式编程需求，返回值应为引用类型
7. 进行=运算符重载，可考虑将左操作数初始化后（如释放其申请的堆区空间），再对其进行赋值

myArry.hpp中的代码
```c++
#pragma once
#include <iostream>
using namespace std;

template<class T>
class myArray {
public:
	//构造函数，申请空间，初始化属性
	myArray(int maxsize) {
		this->m_capacity = maxsize;
		this->Arr = new T[m_capacity];
		this->m_lenth = 0;	//注意：初始化长度为0
	}

	//重写拷贝构造函数，防止浅拷贝
	myArray(const myArray& arr) {		//特别注意：此处尽量加const，防止通过引用对原参数修改
		
		this->m_capacity = arr.m_capacity;
		this->m_lenth = arr.m_length;
		//this->Arr = arr.Arr;	//浅拷贝，应该避免该类操作

		//深拷贝
		this->Arr = new T[arr.m_capacity];
		for (int i = 0; i < this->m_capacity; i++) {
			this->Arr[i] = arr.Arr[i];
		}
	}

	//=运算符重载，以实现该类的赋值操作
	myArray& operator=(const myArray& arr) {	//特别注意：此处参数尽量加const
		//要先判断当前类是否有数据，否则需要重新初始化
		if (this->Arr != NULL)
		{
			delete[] this->Arr;
			this->Arr = NULL;
			this->m_lenth = 0;
			this->m_capacity = 0;
		}
		this->m_capacity = arr.m_capacity;
		this->m_lenth = arr.m_lenth;
		//深拷贝
		this->Arr = new T[arr.m_capacity];
		for (int i = 0; i < this->m_capacity; i++) {
			this->Arr[i] = arr.Arr[i];
		}
		return *this;
	}

	//尾插法实现增加
	void Add(const T &data) {		//使用引用节省空间，加const防止修改原参数
		if (m_lenth < this->m_capacity) {
			this->Arr[m_lenth] = data;
			this->m_lenth++;
		}
		else
			cout << "添加失败，表已满" << endl;
	}

	//尾删法实现删除
	void Delete() {
		if (this->m_lenth > 0) {
			m_lenth--;		//逻辑删除
		}
		else
			cout << "删除失败，表已空" << endl;
	}

	//通过下标获取数组中的元素（自己写的，有一定问题）
	T& GetData(int site) {
		if (site <= this->m_lenth) {
			return Arr[site - 1];
		}
		else
			cout << "请输入合法下标" << endl;
	}

	//通过下标获取数组中的元素，应该重载[]运算符
	//比如用myArray创建了arr对象，想要直接使用arr[n]访问下标为n的数据，就应该重载[]
	T& operator[](int n)		//为保证该返回值能作为左值，以进行链式编程，应返回引用类型，如想实现操作arr[0]=100
	{
		return this->Arr[n];
	}

	//显示最大长度和当前长度
	void Showlenghandmaxsize() {
		cout << "maxzize=" << this->m_capacity << endl;
		cout << "length=" << this->m_lenth << endl;
	}

	//析构函数，清理申请的内存空间
	~myArray() {
		if (this->Arr != NULL) {
			delete[] Arr;
			this->Arr = NULL;
			this->m_capacity = 0;
			this->m_lenth = 0;
		}
	}

private:
	int m_lenth;	//数组长度
	int m_capacity;	//数组容量（由构造函数指定）
	
	T *Arr;			//所维护的数组
};
```

主函数中代码（用于测试功能）
```c++
#include <iostream>
using namespace std;
#include "arr.hpp"

int main(void) {
	myArray<int> arr1(1);
	myArray<int> arr2(2);

	arr1.Add(1);
	arr2.Add(3);
	arr2.Add(6);
	arr1 = arr2;
	arr1.Showlenghandmaxsize();
	cout << arr1.GetData(2) << endl;
	cout << arr1.GetData(1) << endl;;

	return 0;
}
```

## [STL](#目录)
### STL基础
#### STL诞生
长久以来，软件界一直希望建立一种可重复利用的东西
C++的面向对象和泛型编程思想，目的就是**复用性的提升**
大多数情况下，数据结构和算法都未能有一套统一的标准，导致被迫从事大量重复的工作
为建立数据结构和算法的一套标准，诞生了STL

#### STL基本概念
STL(Standard Template Library),标准模板库
STL广义上分为：**容器**，**算法**，**迭代器**
* **容器**和**算法**之间通过**迭代器**进行无缝衔接

STL几乎所有代码都采用了模板类或模板函数

#### STL六大组件
STL六大组件：容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器

1. 容器：各类数据结构
2. 算法：各种算法
3. 迭代器：容器和算法间的粘合剂
4. 仿函数：行为类似函数，可作为算法的某种策略
5. 适配器：修饰容器或仿函数或迭代器的接口
6. 空间配置器：负责空间的配置和管理

#### STL容器、算法、迭代器
容器：即运用最广泛的一些数据结构实现出来
常用的数据结构：数组、链表、栈、队列、集合、映射表......
容器分为**关联式容器**和**序列式容器**
* 序列式容器：如数组，强调值的顺序，每个元素均有固定的位置
* 关联式容器：如二叉树，各元素间没有严格意义上的物理顺序关系

算法(Algorithms)：有限的步骤，解决逻辑或数学上的问题
算法分为**质变算法**和**非质变算法**
* 非质变算法：运算过程中**不会更改**区间内元素的内容
* 质变算法：运算过程中**会更改**区间内元素的内容

迭代器：容器和算法之间的粘合剂，提供一种放啊，使之能够依序寻访某个容器所含的各个元素，而又无需暴露该容器的内部表示方式
> 算法要通过迭代器，才能访问容器中的元素

每个容器都有自己专属的迭代器
迭代器使用非常类似于指针，初级阶段可先理解迭代器为指针
|种类|功能|支持运算|
|---|---|---|
|输入迭代器|对数据的只读访问||
|输出迭代器|对数据的只写访问||
|前向迭代器|读写操作，并能向前推进迭代器||
|双向迭代器|读写操作就|并能向前和向后操作||
|随机访问迭代器|读写操作，可以以跳跃方式访问任意数据，功能最强的迭代器||

常用的容器中，迭代器种类为**双向迭代器**和**随机访问迭代器**

### vector简介
vector容器实现基本数据类型存储
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

void Print(int val) {
	cout << val << endl;
}

void test() {
	//创建了一个vector容器数组
	vector<int> v;

	//向容器中插入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	//通过迭代器访问容器中的数据
	vector<int>::iterator itBegin = v.begin();	//起始迭代器，指向容器中第一个元素
	vector<int>::iterator itEnd = v.end();		//结束迭代器，指向容器中最后一个元素的下一个位置

	//第一种遍历方式
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}

	//第二种遍历方式
	for (vector<int>::iterator i = v.begin(); i != v.end(); i++)
	{
		cout << *i << endl;
	}

	//第三种遍历方式
	for_each(v.begin(), v.end(), Print);	//for_each()包含于头文件algorithm中，实际上该函数使用回调技术，
											//最后一个参数只需要写函数名，不用加括号
}

int main() {
	test();

	return 0;
}
```
vector容器实现自定义数据类型存储
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <string>

class Person {
public:
	Person(string name,int age) {
		this->m_name = name;
		this->m_age = age;
	}
	int m_age;
	string m_name;
};

void test() {
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	
	vector<Person> v1;
	v1.push_back(p1);
	v1.push_back(p2);
	v1.push_back(p3);
	v1.push_back(p4);
	for (vector<Person>::iterator i = v1.begin(); i != v1.end(); i++)
	{
		//.的优先级高于*，所以要加括号，表示先解引用i，然后得到数据
		//Tips：要看*i是什么类型，只需要看vector后面尖括号内的类型即可
		cout << "姓名：" << (*i).m_name << "\t年龄：" << (*i).m_age << endl;
		//另一种获取数据的方式
		i->m_age; i->m_name;
	}

	vector<Person*> v2;		//将指针存储到容器
	v2.push_back(&p1);
	v2.push_back(&p2);
	v2.push_back(&p3);
	v2.push_back(&p4);
	for (vector<Person*>::iterator i = v2.begin(); i != v2.end(); i++)
	{
		cout << "姓名：" << (*i)->m_name << "\t年龄：" << (*i)->m_age << endl;
		//注意此处*i实际上是一个指针，故需要用->访问其指向的对象
	}
}

int main() {
	test();

	return 0;
}
```
嵌套容器
```c++
#include <iostream>
using namespace std;
#include <vector>

void test() {
	//嵌套vector
	vector<vector<int>> v;
	
	//内层vector
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;

	//给内层vector赋初值
	for (int i=0;i<4;i++)	
	{
		v1.push_back(i + 1);
		v2.push_back(i + 2);
		v3.push_back(i + 3);
		v4.push_back(i + 4);
	}

	//将内层vector放到外层vector中
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);

	for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
	{
		//注意：*it为vector<int>类型
		for (vector<int>::iterator vit=(*it).begin();vit!=(*it).end();vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
}

int main() {
	test();

	return 0;
}
```

### string
string是C++风格字符串，本质上是一个**类**
string和char \*的区别：
- char \*是一个指针
- string是一个类，类内封装了char \*，管理这个字符串，是一个char \*容器

特点：
- string类内封装了很多成员方法
- string类管理char \*所分配的内存，不用担心复制越界、取值越界等问题，由类内部进行负责

#### string构造函数
- `string();`                    //创建一个空字符串
  `string(const char *s);`       //使用字符串s初始化
- `string(const string &str);`   //使用一个sring对象初始化另一个string对象
- `string(int n,char c);`        //使用n个字符c初始化

#### string赋值操作
赋值函数原型：
- `string &operator=(const char *s);`       //**char\*类型字符串**赋值给当前字符串
- `string &operator=(const string &s);`     //把字符串s赋值给当前字符串
- `string &operator=(char c);`              //字符c赋值给当前字符串
- `string &assign(const string &s);`        //把字符串s赋值给当前字符串
- `string &assign(const char *s,int n);`    //把字符串s的**前n个字符**赋值给当前字符串
- `string &assign(int n,char c);`           //用n个字符c赋值给当前字符串
#### string字符串拼接
实现在字符串末尾拼接字符串
- `string &operator+=(const char *str);`            //重载+=运算符
- `string &operator+=(const char c);`
- `string &operator+=(const string &str);`
- `string &append(const char *s);`                  //将字符串s拼接到当前字符串末尾
- `string &append(const char *s,int n);`            //将字符串s的**前n个字符**拼接到当前字符串末尾
- `string &append(const string &s);`                //将string类型字符串s拼接到当前字符串末尾
- `string &append(const string &s,int pos,int n);`  //将字符串s中，从**数组下标为pos的位置**开始的**n个字符**，拼接到当前字符串末尾

#### string查找和替换
- `int find(const string &str,int pos=0) const;`        //查找子串str**第一次**出现的位置（子串第一个字符的下标），从pos开始查找（pos默认为0）
- `int find(const char *s,int pos=0) const;`
- `int find(const char *s,int pos,int n) const;`        //从pos位置，查找s的**前n个字符** **第一次**出现的位置
- `int find(const char c,int pos=0) const;`
- `int rfind(const string &str,int pos=npos) const;`    //查找字符串str**最后一次**出现的位置（仍返回的是第一个字符的下标），从pos开始查找
- `int rfind(const char *s,int pos=npos) const`
- `int rfind(const char *s,int pos,int n) const`        //从pos位置，查找s的**前n个字符** **最后一次**出现的位置
- `int rfind(const char c,int pos=0) const;`
- `string &replace(int pos,int n,const string &str);`   //替换从pos开始的n个字符为字符串str（注意，str中的字符可能不是n个！）
- `string &replace(int pos,int n,const char *s);`       //替换从pos开始的n个字符为字符串s

注意：
1. find是**从左往右**查，rfind为**从右往左**
2. find找到字符串后，返回查找的**第一个字符**的位置，找不到则返回 **-1**
3. repalce在替换时，要指定**从哪个位置起**、**多少个字符**、**替换成什么字符串**

#### string字符串比较
比较方式：
- 字符串之间的比较，实际上是将两个字符串，**相同下标**的字符**按照ASCII码值**进行对比
  - ==则返回0
  - \>则返回1
  - <则返回-1

函数原型：
- `int compare(const string &s) const;`
- `int compare(const char *s) const;`

注意：
- 字符串比较通常是用于比较两个字符串是否相等，判断谁大谁小意义并不是很大

#### string字符串存取
string中单个字符存取方式有两种：
- `char &operator[](int n);`    //通过[]方式取字符（即看做一个数组）
- `char &at(int n);`            //通过at成员函数取字符

注意：
1. 不仅仅可以通过这两种方式读取字符，也能修改字符串的该字符
2. 补：可以使用string内部成员函数`int &size();`获取当前字符串大小

#### string插入和删除
即对字符串进行插入和删除字符操作
函数原型：
- `string &insert(int pos,const char *s);`      //在pos位置插入字符串s
- `string &insert(int pos,const string &str);`  //在pos位置插入字符串s
- `string &insert(int pos,int n,char c);`       //在pos位置，插入n个字符c
- `string &erase(int pos,int n=npos);`          //删除从pos位置开始的n个字符

注意：
- 插入和删除，起始下标都是从0开始
- 在pos位置插入，即插入前将pos位置及后面的字符往后挪，然后在pos位置插入新的字符串
  （可以理解为从pos位置前面插入字符串）

#### string子串
从string字符串中，获取想要的子串，**该函数非常实用**

函数原型：
`string substr(int pos=0,int n=npos) const;`    //返回从pos开始的n个字符所组成的字符串

### vector
vector数据结构和**数组**非常类似，也称为**单端数组**
但是vector和普通数组不同：数组是**静态空间**，而vector可以**动态扩展**
* 动态扩展：并非在原空间之后续接新空间，而是寻找更大的空间，然后拷贝原数据至新空间，释放原空间
    ![](./vector.jpg)
vector容器的迭代器，是支持**随机访问**的迭代器

#### vector构造函数
功能：创建vector容器
vector构造函数并没有可比性，灵活使用即可
函数原型：
- `vector<T> v;`                //采用类模板实现类实现，默认构造函数
- `vector(v.begin(),v.end());`  //将v[v.begin(),v.end())区间中的元素拷贝给自身，注意，前面为闭区间，后面为开区间，因为v.end()指向的是最后一个元素的下一个位置
- `vector(n,elem);`             //将n个elem拷贝给自身
- `vector(const vector &vec);`  //拷贝构造函数
#### vector赋值操作
功能：给vector容器赋值
函数原型：
- `vector &operator=(const vector &vec);`   //重载=运算符
- `assign(beg,end);`                        //将[beg，end)区间中的数据拷贝并赋值到自身，注意后面仍为开区间
- `assign(n,elem);`                         //  将n个elem拷贝赋值到自身

#### vector容量和大小
功能：对vector容器的容量和大小操作
函数原型：
- `empty();`            //判断容器是否为空（bool类型）
- `capacity();`         //容器的容量
- `size();`             //返回容器中元素的个数
- `resize(int num);`    //重新指定容器的长度为num
                        //若容器变长，则以默认值填充新位置（默认为0）
                        //若容器变短，末尾超出容器长度的元素将被删除
- `resize(int num,elem);`//重新指定容器的长度为num
                        //若容器变长，则以elem填充新位置
                        //若容器变短，超出末尾长度的元素将被删除

#### vector插入和删除
功能：对vector容器进行插入、删除操作
函数原型：
- `push_basc(ele);`             //尾部插入元素ele
- `pop_back();`                 //删除最后一个元素
- `insert(const_iterator pos,ele);` //迭代器指向位置pos插入元素ele
- `insert(const_iterator pos,int count,ele);`   //迭代器指向位置pos插入count个元素ele
- `erase(const_iterator pos);`  //删除迭代器指向的元素
- `erase(const_iterator start,const_iterator end);`     //删除跌底气从start到end之间的元素
- `clear()`                 //删除容器搜中所有元素

注意：inset和erase中确定位置pos，是一个**迭代器**

#### vector数据存取
功能：对vector中的数据进行存取操作
函数原型：
- `at(int idx);`            //返回是索引idx所指的数据
- `operator[](int idx);`    //返回索引idx所指的数据
- `front();`                //返回容器中第一个数据元素
- `back();`                 //返回容器中最后一个数据元素

通用操作：使用迭代器获取容器数据
```c++
vector<int>::iterator it=v.begin();
cout<<*i<<endl;
```

#### vector互换容器
功能：实现两个容器内元素进行互换
函数原型：
`swap(vec);`        //将vector容器vec与本身的元素互换

注意：通过swap成员函数，可实现收缩内存空间

```c++
#include <iostream>
using namespace std;
#include <vector>

void test() {
	vector<int> v1;
	for (int i = 0; i < 100000; i++) {
		v1.push_back(i);
	}

	cout << "v1的容量为：" << v1.capacity() << endl;
	cout << "v1的大小为：" << v1.size() << endl;

	//通过修改大小的成员函数修改
	v1.resize(3);
	cout << "v1的容量为：" << v1.capacity() << endl;
	cout << "v1的大小为：" << v1.size() << endl;
	//可见容量未变，但是只利用了极少的空间，所以造成浪费

	vector<int> (v1).swap(v1);
	//参数解释：
	//vector<int> ----代表一个匿名对象，
	//vector<int> (v1)----匿名对象构造函数调用，将v1的值赋给匿名对象，该匿名对象的大小为3，容量也为3
	//.swap(v1)----匿名对象成员函数，实现与v1交换
	//该行执行完毕后，v1容量也缩小为3，而匿名对象将由系统回收，实现了 收缩内存空间
	cout << "v1的容量为：" << v1.capacity() << endl;
	cout << "v1的大小为：" << v1.size() << endl;
}

int main() {
	test();

	return 0;
}
```

#### vector预留空间
功能：减少vector在动态扩展容量时的扩展次数
函数原型：
`reserve(int len);`     //容器预留len个元素长度

注意：
- 预留位置**不初始化**，元素不可访问
- 如果数据量较大，可一开始利用reserv预留空间

```c++
#include <iostream>
using namespace std;
#include <vector>

void test() {
	vector<int> v;

	v.reserve(100000);

	int num=0;		//统计分配内存的次数
	int *p = NULL;	//跟进v的内存位置，注意：这里采用int类型指针，因为v[0]实际上返回一个int类型的值
	for (int i = 0; i < 100000; i++) {
		v.push_back(i);
		if (p != &v[0]) {	//v[0]实际上返回的是数组下标为0的元素，取址即可得到容器内部数组的首地址，
							//而v不是数组名，是容器名，不是其内部数组的首地址
			p = &v[0];
			num++;
		}
	}
	cout << num;
}

int main() {
	test();

	return 0;
}
```

### deque容器
功能:双端数组，可以对头端进行插入删除操作
deque与vector的区别：
- vector对于头部的插入、删除效率低，数据量越大，效率越低
- deque相对而言，对头部的插入删除速度会比vector快
- vector访问元素时的速度会比deque快，这和两者的内部实现有关
![](./deque.jpg)

deque内部工作原理：
- deque内部有一个**中控器**，维护每段缓冲区的内容，缓冲区中存放真实数据
- 中控器维护的是每个缓冲区的地址，使得使用deque时像一篇连续的内存空间
![](./deque2.jpg)

* deque容器的迭代器也支持随机访问

#### deque构造函数
函数原型：
- `deque<T> deqT;`          //默认构造
- `deque(beg,end);`         //拷贝构造，将[beg,end)区间中的元素拷贝给本身
- `deque(n,elem)`           //构造函数，将n个elem拷贝给本身
- `deque(const deque &deq);`//拷贝构造

补：对于引用方式传入的容器，如果要防止函数对原容器的修改，可以加const关键字，但是若使用迭代器访问，则应该换为特殊的迭代器`const_iterator`

```c++
#include <iostream>
using namespace std;
#include <deque>

void PrintDeque(const deque<int>& d)
{
	//加const后，迭代器也要用专门的类型
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)	
	{
		//*it=100; //加const后容器的数据不可以修改了
		cout << *it << " ";
	}
	cout << endl;
}

void test() {
	deque<int> d;
	for (int i = 0; i < 10; i++)
	{
		d.push_back(i);
	}

	deque<int> d2(d);
	PrintDeque(d2);

	deque<int> d3(d.begin(), d.end());
	PrintDeque(d3);

	deque<int> d4(4, 100);
	PrintDeque(d4);
}

int main() {
	test();

	return 0;
}
```

#### deque赋值操作
函数原型：
- `dequee &operator=(const deque &deq);`    //重载等号操作符
- `assign(beg,end);`                        //将[beg,end)区间内的数据拷贝赋值给本身
- `assign(n,elem);`                         //将n个elem拷贝赋值给本身

#### deque大小操作
功能：对deque容器的大小进行操作
函数原型：
- `deque.empty();`                  //判断容器是否为空
- `deque.size();`                   //返回容器中元素个数
- `deque.resize(int num);`          //重新指定容器长度为num
                                    //若容器扩大，则以默认值填充新位置
                                    //若容器缩小，则末尾超出容器大小的元素将被删除
- `deque.resize(int num,elem);`     //重新指定容器大小为num
                                    //若容器扩大，则以elem填充新位置
                                    //若容器缩小，则末尾超出容器大小的元素将被删除

注意：deque大小操作和vector很像，但是没有**容量**一说，也没有capacity函数，因为deque容量可以无限去扩展

#### deque插入和删除
注意：插入和删除提供的位置是**迭代器**

函数原型：
两端插入操作：
- `push_back(elem);`        //在容器尾部添加一个数据
- `push_front(elem);`       //在容器头部插入一个数据
- `pop_back();`             //删除容器最后一个数据
- `pop_front();`            //删除容器第一个数据

指定位置操作：
- `insert(pos,elem);`       //在pos位置，插入一个elem元素的拷贝，返回新数据的位置
- `insert(pos,n,elem);`     //在pos位置插入n个elem数据，无返回值
- `insert(pos,beg,end);`    //在pos位置插入[begin,end)区间数据，无返回值
- `clear();`                //清空容器所有数据
- `erase(beg,end);`         //删除[ber,end)区间的数据，返回下一个数据的位置
- `erase(pos);`             //删除pos位置的数据，返回下一个数据的位置


#### deque数据存取
函数原型：
- `at(int idx);`    //返回索引idx所指的数据
- `operator[];`     //返回索引idx所指的数据
- `front();`        //返回容器的第一个数据元素
- `back();`         //返回容器的最后一个数据元素

#### deque排序
可以利用<algorithm>内的sort函数对容器进行排序
支持**随机访问**的迭代器，才能用该算法
sort函数原型：
`sort(interator beg,iterator end);`


### 容器案例——取平均分
有五名选手ABCDE，10个评委分别对其打分，去除最高分，去除最低分，取平均分，输出每位选手成绩

注意：
随机数种子制作：`srand( (usigned int)time(NULL) );`     //注意包含头文件<ctime>或者<time.h>
Tips：
1. 要应用两个容器，刚开始自己的实现让容器包含在了类内，结果是使用容器很复杂，很难分辨
   其实只需要一个容器进行人物切换，另一个容器用完即删除，拿来算分数即可
2. main函数中不要太复杂，先写好框架并用注释注明，然后再在main中列好函数，最后再去实现函数和debug
3. 注意值传递问题，打印的参数和值传递的参数

```c++
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

class Person {
public:
	Person(string name,int score) {
		this->name=name;
		this->score = score;
	}
	string name;
	int score;
};

void CreatPerson(vector<Person> &v)
{
	string seq = "ABCDE";
	for (int i=0;i<5;i++)
	{
		string name = "选手";
		name += seq[i];
		Person p(name, 0);		//初始化选手姓名，初始化分数为0

		//将创建的人放入容器中
		v.push_back(p);
	}
}

void setscore(vector<Person> &v)
{	//添加随机数种子，需要包含time.h或ctime头文件
	srand((unsigned int)(time(NULL)));

	/*for (int i = 0; i < 10; i++)	//通过下标法访问数据
	{
		int score = rand() % 41 + 60;
		v[i].score = score;
	}*/

	//通用方法访问数据
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		deque<int> d;
		//评委打分（用随机数模拟）
		for(int i=0;i<10;i++)
			d.push_back(rand()%41 + 60);	//将分数限制在60-100
		//排序
		sort(d.begin(), d.end());
		//去除最高分与最低分
		d.pop_front();
		d.pop_back();
		//取平均分
		int sum=0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++)
		{
			sum += (*dit);
		}
		it->score = sum / d.size();
	}
	
}

void showscore(const vector<Person> &v)
{
	for (vector<Person>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << it->name << "得了" << (*it).score << "分" << endl;
	}
}

int main(void)
{
	//存储选手信息
	vector<Person> v;

	//创建人物，并赋初值
	CreatPerson(v);

	//打分
	setscore(v);

	//展示
	showscore(v);

	return 0;
}
```

### stack容器
> 特点：

1. 先进后出FILO
2. 栈不允许有遍历行为
3. 栈可以判空，可以返回元素个数
4. 只有顶端元素可以被外界使用

> 常用接口：

构造函数：
- `stack<T> stk;`               //采用类模板实现，stack对象默认构造
- `stack(const stack &stk);`    //拷贝构造

赋值操作：
- `stack &operator=(const stack &stk);`//重载等号运算符

数据存取：
- `push(elem);` //入栈
- `pop();`      //出栈
- `top();`      //返回栈顶元素

大小操作：
- `empty();`    //判空
- `size();`     //返回栈大小

### queue容器
特点：
1. 先进先出FIFO
2. 有两个端口，允许一端新增数据，另一端移除数据
3. 只有队头和队尾能被外界使用，不允许遍历

接口：
构造函数：
- `queue<T> que;`           //采用类模板实现，默认构造
- `queue(const queue &que);`//拷贝构造

赋值操作：
- `queue &operator=(const queue &que);` //重载等号运算符

数据存取：
- `push(elem);` //入队
- `pop();`      //出队
- `back();`     //返回队尾元素
- `front();`    //返回队头元素

大小操作：
- `empty();`    //判空
- `size();`     //返回队的大小

### list容器
**链表list**为物理存储单元上的非连续存储结构，由一系列**结点**构成
结点的组成：
* 数据域：存储数据元素
* 指针域：存放指向下一个结点的指针

链表与数组对比：
* 优点：可以对任意位置进行快速的插入或删除
* 缺点：容器遍历速度没有数组快，占用空间比数组大

STL中的list是一个**双向循环链表**

由于链表存储方式为非连续内存空间，故其迭代器只支持前移和后移，属于**双向迭代器**

list优点：
- 采用动态存储分配，不会造成内存浪费和溢出
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素

list缺点：
- 链表比较灵活，但空间和时间开销较大

list重要性质，插入和删除操作不会造成原有list迭代器的失效！（这在vector中是不成立的）

list和vector是**最常被使用**的容器，各有其优缺点

#### list构造函数
函数原型：
- `list<T> lst;`            //采用类模板实现，默认构造
- `list(beg,end);`          //区间方式构造
- `list(n,elem);`           //用n个elem初始化进行构造
- `list(const list &list);` //拷贝构造

#### list赋值和交换
函数原型：
- `assign(beg,end);`    //将[beg,end)区间中的数据拷贝赋值给本身
- `assign(n,elem);`     //将n个elem拷贝赋值给本身
- `list &operator=(const list &lst);`  //重载等号运算符
- `swap(lst);`          //将lst与本身的元素互换

#### list大小操作
函数原型：
- `size();`             //返回容器中元素个数
- `empty();`            //判断容器是否为空
- `resize(num);`        //重新指定容器长度为num
- `resize(num,elem)`    //重新指定容器长度为num

#### list插入和删除
注意：有的地方要求提供迭代器，remove要求提供元素

函数原型：
- `push_back(elem);`    //在容器尾部插入一个元素
- `pop_back();`         //删除容器中最后一个元素
- `push_front(elem);`   //在容器开头插入一个元素
- `pop_front();`        //从容器开头移除一个元素
- `insert(pos,elem);`   //在pos位置插入元素elem的**拷贝**，返回**新数据**的位置
- `insert(pos,n,elem);` //在pos位置，插入n个elem，无返回值
- `clear();`            //移除容器中所有数据
- `erase(beg,end);`     //删除[beg,end)区间的数据，返回下一个数据的位置
- `erase(pos);`         //删除pos位置的数据，返回下一个数据的位置
- `remove(elem);`       //删除容器中**所有**与elem值匹配的元素

#### list数据操作
list迭代器为**双向迭代器**，不支持随机访问
* 不可以用[]访问list容器中的元素
* 不可以用at()方式访问list容器中的元素
* 其迭代器支持++与--，但不支持+n
  ```c++
    list<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    list<int>::iterator it=L.begin();
    it++;//允许递增
    it--;//允许递减
    //it=it+1;  //不允许随机访问
    //it=it+2;  //不允许随机访问
    //L.at(2);  //不支持用at()访问
  ```

函数原型：
- `front();`    //返回第一个元素
- `back();`     //返回最后一个元素

#### list反转和排序
函数原型：
- `reverse();`  //反转链表  ，注意和vector中的reserve区别
- `sort();`     //链表排序，默认从小到大，若要实现从大到小，需要提供**仿函数**或**成员函数**

注意：
- 所有不支持随机访问的容器，不可以使用标准算法，如sort()
- 不支持随机访问迭代器的容器，一般内部会提供对应的一些算法

```c++
#include <iostream>
using namespace std;
#include <list>

void PrintList(const list<int> &lst) {
	for (list<int>::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//使用一个函数，返回布尔类型，
//用于指定排序规则，让sort实现逆序
bool myCompare(int v1,int v2)
{
	//降序，让第一个数大于第二个数
	return v1 > v2;
}

void test() {
	list<int> lst;
	lst.push_back(10);
	lst.push_back(40);
	lst.push_front(30);
	lst.push_back(20);

	PrintList(lst);

	lst.sort();
	PrintList(lst);

	lst.sort(myCompare);	//降序排序，是一个重载函数
	PrintList(lst);
}

int main() {
	test();

	return 0;
}
```

#### 排序案例
案例：将Person自定义数据类型进行排序，其中属性有姓名、年龄、身高、体重
排序规则：按照年龄进行升序，如果年龄相同，则按照身高进行降序，若身高相同，则按照体重进行升序

```c++
#include <iostream>
using namespace std;
#include <list>

class Person {
	
public:
	Person(string name, int age, int weight, int height)
	{
		this->m_name = name;
		this->m_age = age;
		this->m_height = height;
		this->m_weight = weight;
	}

	string m_name;
	int m_age;
	int m_weight;
	int m_height;
};

void PrintList(const list<Person>& L)
{
	for (list<Person>::const_iterator it = L.begin(); it != L.end(); it++)
	{
		cout << (*it).m_name << " " << it->m_age << "岁 高" 
			<< (*it).m_height << "m 体重" 
			<< it->m_weight << "kg" << endl;
	}
}

//指定排序规则
bool compare(Person p1, Person p2)
{
	if (p1.m_age == p2.m_age)
	{
		if (p1.m_height == p2.m_height)
			return p1.m_weight < p2.m_weight;	//年龄身高相同，按体重升序
		else
			return p1.m_height > p2.m_height;	//年领相同，身高不同，按身高降序
	}
	else
		return p1.m_age < p2.m_age;	//年龄不同，按年龄升序
}

void test() {
	list<Person> L;
	Person p1("小明", 18, 40, 165);
	Person p2("小周", 18, 43, 170);
	Person p3("小刘", 23, 55, 170);
	Person p4("小王", 22, 60, 175);
	Person p5("小罗", 24, 53, 165);
	Person p6("小苏", 18, 48, 165);
	Person p7("小张", 22, 55, 170);
	Person p8("小龙", 22, 46, 160);

	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);
	L.push_back(p7);
	L.push_back(p8);

	PrintList(L);

	cout << "------------------------" << endl;
	cout << "按年龄升序，年龄相同则按身高降序，身高相同则按体重升序" << endl;
	L.sort(compare);
	PrintList(L);
}

int main() {
	test();

	return 0;
}
```

### set/multiset
set：所有元素豆花在插入时**自动被排序**
set/multiset本质属于**关联式容器**，底层结构使用**二叉树**实现
set与multiset区别：
- set不允许容器中有重复的元素
- multiset允许容器中有重复的元素

#### set构造和赋值
构造函数：
- `set<T> st;`       //默认构造函数
- `set(const set &st)`//拷贝构造函数

赋值:
- `set &operator=(const set &st);`

注意：
- set插入方式，只有使用insert函数，并无其他形式
- set不允许插入重复值（set插入相同的值，不会报错，只是输出时仅会输出一次该值 ）

#### set大小和交换
注意：set容器不支持resize操作

函数原型：
- `size();`     //返回容器中元素的数目
- `empty();`    //判空
- `swap(st);`   //交换两个集合容器

#### set插入和删除
函数原型：
- `insert(elem);`   //在容器中插入元素
- `clear();`        //清楚所有元素
- `erase(pos);`     //删除pos迭代器所指的元素，返回下一个元素的迭代器
- `erase(beg,end);` //删除区间[beg,end)的所有元素，返回下一个元素的迭代器
- `erase(elem);`    //删除容器中值为elem的元素

#### set查找与统计
函数原型：
- `find(key);`  //查找key是否存在，若存在，则返回该元素的**迭代器**；否则，返回**set.end()**
- `count(key);` //统计key的元素个数
  //其实对set容器而言，只会返回0或1
  //对于multiset容器，可能返回>=0的数

#### set和multiset区别
区别：
- set不可以插入重复的数据，multiset可以
- set插入数据的同时会返回插入结果，表示插入是否成功
- multiset不会检测数据，因此可以插入重复数据

```c++
#include <iostream>
using namespace std;
#include <set>

void test() {
	set<int> s;
	
	//insert()函数返回的类型是对组,对组中包含一个迭代器类型和一个布尔类型
	pair<set<int>::iterator,bool> ret=s.insert(10);
	
	if (ret.second)
		cout << "第一次插入成功" << endl;
	else
		cout << "第一次插入失败" << endl;

	ret = s.insert(10);
	if(ret.second)
		cout << "第二次插入成功" << endl;
	else
	cout << "第二次插入失败" << endl;
}

int main() {
	test();

	return 0;
}
```

#### 对组pair
对组，即成对出现的数据，利用对组可返回两个数据

两种创建方式：
- `pair<type,type> p (value1,value2);`
- `pair<type,type> p=make_pair(value1,value2);`

```c++
#include <iostream>
using namespace std;
#include <string>

void test() {
	//第一种创建方式
	pair<string, int> p("Tom", 18);
	cout << "姓名：" << p.first << "\t年龄：" << p.second << endl;

	//第二种创建方式
	pair<string, int> p2 = make_pair("Jerry", 17);
	cout << "姓名：" << p2.first << "\t年龄：" << p2.second << endl;
}

int main() {
	test();

	return 0;
}
```

#### set容器排序
set容器默认排序规则为从小到大

利用**仿函数**，可以改变排序规则

```c++
#include <iostream>
using namespace std;
#include <set>

class Compare {
public:
	//返回值应为bool类型，重载()运算符以实现仿函数
	bool operator()(int val1, int val2) const	//该const为vs要求
	{
		//val1大于val2时返回真，实现从大到小排序
		return val1 > val2;
	}
};

void test() {
	set<int> s1;
	s1.insert(10);
	s1.insert(50);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);

	for (set<int>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//由于在插入时即实现排序，s1的顺序无法再改变
	//要实现改变排序规则，需要在插入之前写好仿函数
	set<int,Compare> s2;

	s2.insert(10);
	s2.insert(50);
	s2.insert(30);
	s2.insert(20);
	s2.insert(40);

	//注意这里的set的参数也要同建立s2的相同
	for (set<int, Compare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

int main() {
	test();

	return 0;
}
```

对于**自定义数据类型**，一般都会指定排序规则
Tips：
1. 对于自定义数据类型，即使写了仿函数以指定排序规则，使用set容器依旧不允许排序规则中出现重复的数据，否则将会导致相应的后续插入的自定义数据插入失败，此时应使用multiset容器
```c++
#include <iostream>
using namespace std;
#include <set>

class Person {
public:
	Person(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}
	string m_name;
	int m_age;
};

class ComparePerson {
public:
	//仿函数，实现自定义类型的比较
	bool operator()(const Person& p1, const Person& p2) const
	{
		//实现从小到大排序
		return p1.m_age < p2.m_age;
	}
};

void test() {
	multiset<Person,ComparePerson> s;

	//注意，由于年龄有相同的数值，故会丢失后面插入的相同数据，应使用multiset解决
	Person p1("小王", 24);
	Person p2("小罗", 23);
	Person p3("小张", 22);
	Person p4("小刘", 22);
	Person p5("小龙", 25);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	s.insert(p5);

	//直接运行将会报错，因为自定义类型在插入时无法比较并排序，需要自定义排序
	for (multiset<Person,ComparePerson>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "姓名：" << (*it).m_name << "\t年龄：" << it->m_age << endl;
	}
}

int main() {
	test();

	return 0;
}
```

### map/multimap
map简介：
- map中所有元素都是**pair**
- pair中第一个元素为**key(键值)**，起**索引作用**，第二个元素为**value(实值)**
- 所有元素都会根据元素的键值自动排序

本质：
- map/multimap属于**关联式容器**，底层结构是用**二叉树**实现的

优点：
- 可以根据key值快速找到value值

map和multimap区别：
- map不允许容器有重复的key值元素
- multimap允许容器中有重复的key值元素

#### map构造和赋值
构造函数原型：
- `map<T1,T2> mp;`      //默认构造
- `map(const map &mp);` //拷贝构造

赋值：
- `map &operator=(const map &mp);`

```C++
#include <iostream>
using namespace std;
#include <map>

void PrintMap(map<int, int>& mp)
{
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		cout << (*it).first << " " << it->second << endl;
	}
	cout << endl;
}

void test() {
	map<int, int> mp;

	mp.insert(pair<int, int>(5, 50));	//此处使用了匿名对组，pair<int,int> 是一个匿名对组
										//pair<int,int> (5,50)调用其构造函数初始化该匿名对组
	mp.insert(pair<int, int>(2, 20));
	mp.insert(pair<int, int>(1, 10));
	mp.insert(pair<int, int>(4, 40));
	mp.insert(pair<int, int>(3, 30));

	PrintMap(mp);

	map<int, int> m2(mp);
	PrintMap(m2);

	map<int, int> m3;
	m3 = m2;
	PrintMap(m3);
}

int main() {
	test();

	return 0;
}
```

### map大小和交换
函数原型：
- `size();`		//返回容器中元素的数目
- `empty();`	//判断容器是否为空
- `swap();`		//交换两个集合容器

### map插入和删除
函数原型：
- `insert(elem);`	//在容器中插入元素
- `clear();`		//清除所有元素
- `erase(pos);`		//删除迭代器pos所指的内容，返回下一个元素的迭代器
- `erase(beg,end);`	//删除区间[beg,end)的所有元素，返回下一个元素的迭代器
- `erase(key);`		//删除容器中**索引值**为key的元素，注意，不是删除value为key的元素

```c++
#include <iostream>
using namespace std;
#include <map>

void PrintMap(const map<int, int>& m)
{
	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key=" << it->first << "  value=" << it->second;
		cout << endl;
	}
	cout << endl;
}

void test() {
	map<int, int> m1;
	
	//第一种插入方式
	m1.insert(pair<int, int>(1, 10));
	//第二种插入方式
	m1.insert(make_pair(2, 20));
	//第三种插入方式
	m1.insert(map<int, int>::value_type(3, 30));
	//第四种插入方式(不推荐)
	m1[4] = 40;
		//注意：不建议使用第四种方式插入，如有以下代码将创建一个新的数据
		//cout << m1[5] << endl;	//可以看到新增了key为5的数据，value值默认为0
		//[]方式更建议用于去key访问value，而不是去插入
	PrintMap(m1);

	map<int, int> m2;
	m2 = m1;
	m2.erase(m2.begin());
	PrintMap(m2);

	m2.erase(3);	//按key值删除，与value值无关
	PrintMap(m2);
}

int main() {
	test();

	return 0;
}
```

#### map查找和统计
函数原型：
- `find(key);`		//查找key值为key的元素，若查到，则返回其迭代器，否则返回迭代器map.end()
- `count(key);`		//统计key值为key的元素个数
  对于map而言，由于不允许重复key值的元素，故该结果只可能为0或1
  对于multimap而言，count统计可能大于1

#### map容器排序
map容器插入时默认从小到大排序
通过**仿函数**可自定义排序方案

 ```c++
#include <iostream>
using namespace std;
#include <map>
#include<string>

//class Person;
//class Compare;

class Person {
public:
	Person(string name, int age)
	{
		this->name = name;
		this->m_age = age;
	}
	int m_age;
	string name;
};

class Compare {
public:
	bool operator()(const Person &p1,const Person &p2) const
	{
		//实现按年龄从大到小排序
		return p1.m_age > p2.m_age;
	}
};

//注意传入的类型也要改加Compare
void PrintMap(map<Person, int, Compare>& m)		//必须写在Compare和Person后面，不然编译器报错，但是前面加了声明也会报错？
{
	for (map<Person, int, Compare>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout <<"姓名:"<<it->first.name 
			<< " 年龄：" << it->first.m_age 
			<< " 体重：" << (*it).second << endl;
	}
}

void test() {
	Person p1("小龙", 22);
	Person p2("小明", 21);
	Person p3("小张", 23);
	Person p4("小罗", 24);

	map<Person, int,Compare> m;
	m.insert(make_pair(p1, 44));
	m.insert(make_pair(p2, 40));
	m.insert(make_pair(p3, 46));
	m.insert(make_pair(p4, 60));

	PrintMap(m);
}

int main() {
	test();

	return 0;
}
 ```

### 案例-员工分组
公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司后，需要指派员工在哪个部门工作
员工信息：姓名、工资组成
部门分为：策划、美术、研发
随机给10名员工分配部门和工资
通过multimap进行信息的插入key（部门编号）value（员工）
分部门显示员工信息

自己给出的方案：
```c++
#include <iostream>
using namespace std;
#include <map>
#include <vector>
#include<string>
#include<ctime>

class Staf {
public:
	/*Staf(string name, int salary)
	{
		this->name = name;
		this->salary = salary;
	}*/
	string name;
	int salary;
};

void Creat(multimap<int, Staf>& m) {
	//随机数种子
	srand((unsigned int)time(NULL));
	//创建员工并插入vector容器存储
	Staf p1;
	Staf p2;
	Staf p3;
	Staf p4;
	Staf p5;
	Staf p6;
	Staf p7;
	Staf p8;
	Staf p9;
	Staf p10;
	vector<Staf> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	v.push_back(p6);
	v.push_back(p7);
	v.push_back(p8);
	v.push_back(p9);
	v.push_back(p10);

	//初始化姓名与工资,并插入multimap中初始化部门
	string name = "ABCDEFGHIJ";
	int i = 0;	//在for内部初始化迭代器后，好像不允许再在for内再初始化其他变量？
	for (vector<Staf>::iterator it = v.begin(); it != v.end(); i++, it++)
	{
		it->name = name[i];
		it->salary = rand() % 3001 + 2000;
		m.insert(make_pair(rand() % 3 + 1,*it));
	}
}

void ShowStaf(const multimap<int, Staf>& m)
{
	//选择输出部门语句
	for (multimap<int, Staf>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		if (it->first == 1)
			cout << "部门：策划";
		else if (it->first == 2)
			cout << "部门：美术";
		else
			cout << "部门：研发";

		cout << " 姓名：" << it->second.name
			<< " 工资：" << it->second.salary << endl;
	}
}

int main() {
	//存储员工信息与部门信息，并自动排序
	multimap<int, Staf> m;
	//创建并初始化员工信息
	Creat(m);
	//显示员工信息
	ShowStaf(m);

	return 0;
}
```

示范代码：
```c++
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <map>
#include <ctime>

//公司今天招聘了5个员工，5名员工进入公司之后，需要指派员工在那个部门工作
//人员信息有: 姓名 年龄 电话 工资等组成
//通过Multimap进行信息的插入 保存 显示
//分部门显示员工信息 显示全部员工信息

enum
{
	CAIWU,RENLI,MEISHU
};

class Worker
{
public:
	string m_Name;//姓名
	int m_Money; //工资
};

void createWorker(vector<Worker>&v)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5;i++)
	{
		Worker worker;
		worker.m_Name = "员工";
		worker.m_Name += nameSeed[i];

		worker.m_Money = rand() % 10000 + 10000; // 10000 ~ 19999
		
		v.push_back(worker);
	}
}

void setGroup(vector<Worker>&v, multimap<int, Worker>&m)
{
	for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
	{
		//随机产生部门编号  0 1 2 
		int id = rand() % 3;

		//将员工插入到分组的容器中
		m.insert(make_pair(id, *it));
	}

}

void showWorker(multimap<int,Worker>&m)
{
	// 0 A   0  B   1  C   2  D  2 E
	cout << "财务部门人员如下： " << endl;
	multimap<int,Worker>::iterator pos = m.find(CAIWU);
	int count = m.count(CAIWU);
	int index = 0;

	for (; pos != m.end(), index < count; pos++, index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}

	cout << "人力资源部门人员如下： " << endl;
	pos = m.find(RENLI);	//利用find成员函数，查到第一个人的位置
	count = m.count(RENLI);	//利用count成员函数，统计该key值元素的个数，控制输出人数
	index = 0;

	for (; pos != m.end(), index < count; pos++, index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}


	cout << "美术部门人员如下： " << endl;
	pos = m.find(MEISHU);
	count = m.count(MEISHU);
	index = 0;

	for (; pos != m.end(), index < count; pos++, index++)
	{
		cout << "姓名： " << pos->second.m_Name << " 工资： " << pos->second.m_Money << endl;
	}
}

int main(){

	//随机数种子
	srand((unsigned int)time(NULL));

	vector<Worker>v; //存放员工的容器
	//员工的创建
	createWorker(v);

	//员工分组
	multimap<int, Worker>m;
	setGroup(v,m);

	//分部门显示员工
	showWorker(m);

	//for (vector<Worker>::iterator it = v.begin(); it != v.end();it++)
	//{
	//	cout << "姓名： " << it->m_Name << " 工资： " << it->m_Money << endl;
	//}

	system("pause");
	return EXIT_SUCCESS;
}
```

## [函数对象](#目录)
重载函数调用操作符的**类**，其对象即称为**函数对象**
函数对象使用重载的`()`时，行为类似函数调用，故也叫**仿函数**
本质：函数对象(仿函数)是一个类，不是一个函数

### 函数对象使用
特点
- 函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值
- 函数对象超出普通函数的概念：函数对象可以有自己的状态
- 函数对象可以作为参数传递

```c++
#include <iostream>
using namespace std;
#include <string>
//函数对象/仿函数
class NEWADD1 {
public:
	int operator ()(int a, int b) {
		return a + b;
	}
};

class NEWPRINT {
public:
	NEWPRINT() {
		this->count = 0;
	}
	void operator ()(string str) {
		cout << str << endl;
		count++;
	}

	int count;
};

void doprint(NEWPRINT& p, string str) {
	p(str);
}

//函数对象的用法和函数调用很类似，但本质上不是一个函数，而是对象
void test1()
{
	NEWADD1 add;
	cout << add(1, 2) << endl;
}

//函数对象可以有自己的属性
void test2() {
	NEWPRINT print;
	print("hello c++");
	print("hello c++"); 
	print("hello c++");
	cout << "调用print的次数：" << print.count << endl;
}

//函数对象可以作为参数传递
void test3() {
	NEWPRINT p;
	doprint(p, "hello world!");
}

int main(void)
{
	test1();
	test2();
	test3();

	return 0;
}
```

### 谓词
返回bool类型的**仿函数**称为**谓词**
- 如果`operator()`接受一个参数，则称为**一元谓词**
- 如果`operator()`接受两个参数，则称为**二元谓词**

#### 一元谓词
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Greaterfive {
public:
	bool operator()(int num)
	{
		return num > 5;
	}
};

void test1()
{
	vector<int> v;
	for(int i = 1; i <= 10; i++)
	{
		v.push_back(i);
	}

	//find_if()函数声明在<algorithm>里
	//此次目的：找到大于5的数字
	//Greaterfive() 是一个 "匿名函数对象" ，也可以使用一个实例化的函数对象作为参数
	vector<int>::iterator it = find_if(v.begin(), v.end(), Greaterfive());
	
	if (it == v.end())
	{
		cout << "未找到符合条件的元素" << endl;
	}
	else
	{
		cout << "找到符合条件的元素为" << *it << endl;
	}
	
}

int main(void)
{
	test1();
	
	return 0;
}
```
#### 二元谓词
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class revecompare {
public:
	bool operator()(int val1, int val2)
	{
		return val1 > val2;
	}
};

void test1()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(70);
	v.push_back(40);
	v.push_back(50);
	v.push_back(80);

	sort(v.begin(), v.end());
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	//sort算法默认排序规则为从小到大，且不支持自定义数据类型排序
	//想要修改排序规则，需要借助仿函数（函数对象）作为sort的参数以使用重载的sort
	cout << "------------reverse-------------" << endl;
	sort(v.begin(), v.end(), revecompare());
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
}

int main(void)
{
	test1();
	
	return 0;
}
```

### 内建函数对象
STL内建了一些函数对象

分类：
- 算术仿函数
- 关系仿函数
- 逻辑仿函数

用法：
- 这些仿函数所产生的对象，用法和普通函数一样
- 使用内建函数对象，必须包含头文件`<functional>`

#### 算术仿函数
功能特点：
- 实现四则运算
- negate为**一元运算**，其他都是二元运算

函数原型：
- `template<class T> T plus<T>`		//加法仿函数
- `template<class T> T minus<T>`	//减法仿函数
- `template<class T> T multiplies<T>`//乘法仿函数
- `template<class T> T divides<T>`	//除法仿函数
- `template<class T> T modulus<T>`	//取模仿函数
- `template<class T> T negate<T>`	//取反仿函数一元）

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <functional>

void test1()
{
	negate<int> n;
	cout << n(50) << endl;

	plus<int> p;	
	//注意：虽然是二元运算，但是由于不能对不同数据类型计算，故只需要写一次数据类型在模板中
	int result = p(10, 20);
	cout << result << endl;
}

int main(void)
{
	test1();
	
	return 0;
}
```

#### 关系仿函数
功能：实现关系对比(可以代替自己手写仿函数来进行对比)
仿函数原型：
- `template<class T> bool equal_to<T>`
- `template<class T> bool not_equal_to<T>`
- `template<class T> bool greater<T>`
- `template<class T> bool greater_equal<T>`
- `template<class T> bool less<T>`
- `template<calss T> bool less_equal<T>`

通过关系仿函数实现从大到小排序是很常用的

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <functional>
#include <algorithm>

void test1()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(70);
	v.push_back(40);
	v.push_back(50);
	v.push_back(80);

	sort(v.begin(), v.end());
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	//sort算法默认排序规则为从小到大，且不支持自定义数据类型排序
	//想要修改排序规则，需要借助仿函数（函数对象）作为sort的参数以使用重载的sort
	cout << "------------reverse-------------" << endl;
	sort(v.begin(), v.end(), greater<int>());	//使用了匿名的内建函数对象,不需要再写仿函数
	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
}

int main(void)
{
	test1();
	
	return 0;
}
```

#### 逻辑仿函数
功能：实现逻辑运算
函数原型：
- `template<class T> bool logical_and<T>`	//逻辑与
- `template<class T> bool logical_or<T>`	//逻辑或
- `templare<class T> bool logical_not<T>`	//逻辑非

逻辑仿函数在实际开发中使用较少

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <functional>
#include <algorithm>

void test1()
{
	vector<bool> v1;
	v1.push_back(true);
	v1.push_back(true);
	v1.push_back(false);
	v1.push_back(true);
	v1.push_back(false);

	for (vector<bool>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		cout << *it << " ";
	}

	cout << endl;

	//
	vector<bool> v2;
	v2.resize(v1.size());//修改v2大小，否则搬运将出错（因为没有为目标容器分配内存空间）

	//将v的内容搬运到v2中，并执行取反操作
	//transform函数包含于<algorithm>头文件中
	transform(v1.begin(),v1.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
	{
		cout << *it << " ";
	}
}

int main(void)
{
	test1();
	
	return 0;
}
```

### STL常用算法
算法主要包含于头文件`<algorithm> <functional> <numeric> `中
- `<algorithm>`，所有STL头文件中最大的一个，涉及比较、交换、查找、遍历、复制、修改等等
- `<numeric>`，体积很小，只包括几个在序列上进行简单数学运算的模板函数
- `<functional>`，定义了一些模板类，用以声明函数对象

#### 常用遍历算法
`for_each`	//遍历容器
`transform`	//搬运容器到另一个容器中

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <functional>
#include <algorithm>

void print1(int val)
{
	cout << val << " ";
}

class print2 {
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test1()
{
	vector<int> v;
	v.push_back(10);
	v.push_back(70);
	v.push_back(40);
	v.push_back(50);
	v.push_back(80);

	for_each(v.begin(), v.end(), print1);	//注意，仅传入函数名，因为函数名是

	cout << endl;
	for_each(v.begin(), v.end(), print2());	//注意，print2() 为匿名函数对象(仿函数)，不是函数
}

int main(void)
{
	test1();
	
	return 0;
}
```

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Transform {
public:
	int operator()(int val)
	{
		return val + 100;
	}
};

class print {
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test1()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(70);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(80);

	vector<int> v2;
	v2.resize(v1.size());
	//注意目标容器需要开辟空间

	transform(v1.begin(), v1.end(), v2.begin(),Transform());	
	//第四个参数可触发重载版本的transform，该参数为一个函数或函数模板
	//在其内部可进行运算，并将结果将到目标容器中

	for_each(v2.begin(), v2.end(), print());
}

int main(void)
{
	test1();
	
	return 0;
}
```

#### 常用查找算法
- `find`			//查找元素
- `find_if`			//按条件查找元素
- `addjacent_find`	//查找相邻重复元素
- `binary_search`	//二分查找法
- `count`			//统计元素个数
- `count_if`		//按条件统计元素个数

> find

功能：查找指定元素，找到返回指定元素的迭代器，找不到则返回结束迭代器

函数原型：
`find(iterator beg,iterator end,value);`
- beg开始迭代器
- end结束迭代器
- value查找的元素

注意：
- 对于自定义数据类型，需要重载`==`
- 无论是否查找成功，都会返回**迭代器**

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

class Person {
public:
	Person(int age, string name) {
		this->age = age;
		this->name = name;
	}

	int age;
	string name;
};

void test1()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(70);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(80);

	auto it = find(v1.begin(), v1.end(), 20);
	if (it == v1.end())
	{
		cout << "未找到相应数据" << endl;
	}
	else
	{
		cout << "找到数据：" << *it << endl;
	}
}

bool operator==(Person p1, Person p2) {
	return p1.name == p2.name && p1.age == p2.age;
}

void test2() {
	vector<Person> v;

	Person p1(10, "aaa");
	Person p2(20, "bbb");
	Person p3(30, "ccc");
	Person p4(40, "ddd");
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	vector<Person>::iterator it = find(v.begin(), v.end(), p3);
	if (it == v.end())
	{
		cout << "未找到相应数据" << endl;
	}
	else
	{
		cout << "找到数据：" << (*it).name << " " << it->age << endl;
	}
}

int main(void)
{
	test1();
	test2();

	return 0;
}
```

> find_if

功能：按条件查找元素，找到则返回指定位置迭代器，找不到则返回结束迭代器
函数原型：
`find_if(iterator beg,iterator end,_Pred);`
- beg开始迭代器
- end结束迭代器
- _Pred函数或者谓词（返回bool类型的仿函数）

注意：
- 无论查找是否成功，都返回迭代器
- 无论是内置数据类型还是自定义数据类型，都需要提供函数或谓词以确定查找规则

Tips:
1. 使用引用或指针时（为了加快执行速度），如果函数不应对原参数修改，应加**const**限定
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

class Person {
public:
	Person(int age, string name) {
		this->age = age;
		this->name = name;
	}

	int age;
	string name;
};

class GreaterFifty {
public:
	bool operator()(const int &val) {//注意：使用引用或指针时，如果函数不应对原参数修改，应加const限定
		return val > 50;
	}
};

void test1()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(70);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(80);

	//查找内置数据类型
	auto it = find_if(v1.begin(), v1.end(), GreaterFifty());
	if (it == v1.end())
	{
		cout << "未找到相应数据" << endl;
	}
	else
	{
		cout << "找到数据：" << *it << endl;
	}
}

class GreaterAgeTwenty {
public:
	bool operator()(const Person& p) {
		return p.age > 20;
	}
};

void test2() {
	vector<Person> v;

	Person p1(10, "aaa");
	Person p2(20, "bbb");
	Person p3(30, "ccc");
	Person p4(40, "ddd");
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	//查找自定义数据类型
	vector<Person>::iterator it = find_if(v.begin(), v.end(), GreaterAgeTwenty());
	if (it == v.end())
	{
		cout << "未找到相应数据" << endl;
	}
	else
	{
		cout << "找到数据：" << (*it).name << " " << it->age << endl;
	}
}

int main(void)
{
	test1();
	test2();

	return 0;
}
```

> adjacnt_find

功能：查找**相邻**、**重复**的元素，查找到则返回第一个元素的迭代器，否则返回结束迭代器
函数原型：
`adjacent_find(iterator beg,iterator end);`
- beg开始迭代器
- end结束迭代器

> binary_search

功能：查找指定元素是否存在
函数原型：
`bool binary_search(iterator beg,iterator end,valve)`
- beg开始迭代器 
- end结束迭代器
- value查找的元素

注意：
- 二分查找法效率很高，但是要求查找的容器中元素序列必须**有序**
- 返回bool类型，而不是迭代器
- 只能确定元素是否存在，无法确定其位置

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>

void test1()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(10 * i);
	}

	//二分查找法，要求查找容器中元素必须有序！
	bool result = binary_search(v1.begin(), v1.end(), 50);
	if (result)
	{
		cout << "找到数据" << endl;
	}
	else
	{
		cout << "未找到数据" <<endl;
	}
}

int main(void)
{
	test1();
	
	return 0;
}
```

> count

功能：统计元素个数，返回int类型
函数原型：
`count(iterator beg,iterator end,value);`
- beg开始迭代器
- end结束迭代器
- value要统计的元素

注意：统计**自定义数据类型**时，需要配合重载`operator==`

> count_if

功能：按条件统计元素个数
函数原型：
`count_if(iterator beg,iterator end,_Pred);`
- beg开始迭代器
- end结束迭代器
- _Pred谓词

注意：需要使用谓词，来对条件进行判断

#### 常用排序算法
- `sort`			//对容器内元素进行排序
- `random_shuffle`	//洗牌，指定范围内的元素随机调整次序
- `merge`			//容器元素合并，并存储到另一容器中
- `reverse`			//反转指定范围的元素

> sort

功能：对容器内元素进行排序，不写谓词则默认**升序排列**（从小到大）
函数原型：
`sort(iterator beg,iterator end);`
`sort(iterator beg,iterator end,_Pred);`
- beg 开始迭代器
- end 结束迭代器
- _Pred 谓词（**选填**，是一个重载版本）

注意：sort算法属于开发中最常用的算法之一，必须熟练掌握

> random_shuffle

功能：洗牌，将指定范围内的元素随机调整次序
函数原型：
`random_shuffle(iterator beg,iterator end);`
- beg 开始迭代器
- end 结束迭代器

注意：该函数若要实现真正随机，仍需要在主函数中提供**随机数种子**`srand((usigned int)time(NULL));`

> merge

功能：将两个容器元素合并，并存储到另一容器中
函数原型：
`merge(iterator beg1,iterator end1,iterator beg2,iteratro end2,iterator dest);`
- beg1 容器1的开始迭代器
- end1 容器1的结束迭代器
- beg2 容器2的开始迭代器
- end2 容器2的结束迭代器
- dest 目标容器的开始迭代器

注意：目标容器需要提前开辟空间
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

class Print {
public:
	void operator()(int val)	//注意普通仿函数和谓词的区别
								//仿函数和谓词都要求通过operator重载()运算符
								//但谓词要求返回bool类型  即谓词属于仿函数
	{
		cout << val << " ";
	}
};

void test1()
{
	vector<int> v1;
	vector<int> v2;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	for (int i = 100; i < 110; i++)
	{
		v2.push_back(i);
	}
	
	vector<int> TargetV;
	TargetV.resize(v1.size() + v2.size());
	//为目标容器开辟空间，否则将导致出错

	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), TargetV.begin());
	for_each(TargetV.begin(), TargetV.end(), Print());

}

void test2() {
	
}

int main(void)
{
	test1();
	test2();

	return 0;
}
```

> reverse

功能：将容器内的元素进行反转
函数原型：
`reverse(iterator beg,iteratro end);`
- beg 开始迭代器
- end 结束迭代器

注意：
`reverse`为`<algorithm>`内的**反转算法**
`reserve`为`vector`容器中的**预留空间成员函数**

#### 常用拷贝、替换算法
- `copy`		//容器内指定范围的元素拷贝到另一容器中
- `repalce`		//将容器内指定范围的旧元素修改为新元素
- `replace_if`	//容器内指定范围满足条件的元素替换为新元素
- `swap`		//互换两个容器的元素

> copy

功能：容器内指定范围的元素拷贝到另一容器中
函数原型：
`copy(iterator beg,iterator end,iterator dest);`
- beg 开始迭代器
- end 结束迭代器
- dest 目标起始迭代器

注意：目标容器需要先开辟空间

> replace

功能：将容器内制定范围的旧元素修改为新元素
函数原型：
`replace(iterator beg,iterator end,oldvalue,newvalue);`
- beg 开始迭代器
- end 结束迭代器
- oldvalue 旧元素
- newvalue 新元素

注意：replace会替换掉容器中**所有**的oldvalue

> replace_if

功能：将区间内满足条件的元素，替换成指定元素
函数原型：
`replace_if(iterator beg,iterator end,_Pred,newvalue);`
- beg 开始迭代器
- end 结束迭代器
- _Pred 谓词
- newvalue 替换的新元素

该函数利用仿函数，灵活筛选满足的条件

> swap

功能：互换两个容器，交换的容器要**同种类型**
函数原型：
`swap(constainer c1,container c2);`
- c1 容器1
- c2 容器2

注意：**不允许**互换两个**不同类型**的容器

#### 常用算术生成算法
注意：算术生成算法属于小型算法，使用时应包含头文件`#include <numeric>`
- `accumulate`	//计算容器元素累计总和
- `fill`		//向容器中添加元素

> accumulate

功能：计算区间内，容器元素累计总和
函数原型：
`accumulate(iterator beg,iterator end,value);`
- beg 开始迭代器
- end 结束迭代器
- value 起始值

> fill

功能：向容器中填充指定的元素，对于**后期填充**的作用更大
函数原型：
`fill(iteratro beg,iterator end,value);`
- beg 开始迭代器
- end 结束迭代器
- value 填充的值

#### 常用集合算法
- `set_itersection`	//求两个容器的交集
- `set_union`		//求两个容器的并集
- `set_difference`	//求两个容器的差集

> set_intersection

功能：求两个容器的交集
函数原型：
`set_intersection(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dest);`
- beg1 容器1的起始迭代器
- end1 容器1的结束迭代器
- beg2 容器2的起始迭代器
- end2 容器2的结束迭代器
- dest 目标容器开始迭代器

注意：
1. 求交集的两个集合必须是**有序序列**
2. 目标容器开辟空间需要取**两个容器大小的最小值**（特殊情况）
3. set_intersection返回值是交集中**最后一个元素的位置（即最后一个元素的迭代器）**
```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

void Print(int val)
{
	cout << val << " ";
}

void test1()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}
	v2.push_back(16);
	v2.push_back(17);
	//v2.push_back(11);	//加入此行代码将出错
						//特别注意，set_intersection要求两容器中元素是有序的，否则将出错

	vector<int> TargetV;
	//必须为目标容器开辟空间,经分析，需要的空间最大为较小容器的大小（特殊情况）
	TargetV.resize(min(v1.size(), v2.size()));	//min函数返回参数中的最小值

	//set_intersection函数返回交集末尾元素的迭代器
	auto End=set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), TargetV.begin());

	//注意：遍历时，结束迭代器需要由set_intersection提供，因为遍历到TargetV.end()是特殊情况才达到的交集长度
	for_each(TargetV.begin(), TargetV.end(), Print);
	cout << endl;
	for_each(TargetV.begin(), End, Print);

}

void test2() {
	
}

int main(void)
{
	test1();
	test2();

	return 0;
}
```

> set_union

功能：求两个集合的并集  
函数原型：
`set_union(interator beg1,iterator end1,iterator beg2,iterator end2,iterator dest);`
- beg1 容器1开始迭代器
- end1 容器1结束迭代器
- beg2 容器2开始迭代器
- end2 容器2结束迭代器
- dest 目标容器开始迭代器

注意：
1. 两个集合必须是**有序序列**
2. 目标容器开辟的空间为两个容器的大小之和（特殊情况）
3. set_union返回值时并集中最后一个元素的位置（迭代器）

> set_difference

功能：求两个集合的差集  
函数原型：  
`set_difference(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dest);`
- beg1 容器1开始迭代器
- end1 容器1结束迭代器
- beg2 容器2开始迭代器
- end2 容器2结束迭代器
- dest 目标容器开始迭代器

注意：
1. 求差集的两个集合必须是**有序序列**
2. 目标容器开辟空间为**两个容器大小的最大值**（特殊情况）
3. set_difference返回差集中最后一个元素的位置（迭代器）
4. 注意求差集有顺序之分，
	v1和v2的差集表示v1中于v2不同的元素，
	v2和v1的差集表示v2中于v1不同的元素

```c++
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

void Print(int val)
{
	cout << val << " ";
}

void test1()
{
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}
	

	vector<int> TargetV;
	//必须为目标容器开辟空间,经分析，需要的空间最大为较大容器的大小
	TargetV.resize(max(v1.size(), v2.size()));	//max函数返回参数中的最大值

	//set_difference函数返回交集末尾元素的迭代器
	auto End1=set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), TargetV.begin());

	//注意：遍历时，结束迭代器需要由set_difference提供，因为遍历到TargetV.end()是特殊情况才达到的交集长度
	for_each(TargetV.begin(), TargetV.end(), Print);
	cout << endl;
	for_each(TargetV.begin(), End1, Print);
	cout << endl;

	auto End2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), TargetV.begin());

	//注意：遍历时，结束迭代器需要由set_difference提供，因为遍历到TargetV.end()是特殊情况才达到的交集长度
	for_each(TargetV.begin(), TargetV.end(), Print);
	cout << endl;
	for_each(TargetV.begin(), End2, Print);
}

void test2() {
	
}

int main(void)
{
	test1();
	test2();

	return 0;
}
```


演讲比赛流程管理系统总结：
1. 从简单到困难，逐步实现功能并测试代码，不要去一下子考虑太多实现（大象不是一口吃掉的）
2. 每实现一个小功能，则在主函数写测试代码以debug，不要的测试代码可以直接注释掉（万一最终debug还能用呢）
3. 头文件中包含了的头文件，源文件中可以不重复包含
4. 当一个函数要实现多个功能时，可以先用注释搭建好细节流程，再分部实现功能