# C++核心编程
## 内存四区
* **代码区**——共享 只读
* **全局区**
* **栈区**
  特别注意：不要随便返回和利用栈区的地址
  （有的编译器可能会对返回的栈区地址上的数据做一次保留，但实际上该地址在退出函数后，应该已经被清理）
* **堆区**
    由程序员分配和释放，若程序员不释放，程序结束时将由OS回收
    在C++中主要由new在堆区开辟内存
## new和delete
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

## 引用
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

## 函数提高
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

## 类和对象
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

## 文件操作
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

# C++提高编程
## 模板
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

## STL
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
对组，即成对出现的数据，利用对组可返回两个刷数据

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


