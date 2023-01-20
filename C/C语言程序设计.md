# C基础语法
## 集成开发环境搭建问题
### VS studio
> 解决方案与项目的关系
一个解决方案可有多个项目，但启动解决方案的时候，仅能启动其中的一个项目，对应项目名字是加粗的（一个项目相当于是一个入口，可编译出一个.exe文件）

> 项目中的源文件可包含多个.c文件，编译时可同时合成一个可执行文件

## 数据类型
### 进制变换
> 观察内存使用*十六进制*

> x86架构采用*小端存储*，低位低地址在前（左边），高位地址在后

> 为什么内存数据要用十六进制去看：只使用2个字符就能表示一个字节，非常高效

> 地址开头：

* 0x开头，表示十六进制
* 0开头，表示八进制
> printf输出

* %d表示以十进制去输出某一个整型数
* %f表示以浮点形式输出
* 
### 整型
> 举例

    int n=3;
    printf("输出整型变量n= %d\n",n);

> 一个整型变量一般占用4B

### 浮点型
> 举例


    float n=1.2;
    float m=1.4e-4;
    printf("输出浮点型变量n= %d\n",n);

> 两种表示法

* 小数形式
* 指数形式（要求e（或者E）前必须有数字，且e后面的指数必须为*整数*

> 大小：浮点型变量占用4B

### 字符型
> 举例

    char n='r';
    printf("字符型变量n是 %s\n",n);

> 字符型常量必须用''括起来，且只能包含一个字符

>ASCII表，实际上是以数字来代表字符

> 大小：1B

### 转义字符
> 以"\"开头的特殊字符称转义字符

> \n表示换行，\\表示反斜杠，\b表示退格

> 转义字符也需要用""或者''括起来使用

### 字符串
> 使用""括起来的一串字符
> 注意：
* 字符串中一个字符占**1个字节**
* 整个字符串最后实际以\0（不可见）结尾，故字符串实际大小为**字符数+1**
* " "不是空串，是空格字符串

### 混合运算与强制类型转换
> 混合运算
* 概念：如果使用混合类型，C将采用一套规则进行**自动**类型转换
* 类型级别（高-->低）：long double>double>float>unsigned long long>long long>unsignd long>long>unsigned int>int
* 转换规则：
    1. 类型升级：类型转换出现在表达式时，从较小的类型转换为较大类型
    2. 涉及两种类型的运算，两个值会被分别转换成两种类型的更高级别
    3. 赋值表达式语句中，**计算的最终结果**会被转换成被赋值变量的类型，该过程可能导致类型升级或降级
    4. 作为函数参数传递时，char与short将被转换为int，float被转换成double
> 强制类型转换

在某个量的前面放置圆括号括起来的类型名

* 举例
```c
    int i=5;
    float j;
    j=(float)i/2;\\如果不进行强制类型转换，将导致输出j=2.0000000
```

### 数据输入和输出
scanf和printf函数生命在<stdio.h>中
* scanf读取的是标准输入
* printf输出的是标准输出

> scanf()

* 参数解释
* 返回值：返回**成功赋值的变量数量**，发生错误时返回**EOF**
  * scanf发生错误原因：如连续输入三次ctrl+Z回车结束循环输入
  * EOF在c中定义为-1
* 注意：可变参数前需要加**取址运算符&**
* 运行原理：
  * scanf在读取非%c类型的数据时，会跳过并忽略连续输入中的**空格" "**和**换行符\n**；相反，在读取%c控制字符的数据时，连空格也不会忽略，故scanf读取字符型会比较麻烦（连续读取时，最好**在%c前加入空格**，表示忽略两个控制字符所对应的数据之间的所有空格）
  * 读取缓冲区的数据时，对于不匹配的类型，scanf会把该数据放回
  * scanf读取缓冲区的数据后，会在缓冲区留下一个换行符\n，如果有继续输入要求，需要对未拿出的换行符处理
  * 对于各个参数如%d%d之间，可以加空格，scanf将忽略空格进行读取
* 清空缓冲区操作（仅适用于VS）
  * 对于VS2012：使用fflush(stdin)
  * 对于VS2013-2019：使用rewind(stdin)
* 警惕scanf()未读取的字符，特别是换行符

```c
//输入一个整型数，然后申请对应大小空间内存，
//然后读取一个字符串，字符串的输入长度小于最初输入的整型数的大小，
//最后输出输入的字符串（无需考虑字符串过长、超过内存大小等问题）
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	int max; 
	char *buf=(char *)malloc(100);
	scanf("%d", &max);	//错误点：读取数字后直接结束进程，考虑输错原因为：
						//scanf把未读取的换行符留在缓冲区
	char c;
	scanf("%c",&c);//清理换行符
	char *s = (char *)malloc(max);
	gets(buf);
	if (strlen(buf) < max)
	{
		strcpy(s, buf);
		puts(s);
	}
	/*//使用getchar函数实现
	char c;int i=0;
	while((c=getchar()) != '\n' && i<max-1)
	{
		s[i]=c;
		i++;
	}
	*/

	//清理单个换行符
	/*getchar();*/

	//清理scanf未读取的剩下的字符（包括换行符）
	/*
	char ch;
	while ((ch=getchar())!=EOF && ch!='\n')	//赋值运算符优先级低于逻辑运算符，逻辑运算符结合方向为从左到右
		;*/

	
	return 0;
}
```
> printf()

* 参数解释：
* 返回值
* 运行原理：
  * 打印格式化字符串
  * 注意**控制输出格式**


## 运算符（注意优先级问题）
### 算数运算符

### 关系运算符
* Tips：
  * C将一切**非零值**视为真，**0**视为假
  * 优先级问题
  * 多个表达式结合（如3<a<10)，并非现实理解意义，需要使用逻辑运算符来表达原目的

### 逻辑运算符
* Tips：
  * 判断两个**浮点数**是否相等（浮点数的存储？IEEE754？）：用减法去对比精度，如对于f与234.56比较，需要使用：
  ```C
  if (f-234.56>-0.0001&& f-234.56<0.0001)
  {
    printf("f is equal to 234.56\n");
  }
  else{
    printf("f is not equal to 234.56\n");
  }
  ```
  * 优先级问题：逻辑运算符优先级小于关系运算符

### 赋值运算符
* Tips：
  * 左操作数与右操作数：左操作数必须为左值（变量）

### 条件运算符
### 逗号运算符
* 运算顺序：左->右
* 整体表达式的值为**最后一个表达式的值**

### 自增、自减运算符
* ++ --
* 特别注意：a++与++a不一样！
  * a++表示先使用a，再a+1
  * ++a表示先a+1，再使用a
* Tips：
  * 该运算符不能用于常量
  * 该类运算符优先级特别**高**，一般仅小于括号

### sizeof运算符
* 声明
```c
typedef unsigned int size_t;
sizeof (data type);			//该运算符以字节为单位，返回变量i所占用的空间
							//返回类型为size_t，实质为无符号整型
```
* 使用：
```c
  int a;
  int i=10;
  struct LNode{
	int data;
	LNode *next;
  }LNode;
  LNode *p;
  a=sizeof(i);  					//返回变量i所占用的大小
  a=sizeof(int);					//返回当前机器int类型所占用的大小
  p=(LNode *)malloc(sizeof(LNode));	//为指向一个LNode结构的指针p分配相应大小内存
```
## 选择
### if选择语句
* 语法格式：
```c
  if(i){             //i可为关系表达式、逻辑表达式，甚至是一个值
    printf("k");     //条件为真，执行该语句
  }
  else{              //可以没有else，有else时，条件为假，执行该语句
    printf("K");
  }
  
```

* if语句可与else语句多个同时使用（多分支语句）
  * 此时if可不断地进行else if，最后才可以是else
  * **语句只有一个会得到执行**，一旦一个语句执行，**后面的else if**都将不再执行

* if语句还可以嵌套，注意与多分支语句区别

* Tips:
  * 算符运算符优先级高于关系运算符，关系运算符优先级高于&&和||
  * 注意分隔符;的问题，if语句后面不能直接接;，否则后面的语句与该if语句无关
  * 建议if后面接大括号{}
  * else配队问题：else选择**最靠近它**的不完整的if语句配队
  * else不能单独出现，if可以 

## 循环
### while循环
* 语法格式：

```c
  \\求1加到100
  int i=1;
  int total=0;
  while(i<=100)     //当i当前值为100时，需要再执行一次循环，之后i为101，此时不应再执行循环，故i<=100
  {
    total=total+i;
    i++;
  }

  printf("total=%d",total);
```

* 清除缓冲区操作
```c
  while((ch=getchar())!=EOF && ch!='\n');
```
* Tips:
  * 注意while后不能直接接;
  * 条件合理判断，防止死循环
  * 出现死循环的常见两种情况：
    1. while语句后加了分号
    2. while循环体内没有让表达式趋近于假的操作
  * 警告：不要漏掉初始化和改变循环条件（迭代）的语句，特别是在嵌套循环中

### for循环
* 语法格式：
```c
  //求1加到100
  int i,total;
  for(i=1,total=0;i<=100;i++)       //括号后不能直接加分号，括号内有两个分号，不论语句是否存在，第一个表达式为初始化操作，第二个为判断条件，第三个为执行循环体后进行的操作（一般是使循环条件发生改变的操作）
  {
    total=total+i;
  }
  printf("total=%d",total);
```

* Tips：
  * for循环中自带初始化语句和迭代语句，用于嵌套循环时，子循环每次循环都会对变量初始化值，故很轻松实现嵌套循环，而使用while或者do while则需要自己在**每个子循环体末尾或者开头添加自己的初始化条件和迭代语句**
  * for循环很适用于嵌套循环

* while循环与do while循环需要在循环体中加入**改变循环条件的语句**，而**计数器初始化语句**需要在循环外添加，很容易被遗漏

```c
//某人想要将手中100元面值的钞票换成10/5/2/1元面值的钞票，
//要求正好换40张，且每种钞票至少一张，问有几种换法
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TOTAL 40
int main(void)
{
	//分析：最少面值为18
	int ten = 1;//最多5张
	int five = 1;//最多11张
	int two = 1;
	int one = 1;
	
	int i = 0;//代表正确的换法
	int total = 0;

	//利用最后剩余值判断(失败：结果0），
	while (ten <= 5)
	{
		while (five <= 11)
		{
			while (two <= 31)
			{
				one = 100 - (10 * ten + 5 * five + 2 * two);
				if (ten + five + two + one== TOTAL)
						i++;
				two++;
			}
			five++;
		}
		ten++;
	}
	printf("%d\n", i);
	
	//考虑原因为每轮循环后循环体内ten、five、two、one未回到初始值(结果正确，为34）
	while (ten <= 6)
	{
		while (five <= 12)
		{
			while (two <= 40)
			{
				one = 100 - (10 * ten + 5 * five + 2 * two);
				if (ten + five + two + one == TOTAL && one>=1)
					i++;
				one = 1;
				two++;
			}
			two = 1;
			five++;
		}
		five = 1;
		ten++;
	}
	printf("%d\n", i);

	//暴力枚举（失败：结果为0），
	while (ten <= 40)
	{
		while (five <= 40)
		{
			while (two <= 40)
			{
				while (one <= 40)
				{
					total = 10 * ten + 5 * five + 2 * two + one;
					if (total == 100 && ten + five + two + one == TOTAL)
						i++;
					one++;
				}
				two++;
			}
			five++;
		}
		ten++;
	}
	printf("%d\n", i);

	//考虑原因是每次循环后ten、five、two、one的值没有回到1（结果34,成功）
	while (ten <= 40)
	{
		while (five <= 40)
		{
			while (two <= 40)
			{
				while (one <= 40)
				{
					total = 10 * ten + 5 * five + 2 * two + one;
					if (total == 100 && ten + five + two + one == TOTAL)
						i++;
					one++;
				}
				one = 1;
				two++;
			}
			two = 1;
			five++;
		}
		five = 1;
		ten++;
	}
	printf("%d\n", i);

	//讲解算法——for循环（结果34）
	for(int a=1;a<=40;a++)
		for(int b=1;b<=40;b++)
			for(int c=1;c<=40;c++)
				for (int d = 1; d <= 40; d++)
				{
					if (10 * a + 5 * b + 2 * c + d == 100 && a + b + c + d == 40)
						i++;
				}
	printf("%d\n", i);

	return 0;
}

```
### 数组的传递
* 存储非字符串数据的数组在传递时，除了传递**数组名**,还需要传递**数组长度**

* 对于**字符串数组**可以只传递数组名或者数组元素（因为末尾以\0结尾）
```c
#include <stdio.h>
void print(char d[])
{
    int i = 0;
    while (d[i] != '\0')    //此时d为形参，
							//该条件也可写为d[i]或者d[i]!=0，
							//i可忽略（传入的实参实质为字符数组的首地址）
    {
        printf("%c", d[i]);
        i++;
    }
    printf("\n");
}

int main(void)
{
    char c[10] = "hello";   //注意，字符数组不需要传入长度，只用首地址就行(字符串以'\0'结尾)
    print(c);               //c为实参，即实际传入函数的参数

    return 0;
}
```
### gets与puts
* 大小写转换问题：ASCII码中大小写字符在数值上相差32（大写字符比小写字符大32）

* 引入问题：scanf通过%s读取字符串时，当遇到空格后，就会匹配结束，因此无法一次读取一行带有空格的字符串

* 函数声明：
```c
char gets(char *str);
int puts(char *str);

//另一种读取字符串的函数
char *fgets(char *str, int n, FILE *stream)		//n为要读取的字符大小，stream为输入格式（scanf对应标准输入stdin）
```

```c
#include <stdio.h>
int main(void)
{
  char c[20];
  gets(c);
  puts(c);

  return 0;
}
```
* Tips:
  * gets和puts只能读取、打印**字符类型**或**字符串**
  * gets在读取一行字符串后，**自动在读取到的字符串后方加\0**，puts会自动在输出结果后面加入**换行符**
  * fgets会自动在字符后加\n和\0
  * 区分'\0'与'0'：注意字符'\0'对应ASCII码值0，而字符'0'对应值为48

### str系列操作函数
* 函数声明
```c
#include <string.h>
  size_t strlen(char *str);

  char *strcpy(char *to,const char *from);  //有const关键字修饰时，可以在此放一个字符串常量

  int strcmp(const char *str1,const char *str2);  //1<2时返回值小于0；1=2返回值等于0；1>2返回值大于0
  /*特别注意：该函数比较两个字符串对应位置的字符（实际比较的是ASCII码值），
  当出现第一个不匹配的字符时即停止，返回的是该次不匹配所产生的结果（而不是比较字符串的长度）*/

  char *strcat(char *str1,const char *str2);  //注意目标数组str1应能存下拼接后的字符串
```

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main(void)
{
	char c[20] = "wangdao";
	char d[20];

	printf("数组c内字符串长度=%d\n", strlen(c));

	strcpy(d, c);
	printf("将c中的内容复制到d中，现在d中为：%s\n", d);

	printf("c与d比较结果=%d\n", strcmp(c, d));
  puts("c与字符“wanga”比较的结果："); //注意：puts会自动在输出结果后面加入换行
  printf("%d\n",strcmp(c,"wanga"));
  

	strcat(c, d);
	printf("将d拼接到c的后面，现在c中为：%s\n", c);

	return 0;
}
```
## 指针
* 概念：指针的本质就是**地址**，即在一片内存空间内存储的数据是另一块数据的地址
### 取址符&（也称“引用”）与取值操作符*（也称“解引用”）
  * &i，表示获取变量i的地址值
  * \*p，表示**间接访问**指针p的所指向的地址上所存储的内容（注意\*只能对**指针**使用）

* 常见使用场景：**传递**和**偏移**
  * 传递：由于局部变量原理以及函数调用原理，c中传递数据给函数形参的过程实质是**值传递**，要对实参进行修改需要传递其**指针**
  * 偏移：指针可进行加减（不能进行乘除，没有意义）——指针+n（n为整数）是加的基类型大小*n 
* Tips：
  * 同一行语句定义多个指针变量需要这样写：int *a,*b,*c;
  * 内存有三种权限，掌握两种：可读、可写
```c
#include <stdio.h>
int main(void)
{
	int i = 1;
	int* p = &i;		//&i，表示对变量i取地址
	printf("%d\n", i);	//直接引用
	printf("%d\n", *p);	//间接引用，注意*只能对指针使用

	//在进行声明时，<类型> *<变量名或函数名>  表示后面的变量或函数返回值为一个指针

	return 0;
}
```
### 指针与自增自减运算符
* 优先级：\*的优先级**等于**--与++，规定优先级顺序为从右到左
* 对于\*p++，应先\*p，再将p+1，而不是对\*p得到的值+1（++的运算对象为p）
* 对于j=(\*p)++，应先为j=(\*p)，再(*p)+1（p所指向内存空间的值+1）（++的运算对象为\*p）

```c
#include<stdio.h>
int main(void)
{
	int a[3] = { 1,2,3 };
	int j;
	int *p = a;

	//仅自增
	j = a[0]++;
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);
	a[0] = 1; j = 0; p = a;//恢复初始状态
	//结果：a[0]=2,j=1,*p=2
	//运算对象：++为a[0]
	//原理：对于j=i++;先使用i,再增加i;故j=i,i=i+1,

	//指针自增
	j = *p++;
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);
	a[0] = 1; j = 0; p = a;//恢复初始状态
	//结果：a[0]=1,j=1,*p=2
	//运算对象：*为p，，++也为p
	//原理：*和++与--优先级相同，但执行顺序为从右到左，故此时++和--先执行
	//因此先j=*p，再p++;故j=*p,p++

	j = (*p)++;
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);
	a[0] = 1; j = 0; p = a;//恢复初始状态
	//结果：a[0]=2,j=1,*p=2
	//运算对象：*为p，++为(*p)
	//原理：(*p)优先级最高，故先取值为(1),再使用(*p)，再(*p)++
	//故：j=*p，(*p)++，注意由于*p是对a[0]地址上值的操作，故a[0]的值也改变




	return 0;
}
```
### 指针与一维数组
* C函数调用的本质是值传递
* 数组传递实际传递的是**指针**（即数组名，也是数组首地址的指针），没有传递长度
  * 指针法
  * 下标法

### 指针与动态内存申请
* 一般来说数组放于**栈空间**，故数组的大小一开始就定义好并确定下来了（因为栈空间在编译时是确定的，在相应进程或函数结束时栈空间将被释放）
* 如果使用的空间大小不确定，应使用**堆空间**（堆空间在使用后需要手动释放）

* malloc函数与free函数

```c
#include <stdlib.h>
void *malloc(size_t size);//该函数返回成功分配内存的首地址的指针（无类型）
//注意：void <函数名>表示该函数无返回类型；void *<函数名>表示该函数返回无类型的指针
//通常会对malloc返回的指针进行强制类型转换

void free(void *ptr);//该函数无返回值
//特别注意：free会释放ptr所指向的空间，但实际并未对p修改，p仍指向该空间，故称“野指针”
//对于该类指针，未避免使用p修改或访问到不属于当前进程的数据，最好把p手动置空
```
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int i;
	scanf("%d", &i);
	char* p;
	p = (char*)malloc(i);
	strcpy(p, "malloc success");
	puts(p);
	free(p);//注意释放内存空间时，注意p指针是否已经偏移，否则将导致释放失败
	//释放时的指针指向的位置必须和申请时返回的指针的位置一致！
	p = NULL;//清理野指针

	return 0;
}
```

### 栈空间与堆空间
* 栈的空间会随着函数或进程的执行结束而释放
* 堆空间不会随子函数的结束而释放，需要使用free手动释放，当然，主进程结束时也会释放
```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
char* print_stack()
{
	char c[17] = "I am print_stack";
	puts(c);	//表示函数内能正常打印
	return c;	//返回该字符串的指针
}
char* print_malloc()
{
	char* p = (char *)malloc(30);
	strcpy(p, "I am print_malloc");
	puts(p);	//函数内正常打印
	return p;
}
int main(void)
{
	char* p;
	p = print_stack();
	puts(p);	//不能正常打印！
	//因为栈的空间会随着函数的执行结束而释放，故当前p指向的位置所存放的数据已与在函数内时不同

	p = NULL;	//清理p
	p = print_malloc();		//个人犯错点：没有参数的函数名后面忘加括号
	puts(p);	//可以正常打印！
	//因为堆空间不会随子函数的结束而释放，需要使用free手动释放，当然，主进程结束时也会释放

	printf("释放前p指向%d\n", p);	//释放前p指向的地址
	free(p);
	printf("释放后p指向%d\n", p);	//释放后p指向的地址(与释放前一致，说明free只是释放了p所指向的内存，但并未将p置空)
	p = NULL;	//清理野指针

	return 0;
}
```
### 数组名==指针？
* 声明数组时，系统自动为该数组分配相应大小的内存空间，**数组名实际是一个指针（且相当于一个用const限定的常量，不可改变其指向），指向其数据的首地址**
* 声明指针时，需要对指针指向的位置初始化，否则不能使用，（不使用const声明该指针时）该指针为变量，可以改变其指向方向

```c
#include <stdio.h>
int main(void)
{
	char *p="hello";
	char c[10]="hello";
	c[0]='H';
	//p[0]='H';		//p指向"hello"字符串常量，不能对常量进行修改
	printf("c[0]=%c\n",c[0]);
	printf("p[0]=%c\n",p[0]);
	p="world";		//将p指向"world"字符串常量的首地址
	//c="world";	//非法，c为数组名，指向数组地址空间的首地址，为常量
	puts(p);

	return 0;
}
```
### 二级指针
* 即指向指针的指针（存放的值为一个指针的地址）
* 初始化一定是对一个一级指针取地址
* 想要在**子函数**中改变一个变量的值，必须要将**该变量的地址**传入
* 想要在**子函数**中改变一个指针变量的指向（即值），必须要将**该指针变量的地址**传入，传入的参数即为二级指针

```c
#include <stdio.h>
void change(int **p,int *q)
{
	*p=q;	//将二级指针p指向q（q为一级指针）
}

void change2(int *p,int *q)
{
	p=q;
}

int main(void)
{
	int i=10;
	int j=5;
	int *pi;
	int *pj;
	pi=&i;
	pj=&j;
	//子函数中直接传入指针地址（二级指针）即可实现对该指针指向（即指针的值）的修改
	printf("i=%d,*pi=%d,*pj=%d\n",i,*pi,*pj);	//结果：i和*pi都是10，*pj是5
	change(&pi,pj);		//目标是让*pi的值为j的值
	printf("i=%d,*pi=%d,*pj=%d\n",i,*pi,*pj);	//结果：i为10，*pi和*pj为5

	//主函数中指针赋值给指针可以直接改变其指向
	pj=&j;
	pi=&i;
	printf("*pi=%d,*pj=%d,pi=%d,pj=%d\n",*pi,*pj,pi,pj);
	pi=pj;				//目标是让*pi的值为j的值
	printf("*pi=%d,*pj=%d,pi=%d,pj=%d\n",*pi,*pj,pi,pj);
	/*结果
	*pi=10,*pj=5,pi=7338900,pj=7338888
	*pi=5,*pj=5,pi=7338888,pj=7338888
	*/

	//子函数中直接传入指针并修改将导致修改操作最后失效
	pi=&i;
	pj=&j;
	printf("*pi=%d,*pj=%d,pi=%d,pj=%d\n",*pi,*pj,pi,pj);
	change2(pi,pj);		//目标是让*pi的值为j的值
	printf("*pi=%d,*pj=%d,pi=%d,pj=%d\n",*pi,*pj,pi,pj);
	/*结果：
	*pi=10,*pj=5,pi=7338900,pj=7338888
	*pi=10,*pj=5,pi=7338900,pj=7338888
	*/

	return 0;
}
```

## 函数
### 函数定义、函数声明、函数调用
* 头文件中放的是函数声明以及一些常量
* 使用自定义头文件时，不应使用<>，而应使用""（表示头文件位于当前目录）
* mac编译(main.c为有主函数的源文件，fun.c为其他类型源文件)：gcc main.c fun.c -o main
* 多个源文件、自定义头文件于集成编译器中编译的过程
  1. 先编译：Func.c生成func.obj,Main.c生成main.obj
  2. 链接：将func.obj和main.obj变为main.exe
> 函数定义

1. 返回值
2. 函数名
3. 形参及其类型
4. 函数体

> 函数声明(放于头文件中)

1. 返回值
2. 函数名
3. 形参及其类型
* Tips：
  * 隐式声明：函数如果不显式地声明返回值的类型，则默认返回**整型**
  * 对于没有返回值的函数，最好使用该格式表示该函数无返回值：void <函数名>(形参)

### 递归
* 函数自己调用自己即为递归
  1. 根据数学方法、观察法寻找规律，推导公式（有关递归的）
  2. 寻找递归公式
  3. 寻找特殊的值，判断递归深度（一般与结束条件挂钩）
  4. 注意判断递归结束条件

```c
/*假如有n个台阶，一次只能上1个台阶或2个台阶，请问走到第n个台阶有多少种走法？
注意并非每次只能固定上1个台阶，每次都可能上1个或者2个台阶*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int step(int p)
{
	if (p == 1)			//结束条件
		return 1;
	else if (p == 2)	//结束条件
		return 2;
	else
		return step(p - 1) + step(p - 2);//递归公式
	/*//也可这样写
	if(p==1 || p==2)	//结束条件&特殊条件
		return p;
	else
		return step(p-1)+step(p-2)
	*/
}

int main(void)
{
	int n;
	scanf("%d", &n);

	printf("%d\n", step(n));

	return 0;
}
```
### 局部变量与全局变量
* 尽量避免使用全局变量（容易被修改）
## 结构体
* 一个结构体所占用的空间可能比结构体内结构成员所占的空间大
  * 因为CPU为了存取高效，一般需要对不足一次存取长度的数据放到一个存取长度的空间内（对齐），目的在于提高CPU的访存效率

```c
#define _CRT_SRCURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	//结构声明（又称“模板”）
	struct student {		//struct表示其后面跟的是一个结构，student是一个“可选”的标记
		int bianhao;		//括号内为结构成员列表
		int age;			//结构成员可以是c中的任意数据类型，甚至可以是一个结构
		char sex;
		char name[10];
		int score;
	};						//注意结构体声明的最后大括号后需要加分号


	//结构变量定义
	struct student i;//结构变量i
	struct student *ptstudent;//一个指向某结构类型的指针
	//以上定义相当于：
	struct student {
		int bianhao;
		int age;
		char sex;
		char name[10];
		int score;
	}i;
	//所以可以直接这样定义：
	struct {			//没有结构标记
		int bianhao;
		int age;
		char sex;
		char name[10];
		int score;
	}i;
	//如果想要多次使用某个结构模板，最好使用结构标记，或者使用typedef关键字


	//typedef关键字
	//功能1：为现有类型创建一个新名称（常使用大写）
	typedef int ZHENGXING;
	typedef unsigned char BYTE;
	//功能2：创建一个指向某类型的指针类型标识符，稍后可用该标识符声明指针（不用加*）
	typedef char *STRING;/*没有typedef关键字，编译器将把STRING识别为一个指向char的指针变量。
						   有了typedef关键字，编译器则把STRING解释成一个类型的标识符，该类型是指向char的指针*/
	STRING name, sign;//等价于char *name,*sign;
	//使用typedef关键字意义——代码即注释

	
	//结构变量初始化
	struct student arr[3]={	//声明一个student结构类型的数组，其中每个元素都是该结构类型
		1001,11,'m',"lele",80,
		1002,10,'f',"fanfan",90,
		1003,12,'m',"mingming",99
	 };
	struct student student4 ={
		.bianhao=1004,
		.age=10,
		.sex='f',
		.name="tutu",
		.score=90
	};
	struct student student5;
	student5=student4;
	/*不合法的初始化
	  sturct student next;
	  next={1001,11,'m',"lele",80};
	*/
	//注意:	1.结构体初始化与数组相似，只能在声明时完成
	//		2.现在允许将一个结构赋值给同类型的另一个结构（但是，不允许将一个数组赋值给另一个数组），甚至可以把结构作为返回值返回
	//		  还可以把一个结构初始化为另一个相同类型的结构
	//		  即使结构成员是数组，也能完成赋值
	//		3.可以使用指定初始化器（语法同数组），使用点运算符和成员名标识特定元素（数组用方括号和下标）


	//访问结构成员
	//方法1：下标法
	char sex = arr[0].sex;	//注意.的优先级与括号同级
		//注意数组不可赋值如：char name[10]=arr[0].name;
	//方法2：指针法
	struct student *a = arr;
	int b = a->bianhao;			//注意->优先级与括号同级

	return 0;
}
```

## C++引用
```c
//注意引用为C++语法，源文件需要以.cpp为后缀
#include <stdio.h>
#include <stdlib.h>

//将&写到形参是C++语法，称为引用(C不允许将&写到形参)
//对于使用引用的形参，可以在子函数中对实参进行修改
void modify_num(int &n)
{
	n = n + 1;
}

//对于指针的修改，&应放在变量前、*后
//使用引用对指针修改相当于C中使用二级指针
void modify_pointer(int *&pt)
{
	pt = (int *)malloc(20);
	pt[0] = 1;
}
int main(void)
{
	int a=2;
	modify_num(a);
	printf("%d\n", a);
	
	int* p=NULL;
	modify_pointer(p);
	printf("%d\n", p[0]);
	
	return 0;
}
```



## 问题梳理
### leecode题暴露
* 删除排序数组中的重复项
  1. 忘记指针初始化需要分配地址
  2. 函数体问题
    a.指针越界
    b.循环体没搞清楚：处理完第一次外层循环后，
        并将后面的数组元素覆盖第一个重复的元素，
        但是忘记这次该判断的仍然是第一个元素和第二个元素，
        直接指针后移再判断，造成漏判断第一个元素

```c
# include<stdio.h>
# include<stdlib.h>

//总结c中允许对结构使用二级指针指向结构内的元素
int main(void) {
    typedef struct L{
        int data;
        struct L* next;
    }Linknode, * Linklist;

    Linklist M= (Linknode*)malloc(sizeof(Linknode));
    Linknode *K=(Linknode *)malloc(sizeof(Linknode));
    M->next = K;
    K->data = 1;
    printf("%d", M->next->data);

    return 0;
   
}

/*
问题总结：
    1.混淆指针和结构了，声明结点时，如果要用链表法，需要在结构名前加*表示这是一个指向结构的指针
然后才能用链表方链接上该结构
    2.忘了加typedef...
    3.忘了给指针分配空间
*/
```