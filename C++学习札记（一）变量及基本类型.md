# C++ 学习札记（一）变量及基本类型

[TOC]

## 1 基本类型

### 1.1 算术类型

#### 1.1.1 整型和浮点型

&emsp;&emsp;算术类型分为整型和浮点型，其中，整型包括字符串，布尔类型。下面是C++基本内置类型及其尺寸：

| 类型        | 含义             | 最小尺寸     |
| ----------- | ---------------- | ------------ |
| int         | 整型             | 16位         |
| long        | 长整型           | 32位         |
| long long   | 长整型           | 64位         |
| short       | 短整型           | 16位         |
| bool        | 布尔类型         | 未定义       |
| char        | 字符             | 8位          |
| wchar_t     | 宽字符           | 16位         |
| char16_t    | Unicode 字符     | 16位         |
| char32_t    | Unicode 字符     | 32位         |
| float       | 单精度浮点数     | 6位有效数字  |
| double      | 双精度浮点数     | 10位有效数字 |
| long double | 扩展双精度浮点数 | 10位有效数字 |

&emsp;&emsp;带符号类型与无符号类型：

- 整型
  - int，unsigned int
  - short，unsigned int
  - long，unsigned long
  - long long，unsigned long long
- 字符型
  - char
  - signed char
  - unsigned char

#### 1.1.2 类型选择

1. 当确定数据不为负数时，选用无符号类型
2. 在实际应用中，`short` 太小，`long` 与 `int`  尺寸相等，故`int` 不足时，选用 `long long` 
3. 算术运算避免 `char` 或 `bool`
4. 浮点数运算时，常选用 `double`，因为 `float` 通常精度不够并且双精度浮点数和单精度浮点数的计算代价相差不大。

### 1.2 类型转换

&emsp;&emsp;对象类型定义了对象能包含的数据及其能参与的运算，其中包括从一种给定类型 **转换** 为另一种相关类型。在表达式的类型转换过程中，将低精度转换为高精度，有符号转换为无符号。

#### 1.2.1 类型转换

- 整型 ----> 布尔类型：`bool b = 10`
- 布尔类型 ---> 整型：`int i = b`
- 浮点型 ---> 整型：`i = 3.14`
- 整型 ---> 浮点型：`double d = i`
- 有符号 ---> 无符号类型：`unsigned char c = -1` ，c=255
- 带符号超出表示范围：`signed char c2` = 256

1. 无符号类型超出其范围，其结果是初始值对无符号类型表示数值总数 取模 后的余数，即初始值 % 数值表示范围 的余数。
2. 带符号类型超出其表示范围时，结果是未定义。

##### 取模 v.s. 取余

- 对于符号相同的两个数，取模与取余结果相同
- 对于符号不同的两个数：
  - mod(x, y) = x - y * floor(x / y )，其中 `floor()` 为下取整
  - rem(x, y) = x - y * fix(x / y)，其中 `fix()` 为上取整

比如，上面将有符号类型 ---> 无符号类型：

```bash
unsigned char c = -1;    // c = 255

对于unsigned char 类型，表示范围为 0-255，有
mod(-1, 256) = -1 - 256 * floor(-1/256)
其中， -1 / 256 = -0.0039， floor(-1/256) = -1
mod(-1, 256) = -1 - 256 * (-1) = 255
```



### 1.3 字面值常量

&emsp;&emsp;字面值常量对应一种数据类型，其形式和值决定它的数据类型。

1. 整型和浮点型字面值

- 十进制字面值是带符号的，八进制和十六进制字面值可能带符号，也可能是无符号，类型为整型中最小尺寸
- `short` 无对应字面值
- 浮点型字面值是 `double`

2. 字符和字符串字面值

- 由单引号括起来的一个字符为 `char` 型字面值
- 由双引号括起来的多个字符为字符串型字面值

&emsp;&emsp;字符串型字面值实际上是由常量字符构成的数组，字符串字面值实际长度比其内容多1，因为编译器会在字符串结尾处添加一个空字符 `\0`。

3. 布尔字面值和指针字面值

- `true` 和 `false` 布尔字面值
- `nullptr` 指针字面值



#### 1.3.1 转移序列

| 描述       | 符号 |
| ---------- | ---- |
| 换行符     | \n   |
| 横向制表符 | \t   |
| 纵向制表符 | \v   |
| 反斜杠     | \\   |
| 回车符     | \r   |
| 退格符     | \b   |
| 问号       | \?   |
| 进纸符     | \f   |
| 报警符     | \a   |
| 双引号     | \\'  |
| 单引号     | \\"  |



#### 1.3.2 指定字面值类型

1. 字符和字符串字面值

| 前缀 | 含义           | 类型     |
| ---- | -------------- | -------- |
| u    | Unicode 16字符 | char16_t |
| U    | Unicode 32字符 | char32_t |
| L    | 宽字符         | wchar_t  |
| u8   | UTF-8          | char     |

2. 整型字面值

| 后缀     | 最小匹配类型 |
| -------- | ------------ |
| u or U   | unsigned     |
| l or L   | long         |
| ll or LL | long long    |

3. 浮点型字面值

| 后缀   | 类型        |
| ------ | ----------- |
| f or F | float       |
| l or L | long double |



## 2 变量

&emsp;&emsp;**变量** 提供一个具名的，可供程序操作的**存储空间**。C++中每个变量都有其数据类型，数据类型决定

- 变量所占空间的大小和布局方式
- 该空间存储的值的范围
- 变量能参与的运算

&emsp;&emsp;**对象** 是一块能存储数据并具有某种类型的**内存空间**。

### 2.1 变量声明与定义

#### 2.1.1 变量定义

&emsp;&emsp;变量定义的基本形式：类型说明符 + 一个或多个变量名组成的列表。在变量定义时，还可为一个或多个变量赋以初值。当对象，在创建时获得特定的值，即对象被**初始化**。

> 注：初始化不是赋值，初始化含义是创建变量时赋予其一个初始值，而赋值的含义是把对象当前值擦除，而以一个新值来替代。

##### 列表初始化

&emsp;&emsp;C++中显式初始化由几种不同的形式，其中使用广泛的是列表初始化（用一组花括号括起来的初始值）进行初始化：

```C++
int var = 0;
int var = {0};
int var{0};
int var(0);
```

##### 默认初始化

&emsp;&emsp;如果定义变量没有指定初值，则变量被默认初始化，初始值由变量类型及其位置决定。

1. 内置类型的默认初始化由变量定义的位置决定
   - 在函数体之外的内置类型变量默认初始化为0
   - 在函数体内部的内置类型变量不被初始化（未定义）
2. 类决定自己的初始化方式

> 建议初始化每个内置类型变量。



#### 2.1.2 变量声明 v.s. 定义

&emsp;&emsp;**声明** 使得名字被程序所知，一个文件想使用别处定义的名字，则必须包含对那个名字的声明。

&emsp;&emsp;**定义** 负责创建与名字关联的实体，申请存储空间，也可能为变量赋一个初始值。

```c++
extern int i; // 声明 
int j; //声明 & 定义
```

> 变量只能被定义一次，但可被多次声明。

##### 如何在多个文件使用同一个变量？

&emsp;&emsp;在多个文件中，使用同一个变量，需要将变量声明和定义分离。变量定义必须出现在且只出现在一个文件中，而其他用到该变量的文件必须对其进行声明，绝不能重复定义。即：

1. 在一个文件中定义
2. 在其他文件中声明



### 2.2 标识符与作用域

#### 2.2.1 标识符

&emsp;&emsp;C++ 标识符：

- 由字母，数字，下划线组成
- 以字母，下划线开头
- 长度无限制
- 大小写敏感

##### 命名规范

在变量命名时，命名规范可提高程序可读性：

- 标识符能体现实际含义，如 `mathScore`
- 变量名一般用小写，如 `jack`
- 用户自定义类一般以大写开头，如 `Student`
- 标识符若有多个单词，单词之间应用明显区分，如 `studentIndex`

##### C++ 关键字及操作符替代名

| alignas    | continue     | friend    | register         | true     |
| ---------- | ------------ | --------- | ---------------- | -------- |
| alignof    | decltype     | goto      | reinterpret_cast | try      |
| asm        | default      | if        | return           | typedef  |
| auto       | delete       | inline    | short            | typeid   |
| bool       | do           | int       | signed           | typename |
| break      | double       | long      | sizeof           | union    |
| case       | dynamic_cast | mutable   | static           | unsigned |
| catch      | else         | namespace | static_assert    | using    |
| char       | enum         | new       | static_cast      | virtual  |
| char16_t   | explicit     | noexcept  | struct           | void     |
| char32_t   | export       | nullptr   | switch           | volatile |
| class      | extern       | opterator | template         | wchar_t  |
| const      | false        | private   | this             | while    |
| constexpr  | float        | protected | thread_local     |          |
| const_cast | for          | public    | Throw            |          |



| and    | bitand | compl | not_eq | or_eq | xor_eq |
| ------ | ------ | ----- | ------ | ----- | ------ |
| and_eq | bitor  | not   | or     | xor   |        |



#### 2.2.2 作用域

&emsp;&emsp;作用域是程序的一部分，表示变量名称的有效区域。

##### 全局作用域

&emsp;&emsp;全局作用域：定义在所有花括号之外，比如下面的 `main` 函数。

```C++
int main(){
  int sum = 0;
  for(int i = 0; i <= 10; i++)
    sum += i;
  return 0;
}
```

##### 块作用域

&emsp;&emsp;块作用域：在函数体或循环体内部定义的变量，其作用域是从定义处至函数体或循环体结束，比如，上面的`sum` 变量作用域为从定义 `sum` 开始至 `main` 函数结束；变量 `i` 的作用域则是从 定义`i` 开始至 `for` 循环结束。

##### 嵌套作用域

&emsp;&emsp;作用域被彼此包含，被包含的作用域为**内层作用域** ，包含着别的作用域称为 **外层作用域** 。下例中 `main` 函数中的`sum` 为内层作用域，函数之外的 `sum` 为外层作用域，当作用域被嵌套时，会使用相对接近的作用域。 

```C++
int sum = 0;

int main(){
  int sum = 0;
  for(int i = 0; i < 10; i++)
    sum += i;
}
```



## 3 引用及指针

### 3.1 引用

&emsp;&emsp;引用是对象的一个别名，引用类型引用另外一种类型。在定义引用时，只是把引用与它的初始值绑定，而不是将初始值拷贝给引用。

```C++
int val = 10;
int &refVal = val;
int &refVal2 = refVal;
```



### 3.2 指针

&emsp;&emsp;指针是指向另外一种类型的复合类型。指针本身就是一个对象，允许对指针进行赋值和拷贝，并且无需在定义时赋初值。利用指针访问访问对象时，使用 `*` 解引用符进行访问。

```C++
int val = 10;
int *pVal = &val;
*pVal = 99;    // val = 99
```

指针值有以下4种：

1. 指向一个对象
2. 指向紧邻对象所占空间的下一个位置
3. 空指针，即指针没有指向任何对象
4. 无效指针，上述情况外的其他值

#### * 与 & 符号的多重含义

- & 在声明中 --->  引用
- & 在表达式中 ---> 取地址
- *在声明中 ---> 指针
- *在表达式中 ---> 解引用

#### 空指针

&emsp;&emsp;空指针不指向任何对象，在使用指针前需要判断指针是否为空，下面是几种生成空指针的方法:

```C++
int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL;
```

> 建议初始化所有指针。

指针相同的三种情况：

1. 指针存放的地址值相同
2. 指向同一对象
3. 指向用一个对象的下一地址



void* 指针：

1. 拿它和别的指针比较，作为函数的输入输出
2. 赋给另外一个void* 指针



> 对于一条比较复杂的指针或引用的声明语句，从右往左阅读有助于弄清它的真实含义。



## 4 const限定符

&emsp;&emsp;const限定符是防止对于值的改变，`const` 限定的变量不能进行修改。

```C++
const int bufSize = 512;
```

1. 定义及初始化

```c++
const int i = get_size();    //运行时初始化
const int j = 42;            //编译时初始化
```

2. const 对象仅在文件内有效

如何在多个文件使用const 对象？对于 `const` 变量无论声明还是定义都添加 `extern` 关键字，只需定义一次即可。

```C++
// file_1.c 定义并初始化
extern const int bufSize = fcn();

// file_1.h 
extern const int bufSize;
```



### 4.1 const引用

#### 4.1.1 初始化和对const的引用

&emsp;&emsp;把引用绑定到 `const` 对象上称为对常量的引用。

```C++
const int val = 10;
const int &refVal = val;
```

&emsp;&emsp;引用类型必须与其所引用对象的类型一致，不包含

1. 在初始化常量引用时允许用任意表达式作为初始值
2. 允许为一个常量引用绑定非常量对象、字面值，甚至表达式



#### 4.1.2 对 `const` 的引用可能引用一个非 `const` 对象

&emsp;&emsp;常量引用是对引用可参与的操作作出限定，而对于引用本身是否为常量未做限定，所以当对象是个非常量时，允许通过其他途径修改对象的值。

```C++
int i = 10;
int &r1 = i;
const int &r2 = i;
r1 = 0;    //正确，r1是非常量引用，可以修改 i 的值
r2 = 0;    //错误，r2是常量引用，不能修改对象的值
```



### 4.2 const与指针

&emsp;&emsp;指针本身是一个对象，它又可以指向另一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量是两个相互独立的问题。因此，

- 指针是常量时，指针对象不可修改
- 指针不是常量时，指针对象可修改

- 指针指向常量时，指针对象必须是常量，因为常量地址只能使用指向常量的指针存放
- 指针指向非常量时，指针对象可以是常量，也可以是非常量，都可以通过指针对象修改非常量的值

#### 4.2.1 指向常量的指针（`pointer to const`）

&emsp;&emsp;与引用相同，可以令指针指向常量或非常量。指向常量的指针不能用于改变其所指对象的值。要想存放常量的地址，只能使用指向常量的指针：

```C++
const double d = 3.14;
double *ptr = &d;    //错误，ptr非常量指针
const double *cptr = &d;
*cptr = 12;          //错误，cptr为常量指针
```

&emsp;&emsp;指针类型必须与所指对象的类型一致，但有两个例外，第一是可以令一个指向常量的指针指向一个非常量对象：

```C++
double dval = 3.14;
cptr = &dval;    //	正确，但不能通过cptr更改dval的值。
```

&emsp;&emsp;与常量引用一样，指向常量的指针指向的对象可以不是常量，但指向常量的指针不能通过该指针修改对象的值，但是该对象的值可以通过其他途径进行修改。

#### 4.2.2 const 指针（`const pointer`）

&emsp;&emsp;指针作为对象，也可以作为常量。常量指针必须 **初始化** ，一旦初始化，则它的值（即指针保存的地址）将不能改变。

&emsp;&emsp;把 `*` 放在 `const` 之前说明指针是一个常量，即不变的是指针本身而非指向的那个值。

```C++
int errNumb = 0;
int *const curErr = &errNumb;    //常量指针（指向整型），curErr一直指向errnum
const double pi = 3.1415926;
const double *const ppi = &pi;   //常量指针（指向双精度浮点型常量），ppi 是指向常量对象的常量指针
```



> 要理解对象的类型，最简单的办法是从右向左阅读。

### 4.3 顶层 `const`

&emsp;&emsp;**顶层 `const`** 表示指针本身是个常量；**底层 `const` ** 表示指针所指的对象是一个常量。一般的，顶层 `const` 可以表示任意的对象是常量，比如算术类型、类、指针等。底层 `const` 则与指针和引用等复合类型部分有关。

```C++
int i = 0;              
int *const p1 = &i;				//常量指针，顶层const
const int ci = 40;				//常量，顶层const
const int *p2 = &ci;			//指向常量的指针，底层const
const int *const p3 = p2; //指向常量的常量指针，顶层const & 底层const
const int &r = ci;				//用于声明引用的const都是底层const
```

&emsp;&emsp;对象拷贝时，顶层 `const` 与底层 `const` 明显不同：

- 顶层 `const` 无影响
- 底层 `const` 
  - 拷入与拷出对象必须具有相同的底层 `const`
  - 两个对象类型可以转换
  - 非常量可以转换为常量

```C++
int *p = p3;				// 错误，p3包含底层const，p没有
p2 = p3;						// 正确，p2和p3都是底层const
p2 = &i;						// 正确，int *能转换成const int * 
int &r = ci;				// 错误，普通的int& 不能绑定在int 常量上
const int &r2 = i;	// 正确，const int & 可以绑定在一个普通 int 上
```



### 4.4 constexpr 与常量表达式

&emsp;&emsp; **常量表达式** 是指值不会改变并且在编译过程中能得到计算结果的表达式。C++11中，允许将变量声明为 `constexpr` 类型以编译器来验证变量的值是否是一个常量表达式。

```C++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size();
```

&emsp;&emsp; 在 `constexpr` 声明中如果定义一个指针，限定符 `constexpr` 仅对指针有效，与指针所指对象无关。

```C++
const int *p = nullptr;    //指向整型常量的指针
constexpr int *q = nullptr； //常量指针
constexpr int i = 40;			 //整型常量
constexpr const int *p = &i; //p 是常量指针，指向整型常量
constexpr int *p1 = &j;    //p1是常量指针，指向整数 j
```



## 5 处理类型

### 5.1 类型别名

1. ` typedef` 关键字

```C++
typedef double wages;    // wage 是double的别名
typedef wage base, *p;	 // base 是double的别名，p 是double* 的别名
```

2. `using` 关键字

```C++
using wages = double;    // wage 是double的别名
```



### 5.2 auto 类型说明符

&emsp;&emsp;`auto` 类型说明符可以使编译器分析表达式所属的类型。

```C++
auto item = val1 + val2;    // 由val1 和 val2相加结果推断出 item 的类型
```

#### 复合类型，常量和auto

1. 由于使用引用本质是是使用引用的对象，所以编译器以引用对象的类型作为 `auto` 的类型

```C++
int i = 0, &r = i;
auto a = r;				// a 是整型
```

2. `auto` 会忽略顶层 `const` ，底层 `const` 被保留下来

```C++
const int ci = i, &cr = ci;    
auto b = ci;    // b 是整型
auto c = cr;    // c 是整型
auto d = &i;    // d 是整型指针
auto e = &ci;   // e 是指向整数常量的指针
```

3. `auto` 类型是 顶层 `const`，需要明确指出

```C++
const auto f = ci;    // ci的类型为int， f的类型为const int
```

4. 引用类型也可以设置为 `auto` 

```C++
auto &g = ci;    // g 是整型常量引用，绑定到ci
auto &h = 43;    // 错误，非常量引用不能绑定到字面值
const auto &j = 43;    // 正确，常量引用可以绑定到字面值
```



### 5.3 decltype 类型指示符

&emsp;&emsp;decltype 类型指示符：从表达式中推断出定义的变量的类型，而不用表达式的值初始化变量。

1. `decltype` 处理顶层 `const` 和引用方式与 `auto` 有些许不用，如果表达式是一个变量，则返回变量的类型包括顶层 `const` 和引用

```C++
const int ci = 0, &cj = ci;
decltype(ci) x = 0;    // x 的类型是const int
decltype(cj) y = x;    // y 的类型是const int&，y 绑定到 x
decltype(cj) z;    // 错误，z 是一个引用，必须初始化
```

2. 如果 `decltype` 使用的表达式不是一个变量，则 `decltype` 返回表达式结果对应的类型。

```C++
int i = 42, *p = &i, &r = i;
decltype(r + 0) b;    // 正确，b 是int，未被初始化
decltype(*p) c;       // 错误，c 是int &，必须初始化
decltype((i)) d;      // 错误，d 是int &，必须初始化
decltype(i) e;			  // 正确，e 是int，未被初始化
```

注意：

- 当表达式的内容是解引用操作，则 `decltyp` 将得到引用类型
- 当变量名加上括号，则 `decltype` 将得到引用类型

> &emsp;&emsp;⚠️WARNING：`decltype((variable))` 的结果永远是引用，而 `decltype(variable)` 结果只有当 `variable` 本身是引用时才是引用。



## 6 自定义数据结构

```C++
#ifndef SALES_DATA_H
#define ASLES_DATA_H
#include <string>
struct Sales_data{
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
};
#endif
```

