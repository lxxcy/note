# C++核心编程
## 目录
[TOC]

## [内存四区](#目录)

* **代码区**——共享 只读
* **全局区**
* **栈区**
  特别注意：不要随便返回和利用栈区的地址
  （有的编译器可能会对返回的栈区地址上的数据做一次保留，但实际上该地址在退出函数后，应该已经被清理）
* **堆区**
    由程序员分配和释放，若程序员不释放，程序结束时将由OS回收
    在C++中主要由new在堆区开辟内存
## [new和delete](#目录)
```c++
//new用于动态申请内存，并创建了一个对象
//new返回一个相应内存的指针
data-type *data=new data-type;  //此处data-type表示一个数据类型
data-type *data2=new data-type(val);//括号是可选内容，用于给新申请的内存赋值
data-type *data3=new data-type[10];//中括号表示分配一个数组，并返回数组的首地址

//如果自由存储区已被用完，可能无法成功分配内存。所以建议检查new运算符是否返回 NULL 指针

//delete后接一个指针，用于释放new申请的内存
delete data2;
```

## [引用](#目录)
作用：给变量起别名
语法：`数据类型 &别名 = 原名`
注意：
1. 引用必须要初始化(函数中的引用形参不需要初始化，初始化是在函数调用时完成的)
2. 引用初始化后，不能更改
```c++
int a=10;
int &b=a; //此时b即作为a的别名
          //若对b进行修改，实际上就是对a进行修改
//注意：
//    1.引用必须要初始化(函数中的引用形参不需要初始化，初始化是在函数调用时完成的)
//    2.引用初始化后，不能更改
int c=20;
b=c;//赋值操作，不是修改引用，引用不能修改
```
函数形参中利用引用参数可以实现和按地址传递一样的效果
```c++
void swap(int &a,int &b){ //利用引用作为形参，可实现对传入的原数据进行修改
  int temp=a;
  a=b;
  b=temp;
}
```
引用做函数的返回值
* 不要返回局部变量的引用
* 引用类型的返回值可以作为左值(即函数要做左值，则必须返回引用)
```c++
int &swap(){
  static int temp=10;//使用static是为了使temp成为静态变量而非局部变量
  return temp;
}

int main(void){
  swap()=1000;//实际作用是将temp修改为1000
}

```
C++引用的实质，就是**指针常量**
补：const在指针中的应用
```c++
int b;
const int *a=&b;  //const在数据类型前，表示"常量指针"，该指针指向的位置可以修改，但指向位置的值不可通过该指针修改
int * const c=&b;  //const在*后，表示"指针常量"，该指针指向的位置不可修改，但指向位置的值可以通过该指针修改
```
* 常量引用
```c++
//int &val=10;  //10是存放于常量区的数据，引用本身需要一个合法空间，故该行错误

const int &val=10;  //该行却能正确编译，因为加入const后，编译器将进行优化，
                    //相当于int temp=10;const int &val=temp;

void print(const int &a){   //形参中使用const关键字，可防止函数中对引用的值进行修改
  cout <<"a=" << a << endl;
}
```

## [函数提高](#目录)
### 函数默认参数
* C++允许函数形参列表中是有默认值的
* 注意事项：
  1. 如果某个位置的参数有默认值，则该参数后面的所有参数都必须有默认值
  2. 函数声明和函数定义(函数实现)中，只允许有一个出现参数默认值

```c++
int add(int a,int b,int c);

int add(int a,int b=20,int c=30){
  return a+b+c;
}
```

### 函数占位参数
* C++允许形参列表中有占位参数，用来占位，调用函数时，必须填补该位置
* 语法：返回值类型 函数名(数据类型)
```c++
int func(int a,int){
  ......
}

int func2(int a,int =10){ //占位参数也可以有默认参数
  ......
}
```
### 函数重载
作用：函数名可以相同，提高复用性

函数重载满足条件：
  1. 同一作用域下
  2. 函数名称相同
  3. 函数参数类型不同，或者个数不同，或者顺序不同


注意： 函数返回值不可作为函数重载的条件
```c++
void func(int a,int  b){
  cout << "func(int a,int b)" << endl;
}

void func(){
  cout << "func()" << endl;
}

void func(double a,int b){
  cout << "func(double a,int b)" << endl;
}
```
引用参数也可以作为重载条件，且对于const和非const的修饰的引用参数也能进行区分

避免函数重载碰到**函数默认参数**，可能在调用时产生歧义，导致编译器报错

## [类和对象](#目录)
C++面向对象三大特性：**封装**、**继承**、**多态**
C++认为万事万物皆为对象，对象上有其**属性**和**行为**
具有相同性质的**对象**，可抽象为**类**
### 封装
意义：
* 将属性和行为作为一个整体，表现生活中的事物
* 将属性和行为加以权限控制

语法：
`class 别名{访问权限: 属性; 行为;};  `
`//注意和结构体定义类似，最后有一个分号`

注意事项：
1. 可通过行为，给属性赋值
2. 类中的属性和行为统称**成员**
   属性=成员属性=成员变量
   行为=成员函数=成员方法

权限：
* `public:`
  公共权限，类内可访问，类外也可访问
* `protected:`
  保护权限，类内可访问，类外**不**可访问，可继承
* `private:`
  私有权限，类内可访问，类外**不**可访问，**不**可继承

class和struct的唯一区别——**默认访问权限不同**
* class 默认访问权限为**私有**
* struct默认访问权限为**公有**

成员属性设为私有的好处：
1. 将所有成员属性设为私有，可以自己控制读写权限
   Tips：通常会再设置权限为public的公共接口来让外界修改私有成员属性
2. 对于写权限，我们可以检测数据的有效性

Tips：
* 一个类可以包含另一个类
* 大型项目中常将类拆分为头文件.h和源文件.cpp
```c++
//point.h
#pragma once        //该行作用：
#include <iostream>
using namespace std;
//.h头文件中仅需要保留声明
class Point {
public:			//向外暴露的接口
	void setx(int x);	//设置点的x坐标
	void sety(int y);	//设置点的y坐标
	int getx();			//获取点的x坐标
	int gety();			//获取点的y坐标
private:		//内部属性
	int m_x;
	int m_y;
};




//circle.h
#pragma once
#include <iostream>
using namespace std;
#include "point.h"		//使用点类，来表示圆心坐标

class Circle {
public:
	int getR();						//获取半径
	Point getCenter();				//圆心坐标
	void setR(int R);				//设置半径
	void setCenter(Point Center);	//设置圆心坐标
private:
	int m_R;						//半径
	Point Center;					//圆心
};




//circle.cpp
#include "circle.h"

void Circle::setR(int R) {
	m_R = R;
}

void Circle::setCenter(Point point) {
	Center = point;
}

int Circle::getR() {
	return m_R;
}

Point Circle::getCenter(){
	return Center;
}




//point.cpp
#include "point.h"
//.cpp源文件中仅需要保留函数实现
void Point::setx(int x) { //注意，不可直接使用void Setx(int x)，否则编译器会报错，
                  //因为该函数说明是一个全局函数，而该函数本应是point中的成员函数，
                  //需要给它加上作用域point::
    m_x = x;
}
void Point::sety(int y) {
    m_y = y;
}
int Point::getx() {
    return m_x;
}
int Point::gety() {
    return m_y;
}




//main.cpp
//要求：判断点p与圆的关系
//注：点和圆的位置需要自己设定
#include <iostream>
using namespace std;
#include <string>
#include "circle.h"
#include "point.h"

void wherearepoint(Point &p1, Circle& C) {
	if ((p1.getx ()-C.getCenter ().getx())* (p1.getx() - C.getCenter().getx()) 
		+(p1.gety()-C.getCenter ().gety() )* (p1.gety() - C.getCenter().gety())
		<
		C.getR ()*C.getR ())
		cout << "点在圆内" << endl;
	else if ((p1.getx() - C.getCenter().getx()) * (p1.getx() - C.getCenter().getx())
		+ (p1.gety() - C.getCenter().gety()) * (p1.gety() - C.getCenter().gety())
		>
		C.getR() * C.getR())
		cout << "点在圆外" << endl;
	else
		cout << "点在圆上" << endl;
}	

int main(void) {
	
//对外只能操作类所暴露的接口
	Point p1;		//点坐标
	p1.setx(0);
	p1.sety(0);

	Point center1;	//圆心坐标
	center1.setx(10);
	center1.sety(0);

	Circle c1;
	c1.setR(10);	//圆半径
	c1.setCenter(center1);	//传入圆心

	wherearepoint(p1, c1);

	return 0;
}
```

### 构造函数和析构函数
C++要求实现对象的初始化和清理
故使用**构造函数**和**析构函数**解决初始化和清理工作
这两个函数会被编译器自动调用，若不手动提供这两个函数，将由编译器提供（编译器提供的是构造函数和析构函数是空实现）
* 构造函数：`类名(){}`
  1. 没有返回值，也不用写void
  2. 函数名称和类名相同
  3. 函数可以有参数，因此可发生重载
  4. 程序在**调用对象时**会自动调用构造函数，且仅会调用**一次**，无需手动调用

* 析构函数：`~类名(){}`
  1. 没有返回值，也不写void
  2. 函数名同类名，在名称前加~
  3. 不可以有参数，因此不能发生重载
  4. 程序在**对象销毁前**会自动调用析构函数，且仅会调用**一次**，无需手动调用

构造函数的分类：
* 按有无参数：有参构造，无参构造(即默认构造函数)
* 按类型：普通构造，拷贝构造

构造函数三种调用方式：
1. 括号法:
   `对象标识符 对象名(参数)`
   注意：调用默认构造函数，不要加()，否则将被编译器认为是函数声明
2. 显示法:
   `对象标识符 对象名=对象标识符(参数)`
   注意：
    1.不要尝试利用拷贝构造函数，去初始化匿名对象，如：
      `Person(p2);` 编译器会认为是在重定义p2
    2.对于拷贝构造函数，需要对传入类作为形参，必须使用**引用类型**(否则编译器将报错)，可以**加const**防止修改原对象
3. 隐式转换法:
   `对象标识符 对象名=参数`

Tips：
1. **匿名对象**，如`Person p=Person();`或者`Person p=Person(10);`，
   后面的部分为一个匿名对象，使用完毕后就会被清理
2. 注意分辨匿名对象、函数声明、默认构造函数调用（无参）
   `Person();`      是一个**匿名对象**，没有对象名，只是没有任何操作而已
   `Person p1();`   是一个**函数声明**
   `Person p1;`     **创建了p1对象**，并且也是**默认构造函数调用**
```c++
#include <iostream>
using namespace std;

class Person {
public:
    Person() {
        cout << "默认构造函数" << endl;
    }

    Person(int a) {
        age = a;
        cout << "有参构造函数" << endl;
    }

    Person(const Person &p) {   //注意：需要对传入的类加const防止修改，同时还需要使用引用类型
        age = p.age;
        cout << "拷贝构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
    }

private:
    int age;
};

int main(void) {
    //括号法
    Person p1;      //默认构造函数调用
    Person p2(10);  //有参构造函数调用
    Person p3(p2);  //拷贝构造函数调用
    //Tips：Person p1();  为错误语法，编译器会认为这是一个函数声明

    //显示法
    Person p4;
    Person p5 = Person(10); //有参构造，Person(10)实际是一个匿名对象，
                          //当前行执行结束后，系统会立即回收匿名对象
    Person p6 = Person(p5); //拷贝构造
    //Tips：不要尝试利用拷贝构造函数，去初始化匿名对象，如：
    //Person(p2); 编译器会认为是在重定义p2

    //隐式转换法
    Person p7 = 10; //有参构造
    Person p8 = p7; //拷贝构造

    return 0;
}
```
C++中拷贝构造函数使用的时机：
1. 使用一个已经创建完毕的对象来初始化一个新对象
2. 值传递的方式给函数参数传值
3. 以值方式返回局部对象
```c++
#include <iostream>
using namespace std;

class Person {
public:
    Person() {
        cout << "默认构造函数" << endl;
    }

    Person(int a) {
        age = a;
        cout << "有参构造函数" << endl;
    }

    Person(const Person& p) {
        age = p.age;
        cout << "拷贝构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
    }

private:
    int age;
};

void test01(const Person &p) {
    Person p1(p);           //使用已经创建好的类，利用拷贝构造函数初始化另一个类
}

void test02(Person p) {     //以值传递方式传入p，实际上是利用拷贝构造函数创建了一个副本
    
}

Person test03(void) {       //返回类时，实际上是利用拷贝构造函数创建了一个副本返回(原p1已经被清理)
    Person p1;
    return p1;
}

int main(void) {
    
    return 0;
}
```
构造函数调用规则：
* 默认情况下，C++编译器至少给一个类添加3个函数
  1. 默认构造函数(无参，函数体为空)
  2. 默认析构函数(无参，函数体为空)
  3. 默认拷贝构造函数，对属性值进行拷贝
* 构造函数调用规则：
  * 如果用户自定义**有参构造函数**，c++不再提供无参构造，但仍提供拷贝构造
  * 如果用户自定义**拷贝构造函数**，c++不再提供其他**构造函数**(有参、无参)

#### 浅拷贝vs深拷贝(面试经典问题)
* 浅拷贝：简单的赋值拷贝操作(编译器默认提供的拷贝构造函数也是浅拷贝)
* 深拷贝：在堆区申请空间，进行拷贝操作
  Tips：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题(如在析构函数中清理堆区申请的内存时会报错)

初始化列表：
c++提供初始化列表语法，用来初始化属性
语法：`构造函数():属性1(值1),属性2(值2),属性3(值3)`
Tips：
1. 注意冒号的位置
2. 可以利用参数来动态使用初始化列表赋值（这样做可以使函数体内部的代码用于实现其他操作）
```c++
class Person{
public:
    Person() :m_A(10),m_B(20),m_C(30) {     //默认构造函数中，直接使用初始化列表
        //其他操作
    }

    Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c) { //实现动态使用初始化列表
      //其他非初始化操作
    }

    int m_A;
    int m_B;
    int m_C;
};
```


类对象作为类成员：
c++类中的成员可以是另一个类的对象，此时称该成员为**对象成员**
若类B以对象A作为成员，则A为对象成员：
* 创建B对象时，先调用对象成员A的构造函数，再调用自身B的构造函数
* 退出时，析构顺序则与构造**相反**
```c++
class Phone {
public:
    Phone(string name) :p_name(name) {

    }
    string p_name;
};

class Person {
public:
    //注意，可以直接对对象成员的参数进行初始化，此操作就像
    //隐式调用的拷贝构造函数:Phone p=phonename;
    Person(string name, string phonename) :m_name(name), p(phonename)
    {

    }

    string m_name;
    Phone p;
};
```
### 静态成员
在成员变量或成员函数前加上关键字static，成为静态成员
* 静态成员变量
  * 所有对象共享一份数据(存储于全局区中的常量区)
  * 在编译阶段分配内存
  * 类内声明，类外初始化(初始化格式：`数据类型 类名::静态成员变量=初始化值;`)
* 静态成员函数
  * 所有对象共享同一个函数
  * 静态成员函数只能访问静态成员变量

注意：静态成员也有访问权限——私有权限下，类外不可访问，但由于静态成员变量需要类外初始化，故仍能类外初始化

访问静态成员的方法
* 通过**对象**访问
* 通过**类名**访问

```c++
#include <iostream>
using namespace std;

class Person {
public:
    static int m_age;//静态成员变量
    static void func(int p) {
        m_age = p;
        //num = p;  //该行会报错，静态成员函数不可使用非静态成员变量
    }

    int num;//成员变量
};

int Person::m_age = 10;


int main(void) {
    Person p1;
    cout << "通过对象访问p1的年龄为" << p1.m_age << endl;   //通过对象访问
    cout << "通过类名访问年龄为" << Person::m_age << endl;   //通过类名访问

    return 0;
}
```
### C++对象模型和this指针
#### 成员变量和成员成员函数分开存储
c++中类内的成员变量和成员函数**分开存储**
只有**非静态成员变量**才属于类的对象上
注意：空对象也会占用1B内存
```c++
#include <iostream>
using namespace std;

class Person0 { //空对象

};

class Person {
public:
    int m_A;    //非静态成员变量   属于类的对象上
    static int m_B; //静态成员变量    不属于类的对象上
    void func1() {};    //非静态成员函数   不属于类的对象上
    static void func2() {}; //静态成员函数    不属于类的对象上
};

int Person::m_B = 10;//静态成员变量需要在类外初始化

int main(void) {
    Person0 p0;
    //空对象也会占用一个内存
    //C++编译器会给每个空对象也分配1B空间，是为了区分空对象所占内存的位置，若对象不空，则该1B空间将不会分配
    //每个空对象也应有一个独一无二的内存地址
    cout << "空对象p0占用字节数为" << sizeof(p0) << endl;
    
    return 0;
}
```

#### this指针
由于c++中成员变量与成员函数分开存储
每一个非静态成员函数只会诞生一份实例，即多个同类型对象会共用同一块函数代码
因此，c++提供特殊的对象指针，即**this指针**，this指针指向**被调用的成员函数**所属的**对象**
* this指针是隐含于每一个非静态成员函数内的一种指针
* this指针不需要定义，直接使用即可

this指针的用途：
* 当形参和成员变量同名时，可用this指针来区分(解决命名冲突)
* 在类的非静态成员函数中**返回对象本身**，可使用`return *this;`（要注意按值返回和返回引用类型的区别）
```c++
#include <iostream>
using namespace std;

class Person {
public:
    void Addage1(int age) { 
        age = age;      //与成员变量同名的形参
    }

    int age;

    void Addage2(int age) {
        this->age = age;    //使用this指针标识age，表示指向被调用的对象的成员函数
    }
    
    Person Addage3(Person p) {
        age += p.age;
        return *this;//按值返回当前对象，返回的是其副本
    }

    Person &Addage4(Person p) {
        age += p.age;
        return *this;//以引用类型返回当前对象，返回的是其本身
    }

};

int main(void) {
    Person p1;
    p1.Addage1(10);
    cout << "调用Addage1后的age为" << p1.age << endl;
    //使用与成员变量名相同的形参，编译器在函数体内无法区分出成员变量，只能认为是形参

    p1.Addage2(10);
    cout << "调用Addage2后的age为" << p1.age << endl;

    Person p2;
    p2.age = 10;
    p2.Addage3(p1).Addage3(p1).Addage3(p1);
    cout << "按值返回后， p2的年龄为" << p2.age << endl;
    //由于每次返回的不是p2本身，只有第一次使p2的值加10，后面返回的为p2的多个副本，
    //故函数的操作是基于其不同副本的，而此处打印的为p2的age

    //链式编程思想
    p2.age = 10;
    p2.Addage4(p1).Addage4(p1).Addage4(p1);
    cout << "按引用返回后，p2的年龄为" << p2.age << endl;
    //引用类型返回的是其本身
    return 0;
}
```
#### 空指针访问成员函数
c++空指针也是可以调用**成员函数**的
但是需要注意有没有用到this指针
如果用到this指针，需要加以判断以保证代码的健壮性
```c++
#include <iostream>
using namespace std;

class Person {
public:
    void showname() {
        cout << "张三" << endl;
    }

    void showage() {
        cout << "年龄为" << m_age << endl;
        //实际上这里的 m_age 为 this->m_age ,用到了this指针
    }

    void showage2() {
        if (this == NULL)   //保证健壮性
            return;
        cout << "年龄为" << m_age << endl;
    }

    int m_age;
};

int main(void) {
    
    Person* p = NULL;
    p->showname();
    //p->showage();   //编译器未报错，是因为允许调用空指针的成员函数
                    //但运行出错，是因为传入的为空指针，并未分配内存以及初始化
    p->showage2();
    return 0;
}
```


#### const修饰成员函数
* 常函数：
  * 成员函数**后**加const，成为常函数:`类型 函数名() const {}`
  * 常函数内不可以修改成员属性

* 常对象：
  * **声明对象前**加const，成为常对象：`const 类名 对象名`
  * 常对象只能调用**常函数**(防止普通函数修改常对象内成员变量)
* mutable关键字
  某成员属性前加mutable关键字，则该成员属性无论在常对象还是常函数中，都可被修改
```c++
#include <iostream>
using namespace std;

class Person {
public:
    //this指针的本质是 指针常量 ，即该指针的指向不可改，但其指向的值可改
    //即 Person *const this;
    //在成员函数后加const，实际上是修饰的this指针的指向，让其指向的值也不可修改
    //即 const Person *const this;
    void func() const { //常函数
        m_B=10;
        //m_age=10;//常函数不可以修改成员属性
    }

    void func2() {      //普通函数

    }
    
    void func3() {
        m_age = 0;
    }

    int m_age;
    mutable int m_B;//特殊成员变量，加入关键字mutable后，能在常对象中被修改
};

int main(void) {
    const Person p; //注意实在声明对象时，使用const，使其变为常对象
    //p.m_age = 1;    //报错，常对象中不允许修改成员变量的值
    p.m_B = 1;      //允许修改常对象中 特殊的成员变量

    p.func();   //常对象中只允许调用常函数
    //p.func2();
    //p.func3();//不允许调用非常函数的原因是，普通函数可能修改常对象中的成员变量
    return 0;
}
```

### 友元
程序中，有些私有属性，也需要让类外的特殊的一些函数或者类进行访问，就需要用到友元技术
友元的目的：让一个函数或者类，访问另一个类中的私有成员
友元关键字：`friend`
友元的三种实现：
* 全局函数做友元
* 类做友元
* 成员函数做友元

#### 全局函数做友元
```c++
#include <iostream>
using namespace std;
#include <string>

class Building {
    friend void GoodGay(Building& building); //friend关键字修饰的全局函数应放在类中最上方

public:
    Building() {
        sittingroom = "客厅";
        bedroom = "卧室";
    }
    string sittingroom;
private:
    string bedroom; //私有成员
};


void GoodGay(Building &building) { //注意为了避免值传递，应传入指针或引用类型
    cout << "好基友正在访问您的" << building.sittingroom << endl;
    cout << "好基友正在访问您的" << building.bedroom << endl;
}

int main(void) {
    Building building;
    GoodGay(building);

    return 0;
}
```
#### 类做友元
Tips：可以在类外写类内的函数实现：
1. 先在类内保留声明
2. 类外的实现要加上该类的作用域(语法：`类型 类名::函数名() {}`)
```c++
#include <iostream>
using namespace std;
#include <string>

class Building {
    friend class GoodGay;   //确保可以通过该类，访问当前类的私有成员
public:
    Building();
    string sittingroom;
private:
    string bedroom; //私有成员
};

class GoodGay {
public:
    void visit();
    Building* building = new Building;
};

Building::Building() {      //要在类外写类中的函数，需要加上其作用域
    sittingroom = "客厅";
    bedroom = "卧室";
}

void GoodGay::visit() {
    cout << "好基友正在访问" << building->sittingroom  << endl;
    cout << "好基友正在访问" << building->bedroom << endl;     //要访问私有成员，需在对应类中使用friend关键字
}

void func() {
    GoodGay goodgay;
    goodgay.visit();
}

int main(void) {

    func();
    return 0;
}
```

#### 成员函数做友元
需要在使用friend修饰的成员函数名前加上该函数所在的作用域

Tips:
1. 注意各代码块结构的顺序要求：如果一个类A中，包含另一个类B，则B应该在A之前有**定义**或者**声明**(定义可以A在后面补)
2. 注意定义类时，只能写对成员的**属性(成员变量)** 和 **行为(成员函数)**，不可以写操作，操作应放在行为中
```c++
#include <iostream>
using namespace std;
#include <string>

class Building;//注意，此处为一个声明，因为GoodGay中要用到building

class GoodGay {
public:
    GoodGay();

    void visit1();  //让这个函数访问building中的私有成员
    void visit2();   //不让这个函数访问building中的私有成员
    Building* building; //特别注意***：该行不可直接用new返回的指针给building赋值
                        //目前思考原因为：类定义中只能包含成员属性，不能写操作
};

class Building {
    //使用作用域，告诉编译器，GoodGay下的visit1成员函数作为本类的好朋友
    friend void GoodGay::visit1();//为保证friend对GoodGay作用域有效，应使得building在GoodGay后面
public:
    Building();
    string m_sittingroom;
private:
    string m_bedroom;//私有成员
};

//类外定义成员函数
Building::Building() {
    m_sittingroom = "客厅";
    m_bedroom = "卧室";
}

GoodGay::GoodGay() {
    building = new Building;//通过默认构造函数给building赋值，
                            //再次提醒，类中不允许直接写操作，只能写成员，操作应放在成员函数中实现
}

void GoodGay::visit1() {
    cout << "好基友正在访问：" << building->m_sittingroom << endl;
    cout << "好基友正在访问：" << building->m_bedroom << endl;
}

void GoodGay::visit2() {
    cout << "陌生人正在访问：" << building->m_sittingroom << endl;
    //cout << "陌生人正在访问：" << building->m_bedroom << endl;    //不是该类好朋友的成员函数不可访问该类的私有成员
}

void func() {
    GoodGay gg;
    
    gg.visit1();
    gg.visit2();
}

int main(void) {
    func();
    
    return 0;
}
```

### 运算符重载
运算符重载：对已有的运算符重新定义，赋予其另一种功能，以适应不同的数据类型
#### 加号运算符重载
实现两个自定义数据类型相加

两种重载方式：
* 成员函数实现+号运算符重载
* 全局函数实现+号运算符重载

运算符可以和函数重载同时出现

注意：
1. 对于内置的基本数据类型的表达式的运算符，是不可能改变的
2. 不要滥用运算符重载(如重载+的函数实现中却用-等其他类运算符操作)

Tips：形参传入引用的另一个好处：避免副本产生，节省内存空间，若要防止修改原实参，可考虑加const进行传送
```c++
#include <iostream>
using namespace std;
#include <string>

class Person {
public:
    int m_A;
    int m_B;

    //通过成员函数实现+重载
    Person operator+(Person& p) { //注意类型为本类名Person，而非void
        Person temp;
        temp.m_A = p.m_A + this->m_A;
        temp.m_B = p.m_B + m_B;
        return temp;
    }
    /*实际上应该这样定义
    Person AddPerson(Person &p){
        Person temp;
        temp.m_A=m_A+p.m_A;
        temp.m_B=m_B+p.m_B;
        return temp;
    }
    为了标准化，使用关键字operator修饰运算符，让编译器将"operator运算符"作为函数名
    函数调用为：     p3=p1.AddPerson(p2);    变为     p3=p1.operator+(p2)；
    进一步简化表达式，编译器可直接识别：p3=p1+p2;     
    即实现对+号重定义，可以操作自定义数据类型
    */

};

//通过全局函数重载+号
Person operator+(Person& p1, Person& p2) {  //形参传入引用的另一个好处：避免副本产生，节省内存空间，
                                            //若要防止修改原实参，可考虑加const进行传送
    Person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}
/*实际上应该这样定义
Person PersonAddPerson(Person &p1,Person &p2){
    Person temp;
    temp.m_A=p1.m_A+p2.m_A;
    temp.m_B=p1.m_B+p2.m_B;
    return temp;
}
*/

//运算符重载 也可以发生函数重载
Person operator+(Person& p, int num) {
    Person temp;
    temp.m_A = p.m_A + num;
    temp.m_B = p.m_B + num;
    return temp;
}   //注：该函数放于类中，编译器提示运算符函数参数过多？原理不明

void func() {
    Person p1;
    p1.m_A = 10;
    p1.m_B = 10;
    Person p2;
    p2.m_A = 10;
    p2.m_B = 10;

    //成员函数重载本质调用：
    //Person p3=p1.operator+(p2);

    //全局函数重载本质调用：
    //Person p3=operator+(p1,p2);

    Person p3 = p1 + p2;
    cout << "p3的m_A为" << p3.m_A << endl;
    cout << "p3的m_B为" << p3.m_B << endl;

    Person p4 = p1 + 50;
    cout << "p4的m_A为" << p4.m_A << endl;
    cout << "p4的m_B为" << p4.m_B << endl;
}

int main(void) {
    func();
    
    return 0;
}
```
#### 左移运算符重载
作用：可以输出自定义数据类型

一般不使用成员函数进行左移运算符重载
Tips：
1. 如果不知道某函数的返回类型，可以先写void，后面再修改为正确的类型
2. 链式编程思想要求前面的操作返回相同的数据类型，以继续进行
3. 注意函数返回值类型，有时不能以值返回（如ostream类型，cout的类型），需要使用引用类型接取返回的cout，否则将报错（原理未明）
```c++
#include <iostream>
using namespace std;
#include <string>

class Person {
    friend ostream &operator<<(ostream& out, Person& p);
public:
    Person() {
        m_A = 10;
        m_B = 10;
    }

    //一般不会利用成员函数重载 左移运算符
    //利用成员函数重载左移运算符，调用为： p.operator<<(cout)  简化为 p << cout
    //并不符合原来的目的，因为cout应该在p左侧，这样才不会造成理解出错
    /*
    void operator<<(cout){

    }
    */
private:
    int m_A;
    int m_B;
};

//利用全局函数重载 左移运算符
ostream &operator<<(ostream& out, Person& p) {   //提醒：引用是起别名，故没必要一定要和原数据类似
    out << "p.m_A=" << p.m_A << " p.m_B=" << p.m_B;
    return out;
}   //***注意此处函数返回值是ostream类型，
    //应使用引用类型返回，否则将报错，原因不明？***

void func() {
    Person p;
    cout << p << endl;
    //cout << p << endl; //若运算符重载返回的是void将报错，因为cout的使用本就是利用 链式编程思想，
                         //返回void类型将导致链式编程无法进行
}

int main(void) {
    func();
    
    return 0;
}
```

#### 递增运算符重载
作用：实现对自定义数据类型的递增

前置++重载，需要返回引用类型
后置++重载，不能返回引用类型

Tips：
1. 不要在形参中滥用引用类型，可能导致传入的参数无法识别
2. 区分值传递和引用传递返回值，注意有时需要统一传入的形参和传入的数据的类型（引用类型形参，有时需要传入引用类型数据才不会报错，有时传入非引用类型数据也行），**原理目前还是不够清楚**
3. 不要返回局部变量的指针或引用
```c++
#include <iostream>
using namespace std;
#include <string>

class MyInteger {
    friend ostream& operator<<(ostream& cout, MyInteger integer);
public:
    MyInteger() {
        m_num = 0;
    }

    //重载前置++运算符
    MyInteger &operator++() {
        m_num++;
        return *this;//提醒：要返回当前调用对象，应使用在类中使用this指针
    }

    //重载后置++运算符
    //加入占位参数是为了区分前置++和后置++的重载函数实现
    //可以返回void，但不再支持链式编程，故此处返回一个类
    MyInteger operator++(int) {    //注意，若不加占位参数，此处将报错，因为是重定义
        //先记录当时结果
        MyInteger temp = *this;
        //再 ++
        m_num++;
        //最后再返回记录的结果
        return temp;
        //由于temp是局部变量，故后置++的重载不能以引用类型返回
        //造成的后果是，如果有链式编程调用后置++可能会出问题
    }
    
private:
    int m_num;
};

//全局函数重载<<运算符
ostream& operator<<(ostream &cout,MyInteger integer) {
    cout << integer.m_num;
    return cout;
}   //若MyInteger传入引用类型形参，编译器报错提示没有与<<匹配的运算符？
    //1.++重载引用类型返回      此处传入引用类型    不报错
    //2.++重载引用类型返回      此处传入非引用类型  不报错
    //3.++重载非引用类型返回    此处传入非引用类型  不报错
    //4.++重载非引用类型返回    此处传入引用类型    报错
    //考虑原因为引用实质为指针常量，即一个地址，还是要和原来的数据进行区分
    //重载<< 函数的第二个形参为引用类型，则需要传入引用类型的参数，是对象类型，则需要传入对象类型参数

void func() {
    MyInteger integer;
    cout << ++integer << endl;
    cout << integer << endl;
    cout << ++(++integer) << endl;
    cout << integer << endl;    //如果重载前置++运算符时，不采用引用类型返回，
                                //第一次使integer+1，但第二次将导致integer的副本+1,
                                //而不是integer再+1

    MyInteger integer2;
    cout << "后置++操作" << endl;
    cout << integer2++ << endl;
    cout << integer2 << endl;
    cout << (integer2++)++ << endl;
    cout << integer2 << endl;   //integer2不会加两次，因为有一次加到了副本上
}


int main(void) {
    func();
    
    return 0;
}
```

#### 递减运算符重载（自写）
```c++
#include <iostream>
using namespace std;
#include <string>

class MyInteger {
public:
    int m_num;

    MyInteger() {
        m_num = 3;
    }

    //重载前置--
    MyInteger &operator--() {
        --m_num;
        return *this;
    }

    //重载后置--
    MyInteger operator--(int) { //加入占位参数，以区分前面的前置--的重载
        MyInteger temp = *this;
        m_num--;
        return temp;
    }
};

//重载<<运算符
ostream& operator<<(ostream &cout,MyInteger integer) {
    cout << integer.m_num;
    return cout;
}

void func() {
    MyInteger integer;
    cout << --integer << endl;
    cout << integer << endl;
    cout << integer-- << endl;
    cout << integer << endl;
}

int main(void) {
    func();
    
    return 0;
}
```

#### 赋值运算符重载
c++编译器至少给一个类添加4个函数：
1. 默认构造函数（无参，函数体为空）
2. 默认析构函数（无参，函数体为空）
3. 默认拷贝构造函数，对属性值进行拷贝
4. 赋值运算符`operator=`，对属性值进行拷贝（使`类1=类2`能直接运行，但默认为**浅拷贝**）

如果类中有属性指向堆区，做赋值操作时，也会出现**浅拷贝深拷贝问题**

Tips：
* 形参传入引用类型还是非引用类型，有坑需要填，形参值传递也可能导致浅拷贝深拷贝问题出现
* 为保证代码健壮性，最好手动释放new申请的内存（但要考虑浅拷贝深拷贝问题）
* 写函数返回值时，需要考虑到链式编程的需求，也要考虑是需要值返回还是引用返回

```c++
#include <iostream>
using namespace std;
#include <string>

class Person {
public:
    Person(int num) {
        m_age = new int(num);
    }

    Person& operator=(Person &p){   //注意：此处若不传入引用类型，代码仍崩溃
                                    //考虑为值传递时建立一个副本p(浅拷贝)，在该函数执行完后
                                    //副本p消除，会将原来传入的p的m_age内存清理
                                    //当后面func()执行完，传入的p消除，
                                    //又将重复清理同一块堆区内存，而导致崩溃
        //如果被赋值的对象成员指针非空，则应释放其空间，再赋值(改变指向)
        if (m_age != NULL) {
            delete m_age;
            m_age = NULL;//不要忘了将该指针置空
        }
        //深拷贝
        m_age = new int(*p.m_age);

        return *this;   //使用返回值以保证链式编程，使用引用类型返回原被调对象
    }

    ~Person() { //写析构函数的目的是为了释放new申请的空间
        if (m_age != NULL) {
            delete m_age;
        }
    }

    int *m_age;
};

void func() {
    Person p1(10);
    Person p2(18);
    p2 = p1;
    
    cout << "p1的年龄为" << *p1.m_age << endl;
    cout << "p2的年龄为" << *p2.m_age << endl;
    //如果不写深拷贝的重载=，将触发断点，因为p1和p2在浅拷贝后
    //p1中存储的是p2的m_age的值，是一个堆区的地址
    //在函数执行完，消除对象，先由p2释放该地址的空间，再由p1重复释放堆区内存(导致出错)
    //解决方案：深拷贝
}

int main(void) {
    func();
    
    return 0;
}
```

#### 关系运算符重载
作用：让两个自定义类型对象进行对比操作
```c++
#include <iostream>
using namespace std;
#include <string>

class Person {
    friend bool operator!=(Person& p1, Person& p2);
public:
    Person(string name,int age) {
        this->name = name;
        this->age = age;
    };

    //通过成员函数重载 ==运算符
    bool operator==(Person& p) {
        if (this->age == p.age && this->name == p.name)
            return true;
        return false;
    }


private:
    string name;
    int age;
};

//通过全局函数重载 !=运算符(注意私有权限需要友元技术访问)
bool operator!=(Person& p1, Person& p2) {
    if (p1.name == p2.name && p1.age == p2.age)
        return false;
    return true;
}

void func() {
    Person p1("Tom", 18);
    Person p2("Jerry", 20);

    if (p1 == p2)
        cout << "p1和p2是相等的" << endl;
    else
        cout << "p1和p2是不相等的" << endl;

    if (p1 != p2)
        cout << "p1和p2是不相等的" << endl;
    else
        cout << "p1和p2是相等的" << endl;
}

int main(void) {
    func();
    
    return 0;
}
```

#### 函数调用运算符重载
函数调用运算符`()`也可以重载
由于重载后使用的方式非常像函数调用，因此称为**仿函数**
仿函数没有固定的写法，非常灵活
Tips:
1. 函数调用运算符重载只能在**类内**，即只能通过成员函数重载
```c++
#include <iostream>
using namespace std;
#include <string>

class print{
public:
    //通过仿函数实现打印
    void operator()(string ch) {
        cout << ch << endl;
    }
};

void print2(string ch) {
    cout << ch << endl;
}

//仿函数非常灵活，没有固定的写法
//实现加法
class Add {
public:
    int operator()(int num1, int num2) {
        return num1 + num2;
    }
};

void func() {
    print print1;
    print1("Tom");//由于使用起来非常类似函数调用，因此称为仿函数
    print2("Tom");
}

void func2() {
    Add add;
    cout << add(1, 2) << endl;
    cout << Add()(1, 2) << endl;//Add()是匿名对象，如果不想创建对象，可考虑使用匿名对象
    
}

int main(void) {
    func();
    func2();
    
    return 0;
}
```

### 继承
c++面向对象三大特性之一

定义类时，下级别的成员（子类），除了拥有上一级（父类）的共性，还有自己的特性，故设置继承技术

继承的好处：减少重复代码

* 子类=派生类
* 父类=基类

#### 继承基本语法
语法：`class 子类:继承方式 父类 {};`
继承方式一共有三种：
* 公共继承
* 保护继承
* 私有继承
![继承方式](./继承方式.jpg)
```c++
#include <iostream>
using namespace std;
#include <string>

class Base {
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};

class Son1 :public Base {
public:
    string name;
    //再次提醒，操作属于行为，应放在行为中，类中不允许直接使用操作
    void func1() {
        m_A = 10;   //公共权限成员
        m_B = 10;   //保护权限成员
        m_C = 10;   //父类私有成员不继承
    }
};

class Son2 :protected Base {
public:
    string name;
    void func1() {
        m_A = 10;   //保护权限成员
        m_B = 10;   //保护权限成员
        m_C = 10;   //父类私有成员不继承
    }
};

class Son3 :private Base {
public:
    string name;
};

class Grandson :public Son3 {
public:
    //下面都会报错，因为私有成员不会继承
    void func1() {
        m_A = 10;
        m_B = 10;
        m_C = 10;
    }
};

void func() {
    Son1 son1;
    Son2 son2;
    Son3 son3;

    son1.m_A = 10;  //父类的公共成员，到子类中也是公共成员
    son1.m_B = 10;  //报错，父类的保护成员，到子类中仍为保护成员
    son1.m_C = 10;  //报错，父类的私有成员，子类不可访问

    son2.m_A = 10;  //报错，父类的公共成员，到子类变成保护成员
    son2.m_B = 10;  //报错，父类的保护成员，到子类中仍为保护乘员
    son2.m_C = 10;  //报错，父类的私有成员，子类不可访问

    son3.m_A = 10;  //报错，父类的公共成员，到子类中变为私有成员
    son3.m_B = 10;  //报错，父类的保护成员，到子类中变为私有成员
    son3.m_C = 10;  //报错，父类的私有成员，子类不可访问
}

int main(void) {
    func();
    
    return 0;
}
```

#### 继承中的对象模型
问：从父类继承过来的成员，哪些是属于子类对象中？
* 父类中**非静态成员属性**都将继承到子类
* 私有成员只是被编译器隐藏了，所以访问不到，但还是会被继承下去
继承图解：
![](继承图解.jpg)

补：（不需要掌握）
* 利用开发人员命令提示工具查看对象模型
  1. 跳转盘符 ，如F:
  2. 跳转文件路径   cd 具体路径下
  3. 查看命名
  4. cl /d1 reportSingleClassLayout类名 文件名

#### 继承中的构造和析构顺序
子类继承父类后，当创建子类对象时，也会调用父类的构造函数

继承中，创建子类对象时：
* 先调用父类的构造函数，再调用子类的构造函数（先构造父类，再构造子类）
* 析构的顺序与构造相反

#### 继承同名成员处理方式
当子类和父类出现同名成员时
* 访问子类同名成员  直接访问即可
* 访问父类同名成员  需要加作用域

注意：如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类所有同名成员函数（无论有参无参），故直接访问不会触发函数重载，只会报错

```c++
#include <iostream>
using namespace std;
#include <string>

class Base {
public:
    string name = "父类";

    void func() {
        cout << "父类成员函数" << endl;
    }

    void func(int a) {
        cout << "父类有参成员函数" << endl;
    }
};

class Son :public Base{
public:
    string name = "子类";

    void func() {
        cout << "子类成员函数" << endl;
    }
};

void test() {
    Son son;

    //仅会给出子类的同名成员
    cout << son.name << endl;
    son.func();

    //要访问父类中同名成员，需要加作用域
    cout << son.Base::name << endl;
    son.Base::func();

    //如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类所有同名成员函数
    //son.func(100);    //报错
    son.Base::func(100);    //如果想访问父类中被隐藏的同名成员函数，需要加作用域
}

int main(void) {
    test();
    
    return 0;
}
```

#### 继承同名静态成员函数处理方式
静态成员和非静态成员同名，处理方式一致：
  * 访问子类同名成员    直接访问即可
  * 访问父类同名成员    需要加作用域

```c++
#include <iostream>
using namespace std;
#include <string>

class Base {
public:
    static int num;
    static void func() {
        cout << "Base的成员函数" << endl;
    }

    static void func(int a) {
        cout << "Base的成员函数(有参）" << endl;
    }
};
int Base::num = 10;

class Son :public Base{
public:
    static int num;

    static void func() {
        cout << "son的成员函数" << endl;
    };
};

int Son::num = 1;
void test() {
    Son s;

    //通过对象访问
    cout << "通过对象访问" << endl;
    cout << s.num << endl;
    s.func();

    cout << s.Base::num << endl;
    s.Base::func();

    //通过类名访问
    cout << "通过类名访问" << endl;
    cout << Son::num << endl;
    Son::func();

    cout << Son::Base::num << endl; //表示的是：通过Son类访问Base类下的num
    //其实也可以直接写为：Base::num;  但是与上面一行意义不同，上面是通过子类类名访问父类的成员
                                    //而此处为直接通过父类类名访问其成员
    Son::Base::func();
    
    Son::Base::func(100);
}

int main(void) {
    test();
    
    return 0;
}
```

#### 多继承语法
c++允许一个类继承**多个**类
语法：`class 类: 继承方式1 父类1 , 继承方式2 父类2...`

注意：多继承可能引发父类中有同名函数出现的情况（将造成歧义），此时需要加作用域以区分

**C++实际开发中不建议使用多继承**
```c++
#include <iostream>
using namespace std;
#include <string>

class Base1 {
public:
    int m_A;
};

class Base2 {
public:
    int m_A;
};

class Son :public Base1,public Base2{
public:
    int m_C;
};


void test() {
    Son s;

    //s.m_A = 10; //由于继承的父类都有m_A，不加作用域，将导致歧义
    s.m_C = 10;
    
    //访问多继承形式下的同名成员，需要加作用域
    s.Base1::m_A = 10;
    s.Base2::m_A = 20;
    cout << s.Base1::m_A << endl;  
    cout << s.Base2::m_A << endl;
}

int main(void) {
    test();
    
    return 0;
}
```
#### 菱形继承问题及其解决办法
**菱形继承**（又称**钻石继承**）：
* 两个派生类继承同一个基类
* 又有某个类同时继承着这两个派生类

菱形继承带来的问题：（假设A被B、C继承，B、C又被D继承）
1. 当D使用数据时，产生二义性（需要加作用域解决）
2. D继承了两份来自A的相同的数据，导致资源浪费

菱形继承问题的解决——**虚继承**
语法：继承前，加上关键字 virtual 变为虚继承：`virtual 继承方式 类名`
最大的那个类称 **虚基类**
注意：虚继承关键字virtual加在中间的子类B、C上即可
```c++
#include <iostream>
using namespace std;
#include <string>

class Animal {
public:
    int m_Age;
};

class Sheep :virtual public Animal{

};

class Camel:virtual public Animal {

};

class SheepCamel :public Sheep, public Camel {
    
};

class SheepCamel2 :public Sheep, public Camel {

};

void test() {
    SheepCamel s1;
    //s1.m_Age = 10;//菱形继承，两个父类有相同的数据，编译器不能识别，需要加作用域
    s1.Sheep::m_Age = 10;
    s1.Camel::m_Age = 20;
    //但是实际上，我们知道这份数据只需要有一份就行了，菱形继承导致数据有两份，导致资源浪费

    //利用虚继承，可解决菱形继承问题
    //继承前，加上关键字 virtual 变为虚继承
    //Animal类称 虚基类
    //虚继承底层实现：使用virtual关键字后，子类继承的实际上是一个指针vbptr(v-virtual b-base ptt-pointer)
    //该指针指向一个虚基类表vbtable，表中记录一个偏移量，
    //各指针所在位置加上其偏移量都将指向一个唯一的数据
    //注意：虚继承关键字virtual加在中间的子类上即可
    
    SheepCamel2 s2;
    s2.m_Age = 10;//由于数据唯一，故即使直接访问也不会产生二义性

}   

int main(void) {
    test();
    
    return 0;
}
```

### 多态
c++面向对象三大特性之一
多态分为两类：
* **静态多态**：函数重载 和 运算符重载 属于静态多态，复用函数名
* **动态多态**：派生类和虚函数实现运行时多态

静态多态和动态多态区别：
* 静态多态的函数地址**早绑定**——编译阶段确定函数地址
* 动态多态的函数地址**晚绑定**——运行阶段确定函数地址

多态满足条件：
* 有继承关系
* 子类**重写**父类的虚函数
  （重写：函数返回值、函数名、参数列表 完全一致）

多态使用条件：
* 父类**指针**或**引用**指向子类对象

注意：虚函数是在父类的
```c++
#include <iostream>
using namespace std;
#include <string>

//静态多态
class Animal {
public:
    void Speak() {
        cout << "动物在说话" << endl;
    }
};

class Cat :public Animal{
public:
    void Speak() {
        cout << "小猫在说话" << endl;
    }
};

//地址早绑定，在编译阶段就确定了函数的地址，而此处是要求传入父类的对象，用的父类函数
//所以即使 运行时 传入子类，使用的仍为父类的函数
//如果想让小猫说话（执行子类的重写成员函数），需要在运行阶段绑定，不能提前绑定函数地址
void doSpeak(Animal& animal) {
    animal.Speak();
}


//动态多态

//动态多态满足条件：
//1. 有继承关系
//2. 子类重写父类的虚函数

//动态多态的使用：父类的 指针 或 引用 ，指向子类对象
class Animal2 {
public:
    //虚函数，注意虚函数是在父类的，因为后面的函数中使用的是父类的函数，子类虚函数可写可不写
    virtual void Speak() {
        cout << "动物在说话" << endl;
    }
};

class Cat2:public Animal2 {
public:
    void Speak() {
        cout << "小猫在说话" << endl;
    }
};

void doSpeak2(Animal2& animal) {
    animal.Speak();
}


void test() {
    Cat cat;
    doSpeak(cat); //C++允许父类和子类之间进行自动类型转换，不需要做强制类型转换
                //故即使这里的形参指针或引用要求传入一个父类，但其指针或引用也可指向其子类
    Cat2 cat2;
    doSpeak2(cat2);
}   

int main(void) {
    test();
    
    return 0;
}
```

#### 多态底层原理
为什么子类要重写父类的虚函数：
当父类Animal中，写了一个虚函数后，其创建的对象不再是一个空对象
里面包含了一个**虚函数指针vfptr**(v-virtual f-function ptr-pointer)
该指针指向一个**虚函数表vftable**，表内存放该类的**虚函数地址**&Animal::Speak

当发生继承后，子类对象cat中也继承了一个虚函数指针vfptr，该指针指向子类对象的虚函数表vftable，而该vftable是默认继承的父类Animal的虚函数地址
* 若子类中不发生重写，则当doSpeak2传入子类对象cat时，仍将调用父类的虚函数
* 若子类发生重写，则子类重写的函数地址(&Cat::Speak)将**覆盖**其虚函数表中存储的内容（即父类的虚函数地址），则当doSpeak2传入子类cat时，通过子类vfptr找到的vftable，再通过该表找到的函数，是子类重写的函数，故会调动子类的函数

#### 多态案例1——计算器制作
多态优点
* 代码结构清晰
* 可读性强
* 利于前期和后期的扩展与维护
  
**c++提倡多态设计程序架构，因为多态的优点很多**

Tips：
1. 真实开发中，提倡 开闭原则
2. **开闭原则**：对扩展进行开放，对修改进行关闭

```C++
#include <iostream>
using namespace std;
#include <string>

//普通方式实现计算器功能
class Calculator {
public:
    int GetResult(string oper) {
        if (oper == "+")
            return m_num1 + m_num2;
        else if (oper == "-")
            return m_num1 - m_num2;
        else if (oper == "*")
            return m_num1 * m_num2;
        //普通实现带来的问题：如果想拓展新的功能，需要修改源码
        //在真实开发中 提倡 开闭原则：对扩展进行开放，对修改进行关闭
    }

    int m_num1;//操作数1
    int m_num2;//操作数2
};

void test01() {
    //创建计算器对象
    Calculator a;
    a.m_num1 = 10;
    a.m_num2 = 10;
    cout << a.m_num1 << "+" << a.m_num2 << "=" << a.GetResult("+" ) << endl;
    cout << a.m_num1 << "-" << a.m_num2 << "=" << a.GetResult("-") << endl;
    cout << a.m_num1 << "*" << a.m_num2 << "=" << a.GetResult("*") << endl;
}   


//利用多态技术实现计算器
class AbstractCalculator {
public:
    int m_num1;
    int m_num2;

    virtual int GetResult() {   //虚函数
        return 0;
    }
};

class Add:public AbstractCalculator {
public:
    int GetResult() {
        return m_num1 + m_num2;
    }
};

class Sub :public AbstractCalculator {
public:
    int GetResult() {
        return m_num1 - m_num2;
    }
};

class Muti :public AbstractCalculator {
public:
    int GetResult() {
        return m_num1 * m_num2;
    }
};

void test02() {
    //多态使用条件：父类 指针 或 引用 指向子类对象
    //加法运算
    AbstractCalculator* ptr = new Add;
    ptr->m_num1 = 10;
    ptr->m_num2 = 10;
    cout << ptr->m_num1 << "+" << ptr->m_num2 << "=" << ptr->GetResult() << endl;
    //用完后记得销毁堆区内存
    delete ptr;

    //减法运算：
    ptr = new Sub;
    ptr->m_num1 = 10;
    ptr->m_num2 = 10;
    cout << ptr->m_num1 << "-" << ptr->m_num2 << "=" <<ptr->GetResult ()<< endl;
    delete ptr;
    //使用多态技术，虽然代码量变多了，但是更有利于维护和拓展，框架性结构很方便阅读以寻找问题
}
int main(void) {
    cout << "普通实现方式：" << endl;
    test01();
    cout << "通过多态实现：" << endl;
    test02();
    return 0;
}
```

#### 纯虚函数和抽象类
在多态中，父类的虚函数往往是没有意义的，主要是调用子类重写的内容
因此可以将虚函数改为**纯虚函数**
纯虚函数语法：`virtual 函数返回类型 函数名(参数列表)=0;`
当类中有了纯虚函数，这个类也称**抽象类**

抽象类特点：
* 无法实例化对象
* 子类必须重写抽象类的纯虚函数，否则也属于抽象类
```c++
#include <iostream>
using namespace std;
#include <string>

class Base {
public:
    virtual void test() = 0;
};

class Son1:public Base {

};

class Son2 :public Base {
public:
    void test() {
        cout << "son2的函数调用" << endl;
    }
};

void func() {
    //Base a; //抽象类不允许实例化对象
    //Son1 b; //Son1没有重写父类的纯虚函数，也是抽象类
    //new Base;//抽象类不允许实例化对象
    Son2 c;
    c.test();
}

int main(void) {
    func();

    return 0;
}
```

#### 多态案例2——制作饮品
```c++
#include<iostream>
using namespace std;

class AbstractDrinking {
public:
	virtual void Boil() = 0;
	virtual void Brew() = 0;
	virtual void Pour() = 0;
	virtual void Addsth() = 0;

	void MakeDrink() {
		Boil();
		Brew();
		Pour();
		Addsth();
	}
};

class Tea:public AbstractDrinking {
	void Boil() {
		cout << "烧水" << endl;
	}
	void Brew() {
		cout << "放入茶叶" << endl;
	}
	void Pour() {
		cout << "倒入杯中" << endl;
	}
	void Addsth(){
		cout << "加糖和牛奶" << endl;
	}
};

class Coffee :public AbstractDrinking {
	void Boil() {
		cout << "烧水" << endl;
	}
	void Brew() {
		cout << "放咖啡" << endl;
	}
	void Pour() {
		cout << "倒入杯中" << endl;
	}
	void Addsth() {
		cout << "加点枸杞" << endl;
	}
};

void Make(AbstractDrinking* item) { //接受new出来的子类指针
	item->MakeDrink();
	delete item;    //使用完后释放堆区内存
}

void func() {
	Make(new Tea);

	Make(new Coffee);
}

int main(void) {
	func();

	return 0;
}
```

#### 虚析构和纯虚析构
多态使用时，如果子类有属性开辟到堆区，则父类指针在释放时无法调用到子类的析构代码，从而造成堆区内存未释放，导致内存泄露

解决方式：将父类的析构函数改为**虚析构**或者**纯虚析构**
* 虚析构：
  `virtual ~类名(){}`
* 纯虚析构：
  `virtual ~类名(){}=0`
  `类名::~类名(){}`

虚析构和纯虚析构特性：
* 可解决父类指针释放子类对象
* 都需要有具体的函数实现
  （为了清理父类的堆区数据，纯虚析构函数实现写在类外，需要加作用域）

虚析构与纯虚析构的区别：
* 如果有纯虚析构，该类属于抽象类，无法实例化对象

注意：
1. 虚析构或纯虚析构是用来解决通过父类指针释放子类对象
2. 如果子类没有堆区数据，可以 不写虚析构或纯虚析构
3. 拥有纯虚析构函数的类也属于抽象类

```c++
#include <iostream>
using namespace std;
#include <string>

class Animal {
public:
    Animal() {
        cout << "Base的构造函数调用" << endl;
    }
    
    virtual ~Animal() { //虚析构
        cout << "Base的析构函数调用" << endl;
    }
    /*//纯虚析构，需要在类外写函数实现，为了清理父类的堆区数据
    virtual ~Animal()=0;
    */

    virtual void Speak() = 0;
};

/*//纯虚析构函数实现
Animal::~Animal(){
    cout<<"Animal的纯虚析构函数调用"<<endl;
}
*/
class Cat :public Animal {
public:
    Cat() {
        cout << "Son的构造函数调用" << endl;
        name = new string("Tom");
    }

    ~Cat() {
        cout << "Son的析构函数调用" << endl;
        if (name != NULL)   //析构函数清理堆区数据
            delete name;    
    }

    void Speak() {
        cout << "小猫" << *name << "在说话" << endl;
    }

    string* name;
};

void test0() {
    Animal* base = new Cat;
    base->Speak();
    delete base;    //清理申请的子类指针，将导致子类被清理，从而调用析构函数
                   /*但是若父类析构函数不为虚析构或者纯虚析构，结果如下：
                            Base的构造函数调用
                            Son的构造函数调用
                            小猫Tom在说话
                            Base的析构函数调用
                     即通过父类指针清理子类后，子类的析构函数并未被调用，其堆区数据未被释放
                     
                     父类析构函数加上virtual关键字后则出现子类析构调用，
                     其堆区已被释放
                            Base的构造函数调用
                            Son的构造函数调用
                            小猫Tom在说话
                            Son的析构函数调用
                            Base的析构函数调用
                     */
}

int main(void) {
    test0();

    return 0;
}
```

#### 多态案例3——电脑组装
```c++
#include<iostream>
using namespace std;
#include<string>

class CPU {
public:
	virtual void calculate() = 0;
};

class GPU {
public:
	virtual void display() = 0;
};

class Memory {
public:
	virtual void store() = 0;
};

class Intelcpu :public CPU {
public:
	void calculate() {
		cout << "Intelcpu开始计算了！" << endl;
	}
};

class Intelgpu :public GPU {
public:
	void display() {
		cout << "Intelgpu开始显示了！" << endl;
	}
};

class Intelmemory :public Memory {
public:
	void store() {
		cout << "Inetlmemory开始存储了！" << endl;
	}
};


class Lenovocpu :public CPU {
public:
	void calculate() {
		cout << "Lenovocpu开始计算了！" << endl;
	}
};

class Lenovogpu :public GPU {
public:
	void display() {
		cout << "Lenovogpu开始显示了！" << endl;
	}
};

class Lenovomemory:public Memory {
public:
	void store() {
		cout << "Lenovomemory开始存储了" << endl;
	}
};

class Computer {
public:
	Computer(CPU* cpu, GPU* gpu, Memory* memory) {
		this->cpu = cpu;
		this->gpu = gpu;
		this->memory = memory;
	}

	void Work() {
		cpu->calculate();
		gpu->display();
		memory->store();
	}

	~Computer() {
		if (cpu != NULL)
			delete cpu;
		if (gpu != NULL)
			delete gpu;
		if (memory != NULL)
			delete memory;
	}


	CPU* cpu;
	GPU* gpu;
	Memory* memory;

};

void test() {
	//Intelcpu intelcpu;//由于该方式不是申请的堆区内存，不应这样使用
	//Intelgpu intelgpu;
	//Intelmemory intelmemory;

	//Computer computer1(&intelcpu, &intelgpu, &intelmemory);
	//computer1.Work();

	cout << "第一台电脑开始工作了！" << endl;
	CPU* intelcpu = new Intelcpu;
	GPU* intelgpu = new Intelgpu;
	Memory* intelmem = new Intelmemory;
	Computer computer1(intelcpu, intelgpu, intelmem);
	computer1.Work();
	//此处暴露一个问题，申请的内存未清理干净
	//故考虑在computer的虚构函数中实现清理

	cout << "------------------------" << endl;
	cout << "第二台电脑开始工作了！" << endl;
	Computer computer2(new Lenovocpu, new Lenovogpu, new Lenovomemory);
	computer2.Work();

	cout << "------------------------" << endl;
	cout << "第三台电脑开始工作了！" << endl;
	Computer computer3(new Intelcpu, new Lenovogpu, new Lenovomemory);
	computer3.Work();
}

int main(void) {
	test();

	return 0;
}
```

## [文件操作](#目录)
程序运行时，产生的数据都属于**临时数据**，程序一旦运行结束，就会被释放
通过文件可以将数据**持久化**
C++中对文件操作，需要包含头文件`<fstream>`

文件类型分为两种：
1. 文本文件：以ASCII码形式存储
2. 二进制文件：以二进制形式存储

操作文件的三类头文件：
1. `ofstream`   写操作
2. `ifstream`   读操作
3. `fstream`    读写操作（一般使用这个）

### 文本文件
#### 写文件
写文件步骤：
1. 包含头文件： `#include <fstream>`
2. 创建流对象： `ofstream ofs;`
3. 打开文件：   `ofs.open("文件路径",打开方式);`
4. 写入数据：     `ofs<<"写入的数据";`
5. 关闭文件     `ofs.close();`

文件打开方式：
|打开方式|解释|
|:---|:---:|
|ios::in|为**读文件**而打开文件|
|ios::out|为**写文件**而打开文件|
|ios::ate|初始位置：文件尾|
|ios::app|追加方式写文件|
|ios::trunc|如果文件存在，先删除，再创建|
|ios::binary|二进制方式|

注意：文件打开方式可以配合使用，利用`|`操作符
如：用二进制方式写文件：`ios::binary | ios::out`

```c++
#include <iostream>
#include <fstream>
using namespace std;

void test() {
	//第一步：包含头文件

	//第二步：创建流对象
	ofstream test;
	//第三步：打开文件
	test.open("test.txt", ios::out);
	//第四步：写入数据
	test << "姓名：张三" << endl;   //endl也能在文件中输出换行符
	test << "性别：男" << endl;
	test << "年龄：18" << endl;
	//第五步：关闭文件
	test.close();
}

int main() {
	test();

    return 0;
}
```

Tips：
1. 文件操作必须包含头文件`<fstream>`
2. 读文件可使用ofstream，或者fstream类
3. 打开文件时，需要指定操作文件的路径、打开方式
4. 利用`<<`可向文件中写数据
5. 操作完毕，要关闭文件

#### 读文件
读文件步骤：
1. 包含头文件：`#include <fstream>`
2. 创建流对象：`ifstream ifs;`
3. 打开文件，并判断是否打开成功：
   `ifs.open("文件路径",打开方式);`
4. 读数据：四种方式
5. 关闭文件：`ifs.close();`

```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void test() {
	//第一步：包含头文件

	//第二步：创建流对象
	ifstream ifs;
	//第三步：打开文件，并做判断
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()){
		cout << "文件打开失败" << endl;
		return;
	}
	//第四步：读取文件
		//方法一
	char buf[1024] = { 0 };
	while (ifs >> buf) {		//注意这里不是用test文件输入到buf，而是用流对象
		cout << buf << endl;
	}
		//方法二
	char buf2[1024] = { 0 };
	while (ifs.getline(buf2, sizeof(buf2)))	//成员函数getline(数据存放地址,读取字节数)
		cout << buf2 << endl;

		//方法三
	string buf3;
	while (getline(ifs, buf3))	//全局函数getline(流对象，数据存放地址)
		cout << buf3 << endl;

		//方法四	不推荐使用该方法，因为效率低
	char c;
	while ((c = ifs.get()) != EOF)	//EOF:end of file文件末尾
		cout << c;		//由于单个输出字符，故不加endl换行

	//第五步：关闭文件
	ifs.close();
}

int main() {
	test();

	return 0;
}
```

### 二进制文件
以二进制方式对文件进行读写操作
打开文件要指定为`ios::binary`
#### 写文件
二进制方式写文件主要利用流对象调用成员函数write
write函数原型：`ostream &write(const char * buffer,int len);`
参数解释：字符指针buffer指向内存中的一段存储空间，len为读写的字节数

Tips:
1. 进行文件读写操作时，尽量避免使用c++的string类，可能会造成一些问题
```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//C++二进制写入文件功能很强大，不仅仅限于基础数据类型，类也能写入
class Person {
public:
	char m_name[64];	//注意：在写入字符串时最好不要用c++的string，可能会出现一些问题
	int m_age;
};

void test() {
	//第一步：包含头文件

	//第二步：创建输出流
	ofstream ofs;
        //注：ofs对象有构造函数，可实现创建时就打开文件
    //ofstream ofs("test2.txt,ios::binary|ios::out)

	//第三步：打开文件（写文件可以不用判断）
	ofs.open("test2.txt",ios::binary|ios::out);
	
	//第四步：写入文件
	Person p = { "张三",18 };
	ofs.write((const char*)&p, sizeof(p));  
            //注意，此处要求传入char类型指针的参数，故采用强制类型转换
	//第五步：关闭文件
	ofs.close();
}

int main() {
	test();

	return 0;
}
```

#### 读文件
二进制方式读文件主要利用流对象调用**成员函数read**
函数原型：`istream &read(char *buffer,int len);`
参数解释：字符指针buffer指向内存中的一段存储空间，len为读写的字节数

注意：读、写二进制文件，对类来说，要求进行读的类成员和进行写时的类成员的**顺序一致**，否则将是乱码

```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {		//注意，该Person类的声明要和写入时的声明完全一致，
					//成员顺序也不能变，否则读出会读出乱码
public:
	char name[64];
	int m_age;
};

void test() {
	Person p;
	//第一步：包含头文件

	//第二步：创建流对象
	ifstream isf;
	//第三步：打开文件，判断是否打开
	isf.open("test2.txt", ios::binary | ios::in);
	if (!isf.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	//第四步：读取文件
	isf.read((char *)&p, sizeof(Person));
	//第五步：关闭文件
	isf.close();
	cout << p.name << " " << p.m_age << endl;
}	

int main() {
	test();

	return 0;
}
```

### 多态应用——职工管理系统
Tips总结：
1. 头文件和源文件分开写，
   * 在头文件中写函数声明，并注释函数功能
   * 在源文件中写函数定义
   * 先在头文件构思要实现的功能，写好函数声明，再转到源文件通过实现函数来实现功能
2. 利用多态技术，用父类（甚至父类指针）去管理子类（或子类指针）以实现统一管理不同种类的数据
3. 将**数据定义**和**功能实现**分文件写，更方便阅读
4. 功能内的小功能，也可以适当封装，留下接口即可
5. 通过问题定位到接口，再从接口定位到封装的实现，一步一步寻找bug
6. 特别注意清理堆区内存，可以在析构函数中实现，但如果其他地方也有清理内存的操作，要注意防止二次清理