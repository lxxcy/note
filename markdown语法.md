# markdown语法[^标题1] 

[TOC]

## 标题 [^标题2] 

* *use a ‘#’ to create the first title*

* *use more ‘#’ to create smaller title*

***
## 段落  
* *斜体*
* **粗体**
* ***粗斜体***
* 下面是一个分隔线：   
***
* ~~删除线~~
* <u>下换线</u>
* 脚注 [^脚注名]  
***
## 列表

这是一个**无序**列表：
* 这是第一个元素
* 这是第二个元素 
+ 也可以这样（第三个元素）
- 还可以这样（第四个元素）

这是一个**有序**列表：
  1.第一个元素
  2.第二个元素

这是一个**嵌套**列表：
* 第一个元素
    1.嵌套元素1（前面添加4个空格或者一个tab键（即制表符））
    2.嵌套元素2  
* 第二个元素
***
## 目录
* 自动生成目录：只需要在恰当的位置添加 [TOC] 符号，凡是以 # 定义的标题都会被编排到目录中
* 手动添加目录：将「列表」和「页内超链接」相结合
***
## 区块（即引用）
* 区块可以嵌套
> 区块1
> > 区块2
> >
> > > 区块3  
***
## 代码  
* > 单行代码可以这样书写：
`#include <stdio.h>` 代表这是一个代码，但是只能叙述单行
* > 区块代码表示：

 	<#include <stdio.h> \*注意该行首位增加了一个tap键（即制表符）或者也可以用四个空格（注意这是c注释）然后再是小于符号*\
 	int main(void)
 	{
 	printf("hello world");
 	getchar();
 	return 0;
 	}
 	>

* > 也可以这样表示：（三个上点后面指定编程语言，当然，也可以不指定，指定的语言不显示）  
```C
	#include <stdio.h> \*注意该行首位增加了一个tap键（即制表符）或者也可以用四个空格（注意这是c注释）然后再是小于符号*\
 	int main(void)
 	{
 	printf("hello world");
 	getchar();
 	return 0;
 	}
```
***
## 链接  
* 普通形式的链接：
	这里链接了[菜鸟教程](https://www.runoob.com/markdown/md-link.html)
	当然也可以直接放地址：<https://www.runoob.com/markdown/md-link.html>
	
* 高级链接	前面方括号内为链接名称，后面使用方括号创建链接的变量名，文档末尾可以为链接的变量赋值（即网址）
	[高级链接：这里链接了dillinger：][dillinger]

* 按住ctrl键再点击连接名即可转到打开链接到的网页
***
## 图片
* 感叹号后接方括号（内部为图片描述），然后是小括号（内部为图片的地址）
	![这里是图片的描述]()
* 遗憾的是，markdown还不能指定图片大小参数，如果需要，可以使用普通的 <img> 标签（双引号中为图片的地址）：

<img src=" " width="50%">
***

### 相对路径使用
* 在表示相对路径中，单点表示当前目录，双点表示上一级目录，反斜杠“/”表示分隔目录；
* 相对路径特殊符号有以下几种表示意义：
	1.以“./”开头，代表当前目录和文件目录在同一个目录里，“./”也可以省略不写！
	2.以"../"开头：向上走一级，代表目标文件在当前文件所在的上一级目录；
	3.以"../../"开头：向上走两级，代表父级的父级目录，也就是上上级目录，再说明白点，就是上一级目录的上一级目录
	4.以"/”开头，代表根目录

应用：
![脊髓横切面](..\笔记本\image\15-3新生儿脊髓膨大横切面.jpg)

## 表格
* 使用竖直符号分隔表格内容
	表头下一列的减号代表上面是一个表头
	英文冒号在减号前是左对齐，左边为右对齐，把减号包饶即居中对齐，计算机默认左对齐
|表头1|表头2|表头3|表头4|
|:---|---:|:---:|---|
|内容11|内容21|内容31|内容14|
|内容21|内容22|内容23|内容24|

* 表格内换行
使用html标记语言<br>插入两者之间
***
## 高级技巧
### 支持的HTML元素
不在 Markdown 涵盖范围之内的标签，都可以直接在文档里面用 HTML 撰写。
目前支持的 HTML 元素有：<kbd> <b> <i> <em> <sup> <sub> <br>等 

### 转义
使用反斜杠转义特殊字符：\*正常显示星号*\

### 公式
可以使用两个美元符 $$ 包裹 TeX 或 LaTeX 格式的数学公式来实现。提交后，问答和文章页会根据需要加载 Mathjax 对数学公式进行渲染。

###  使用to-do列表
* 减号、空格、左中括号、空格、右中括号  列表
* GFM task list
- [x] GFM task list 1
- [x] GFM task list 2
- [x] GFM task list 3
    - [ ] GFM task list 3-1
    - [ ] GFM task list 3-2
    - [ ] GFM task list 3-3
- [ ] GFM task list 4
    - [ ] GFM task list 4-1
    - [ ] GFM task list 4-2

#### 特殊符号 HTML Entities Codes

&copy; &  &uml; &trade; &iexcl; &pound;
&amp; &lt; &gt; &yen; &euro; &reg; &plusmn; &para; &sect; &brvbar; &macr; &laquo; &middot; 

X&sup2; Y&sup3; &frac34; &frac14;  &times;  &divide;   &raquo;

18&ordm;C  &quot;  &apos;

[========]

### Emoji表情 :smiley:

> Blockquotes :star:

#### GFM task lists & Emoji & fontAwesome icon emoji & editormd logo emoji :editormd-logo-5x:

- [x] :smiley: @mentions, :smiley: #refs, [links](), **formatting**, and <del>tags</del> supported :editormd-logo:;
- [x] list syntax required (any unordered or ordered list supported) :editormd-logo-3x:;
- [x] [x] :smiley: this is a complete item :smiley:;
- [ ] []this is an incomplete item [test link](#) :fa-star: @pandao; 
- [ ] [x]this is an incomplete item :fa-star: :fa-gear:;
    - [ ] :smiley: this is an incomplete item [test link](#) :fa-star: :fa-gear:;
    - [ ] :smiley: this is  :fa-star: :fa-gear: an incomplete item [test link](#);

#### 反斜杠 Escape

\*literal asterisks\*

[========]
            
### 科学公式 TeX(KaTeX)

$$E=mc^2$$

行内的公式$$E=mc^2$$行内的公式，行内的$$E=mc^2$$公式。

$$x > y$$

$$\(\sqrt{3x-1}+(1+x)^2\)$$
                    
$$\sin(\alpha)^{\theta}=\sum_{i=0}^{n}(x^i + \cos(f))$$

多行公式：

```math
\displaystyle
\left( \sum\_{k=1}^n a\_k b\_k \right)^2
\leq
\left( \sum\_{k=1}^n a\_k^2 \right)
\left( \sum\_{k=1}^n b\_k^2 \right)
```

```katex
\displaystyle 
    \frac{1}{
        \Bigl(\sqrt{\phi \sqrt{5}}-\phi\Bigr) e^{
        \frac25 \pi}} = 1+\frac{e^{-2\pi}} {1+\frac{e^{-4\pi}} {
        1+\frac{e^{-6\pi}}
        {1+\frac{e^{-8\pi}}
         {1+\cdots} }
        } 
    }
```

```latex
f(x) = \int_{-\infty}^\infty
    \hat f(\xi)\,e^{2 \pi i \xi x}
    \,d\xi
```

### 分页符 Page break

> Print Test: Ctrl + P

[========]

### 绘制流程图 Flowchart

```flow
st=>start: 用户登陆
op=>operation: 登陆操作
cond=>condition: 登陆成功 Yes or No?
e=>end: 进入后台

st->op->cond
cond(yes)->e
cond(no)->op
```

[========]
                    
### 绘制序列图 Sequence Diagram

```seq
Andrew->China: Says Hello 
Note right of China: China thinks\nabout it 
China-->Andrew: How are you? 
Andrew->>China: I am good thanks!
```

## 详解
![](./markdown语法详解.jpeg)




 	

[^标题2]: 小标题
[^标题1]: 大标题
[^脚注名]:文档末尾再次书写脚注名，加上英文冒号以给出脚注
[dillinger]:https://dillinger.io/