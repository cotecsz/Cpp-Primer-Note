# C++ 学习札记（二）字符串、向量和数组

[TOC]

本章主要介绍两种重要的类型，字符串和向量。字符串是变长字符的序列，向量是可变长度的给定类型集合。

## 1 Namespace

### 1.1 using 声明命名空间

&emsp;&emsp;对命名空间的每个成员进行单独声明，如下

```c++
#include <iostream>
using namespace std::cin;
using namespace std::cout;
using namespace std::endl;

int main(){
  	cout << "A Separate using Declaration Is Required for Each Name" << endl;
  	return 0;
}
```

### 1.2 头文件中不能使用 `using` 

&emsp;&emsp;在头文件中通常不能使用`using` 声明。因为头文件中的代码在编译过程中被拷贝至包含该头文件的源文件中，使得命名空间中的名字与源文件的命名可能发生冲突。



## 2 String

### 2.1 定义和初始化字符串

&emsp;&emsp;字符串是变长字符序列，包含头文件如下，初始化方式如下四种

```C++
#include <string>
using std::string;

// 空字符串
string s1;
// s1 字符串的拷贝
string s2 = s1;
// 字符拷贝
string s3 = "character";
// 直接初始化
string s4(10, 'b')
```

#### 直接初始化与拷贝初始化

拷贝初始化：当使用 `=` 对变量初始化时，编译器则会拷贝等号右边的变量对创建的目标变量进行初始化

直接初始化：当省略 `=` 对变量初始化时

```C++
// 拷贝初始化
string s5 = "hi";
// 直接初始化
string s6("hi");
string s7(10, 'c');
```



&emsp;&emsp;下面三种方式都可以初始化字符串 `s1` ，但是第二种和第三种初始化方式较为繁琐，可读性差，使用第一种方式进行初始化。

```C++
string s1("hello");

string s1 = string("hello");

string temp = string("hi");
string s1 = string("hello");
```

### 2.2 常用操作

|   Operation    | Use                               | Retrun     |
| :------------: | --------------------------------- | ---------- |
|    os << s     | s 写至输出流                      | os         |
|    is >> s     | 从输入流读取至 s                  | is         |
| getline(is, s) | 从输入流中读取一行写至s           | is         |
|   s.empty()    | 判断 s 是否为空                   | true/false |
|    s.size()    | 计算 s 的字符个数                 | n          |
|      s[n]      | s 的第 n 个字符                   |            |
|    s1 + s2     | 字符 s1 与 字符 s2 连接为新的字符 | string     |
|    s1 = s2     | 将字符 s2 的值拷贝至 字符 s1      |            |
|    s1 == s2    | 判断字符 s1 是否与字符 s2 相等    | true/false |
|    s1 != s2    | 判断字符 s1 是否与字符 s2 不相等  | true/false |
|  <, <=, >, >=  | 字符串大小比较                    | true/false |

#### 2.2.1 字符串写入

1. 连续写入

```C++
// contuine cin
string s1, s2;
cin >> s1 >> s2;
cout << s1 << s2 << endl;
```



2. 未知数量的字符串写入

```C++
string word;
while(cin >> word){
  	// process word
  	cout << word << endl;
}
```



3. 读取整行

```C++
string line;
while(getline(cin, line))
  		cout << line << endl;
```

#### 2.2.2 empty() 和 size()

&emsp;&emsp;增加终止条件，修改上面读取整行的例子，当读取为空时，读取结束，如下

```C++
string line;
while(getline(cin, line))
  	if(!line.empty())
      	cout << line << endl;
		else
      	break;
```

&emsp;&emsp;增加终止条件，修改上面读取整行的例子，当读取长度为3个字符至5个字符时，读取结束，如下

```C++
string line;
while(getline(cin, line))
  	if(line.size() >= 3 && line.size() <= 5)
      	cout << line << endl;
		else
      	break;
```



#### 2.2.3 string::size_type 类型

&emsp;&emsp; size() 方法返回值类型为 `string::size_type` ，而不是 `int` 类型。

&emsp;&emsp;`string` 类与其他库相同，定义了一些 `companion types` [1]。`string::size_type` 是 `companion type`的一种，它是一种无符号类型。在C++11标准中，可以通过 `auto` 或 `dealtype` 给定返回值类型，如下代码所示

> `Companion types` is likely just a figurative way to mention `member types` i.e. types declared within another type

```C++
auto len = line.size();
```

&emsp;&emsp;字符的大小一定是无符号类型，所以尽量避免 `unsigned` 类型与 `int` 类型进行比较。



#### 2.2.4 字符比较

&emsp;&emsp;当两个字符长度相同且包含对应字符相同时，字符相等。其他情况比较遵循如下两个规则：

- 若两个字符串长度不等，长度短的字符与长度长的字符对应相等，则 短字符小于长字符
- 若两个字符串对应位置字符不同，则比较第一个不同的字符

```C++
string str = "Hello";
string parse = "Hello World";
string sline = "Hi"
```



#### 2.2.5 字符串相加

1. 两个字符相加

```C++
string s1 = "Hello", s2 = "World";
string s3 = s1 + ", " + s2 + '\n';
```

2. 字符与字面值相加，字符常量与字符常量无法相加

```C++
string s4 = s1 + ", ";
string s5 = "Hello" + ", "; //错误，两个字符常量无法相加

//--------------------------------------------------
string s6 = s1 + ", " + "World";

string tmp = s1 + ", ";
s6 = tmp + "World";
//--------------------------------------------------

string s7 = "Hello" + ", " + s2; // 错误，"Hello" + ", " 无法做加法操作
```

> ⚠️警告：由于历史原因，与C兼容，字符常量不是string类型，所以在使用字符常量和string时，应该区分开。



### 2.3 字符串处理

下面为字符处理的一些库函数，包含在 `cctype` 头文件中。

| Function    | Use                                                          | Return       |
| ----------- | ------------------------------------------------------------ | ------------ |
| isalnum(c)  | 判断 c 是否为字母或数字                                      | true / flase |
| isalpha(c)  | 判断c 是否为字母                                             | true / flase |
| iscntrl(c)  | 判断 c 是否为控制字符                                        | true / flase |
| isdigit(c)  | 判断 c 是否为数字                                            | true / flase |
| islower(c)  | 判断 c 是否为小写字符                                        | true / flase |
| isprint(c)  | 判断 c 是否为输出字符                                        | true / flase |
| ispunct(c)  | 判断 c 是否为标点符号                                        | true / flase |
| isspace(c)  | 判断 c 是否为空白符，指空格，水平/垂直制表，换页，回车和换行 | true / flase |
| isupper(c)  | 判断 c 是否为大写字符                                        | true / flase |
| isxdigit(c) | 判断 c 是否为十六进制                                        | true / flase |
| tolower(c)  | 将 c 转换为小写字符                                          |              |
| toupper(c)  | 将 c 转换为大写字符                                          |              |

> 建议：使用 C++ 版本的 C 标准库的头文件
>
> 在 C++ 中使用 C 的标准库头文件时，直接将 `.h` 后缀去掉，在文件名前加 `c` ，如以上的字符串处理的头文件在C 语言中为 `ctype.h` ，在 编写 C++ 文件时，写成 `cctype` 。这些以 `c ` 开头的头文件，被定义在 `std` 命名空间中，在使用时可以避免明明冲突。



#### 2.3.1 使用 `Ranged-Based for` 处理字符串中所有字符

&emsp;&emsp;如果想处理字符串中的每个字符，最好的办法是使用新标准中的 `range for` 语句。

```C++
for (declaration : expression)
  	statement
```

&emsp;&emsp;1. 输出字符串中的字符代码如下

```C++
string str("Hello, Alice!");

for (auto c : str)
  	cout << c << endl;
```

&emsp;&emsp;2. 计算字符串中的标点符号， `decltype` 用来声明字符数量的类型（`string::size_type`）

```C++
string str("Hello, World!!!");

decltype (str.size())punct_cnt = 0;
for(auto c : str){
  	if(ispunct(c))
      	++punct_cnt;
}

cout << punct_cnt << " punctuation chararcters in " << str << endl;
```

&emsp;&emsp;3. 将所有字符转化为大写字符，使用引用可以修改字符

```C++
string str("Hello, Alice!");

for(auto &c : str)
  	c = isupper(c);

cout << str << endl;
```



#### 2.3.2 处理字符串中的特定字符

1. 使用下标输出第一个字符

```C++
string s = "Hello, Alice!";

if(!s.empty())
  	cout << s[0] << endl;
```

2. 将第一个字母大写

```C++
string s = "Hello, Alice!";

if(!s.empty())
  	s[0] = toupper(s[0])
```

3. 将第一个单词所有字母大写

```C++
string s = "Hello, Alice!";

for (decltype(s.size) index=0; index != s.size() && !isspace(s[index]); ++index)
  	s[index] = toupper(s[index]);
```

4. 将十进制转换为十六进制

```C++
const string hexdigits = "0123456789ABCDEF";
string::size_type n;
string result;

while (cin >> n)
		if (n < hexdigits.size())
				result += hexdigits[n];

cout << result << endl;
```



## 3 Vector

### 3.1 定义和初始化 `vector`

&emsp;&emsp;C++有函数模版和类模版， `vector` 是 **类模版** 。对于类模版，给定需要初始化的类进行实例化。使用 `vector` 的头文件为

```C++
#include <vector>
using std::vector;
```

&emsp;&emsp;定义 `vector` 的方式如下

```C++
vector<T> v1;								// 默认初始化，v1 为空
vector<T> v2(v1);						// v2 拷贝 v1 的每个元素进行初始化
vector<T> v2 = v1;					// 同 vector<T> v2{v1}
vector<T> v3(n, val);				// v3 以 n 个 val 元素进行初始化
vector<T> v4(n);						// v4 以 n 个默认元素进行初始化
vector<T> v5{a,b,c,...};		// v5 以 {a,b,c,...} 进行初始化
vector<T> v5 = {a,b,c,...}; // 同 vector<T> v5{a,b,c,...}
```

#### 3.1.1 列表初始化

1. 使用0或多个初始元素值进行初始化

```C++
vector<string> articles = {"a", "an", "the"};
```

2. 通过个数和元素值进行初始化

```C++
vector<int> ivec(10, 1);
vector<string> svec(10, "hi!");
```



#### 3.1.2 值初始化

&emsp;&emsp;通过值初始化的 `vector` 有两个限制：

1. 必须具有初始值
2. 给定元素个数

```C++
vector<int> ivec(10);
```



### 3.2 添加元素

&emsp;&emsp;`push_back` 可以在运行时在 `vector` 中添加元素，`push` 表示添加新的元素至 `vector`， `back` 表示 添加在 `vector` 的末尾。当不知道 `vector` 的大小时，直接创建 `vecotr` ，在运行时进行添加。

```C++
vector<int> ivec;
for (int i=0; i <= 100; i++)
  	ivec.push_back(i);
```

从输入流中读取，保存至 `vector` 中

```C++
string word;
vector<string> text;

while(cin >> word){
  	text.push_back(word);
}
```

>⚠️注意： `vector` 在运行时，添加元素十分高效，因此不需要再定义时确定它的大小，这样反而会影响其效率。

#### 添加元素可能的后果

1. 必须确保循环的正确性，即使循环改变了 `vector` 的大小
2. 如果在循环体内添加元素，则不能使用 `for` 范围

> 当在 `for` 循环时，不能在循环体中改变序列的大小。



### 3.3 其他操作

| Operation           | Use                            | Return       |
| ------------------- | ------------------------------ | ------------ |
| v.empty()           | 判断vector 是否为空            | true / false |
| v.size()            | 计算vector 的大小              |              |
| v.push_back(t)      | 给 vector 中添加元素           |              |
| v[n]                | 取第 n 个元素                  | 返回元素引用 |
| v1=v2               | 用 v2 中的元素替换 v1 中的元素 |              |
| v1 = {a, b, c, ...} | 列表初始化                     |              |
| v1 == v2            | 判断两个 vector 是否相同       | true / false |
| v1 != v2            | 判断两个vector 是否不同        | true / false |
| <, <=, >, >=        | 比较两个 vector 的大小         | true / false |

1. 求 vector 中的值的平方

```C++
vector ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

for (auto &i : ivec)
  	i *= i;
for (auto i : ivec)
  	cout << i << " ";
cout << endl;
```

2. 计算不同分数范围个数

```C++
vector<unsigned> score(11, 0);
unsigned grade;

while(cin >> grade){
  	if (grade <= 100)
      	++score[grade/10];
}
```

&emsp;&emsp; 在 `vector` 有值时，可以通过下标运算，如果没有则不能进行操作，如下所示为错误的：

```C++
vector<int> ivec;

for (decltype(ivec.size) i=0; i != ivec.size; ++i)
  	ivec[i] = i; // 错误，更改为 ivec.push_back(i);
```

> ⚠️警告：`vector` 下标操作只能获得已经存在的值，不能添加元素。下标元素不存在即为缓冲区溢出错误。



##  4 Iterators

&emsp;&emsp;通过下标可以处理 `vector` ，迭代器（iterators）也能完成处理。与指针不同，迭代器具有返回迭代器的成员 `begin` 和 `end` 。`begin` 返回一个指向第一个元素的迭代器，`end` 指向最后一个元素的后一个位置（即一个不存在的元素位置），用于标志处理完所有元素。

> 如果一个容器为空，那么其 `begin` 和 `end` 返回的迭代器相同，都指向 `off the end iterator` 。



### 4.1 迭代器操作

| Operation      | Uses                                            | Return       |
| -------------- | ----------------------------------------------- | ------------ |
| *iter          | 迭代器指向元素的引用                            | 引用         |
| iter->mem      | 同 (*iter).mem                                  |              |
| ++iter         | 指向下一个元素                                  | itertator    |
| --iter         | 指向上一个元素                                  | iterator     |
| iter1 == iter2 | 判断两个迭代器是否相等                          | ture / false |
| iter1 != iter2 | 判断是否指向同一个元素 / 是否都为 `off the end` | true / false |

1. 将字符串第一个字符大写，判断字符串是否为空：**s.begin() !=  s.end())**

```C++
string s("some string!");

if (s.begin() != s.end()!){
  	auto it = s.begin();
  	*it = toupper(*it);
}
```



### 4.2 移动迭代器从一个元素移动至另一个

1. 将字符串的第一个字符大写

```C++
String s("some string");

for (auto it = s.begin(); it != s.end() && isspace(*it); ++it)
  	*it = toupper(*it);
```



### 4.3 迭代器类型

&emsp;&emsp;正如 `vector` 和 `string` 有 `size_type` 一样，迭代器也定义了 `iterator` 和 `const_iterator` 类型。`const_iterator` 与 `const` 指针相同，只能读取指向的元素不能写入。如果 `vector` 和 `string` 类型为 `const` ，那么只能使用 `const_iterator` 。

```C++
vector<int>::iterator it;
string::iterator it2;
vector<int>::const_iterator it3;
string::const_iterator it4;
```



#### 4.3.1 `begin` 和 `end` 操作

&emsp;&emsp; `begin` 和 `end` 返回的类型由对象类型决定。当对象类型为 `const` 类型，则返回 `const_iterator` 类型的迭代器，否则返回 `iterator` 类型。

```C++
vector<int> v;
const vector<int> cv;

auto it1 = v.begin();			// it1 类型：iterator
auto it2 = cv.begin();		// it2 类型：const_iterator
```

&emsp;&emsp;当对对象进行只读操作而不进行写操作时，尽量使用 `const` 类型。在 C++11 中，有两个新的函数 `cbegin` 和 `cend` 。无论对象是否为 `const` 对象，都返回 `const_iterator` 类型。



#### 4.3.2 组合解引用和成员操作

&emsp;&emsp;在对迭代器所指的对象的成员进行操作时，需要先对其解引用，在对其成员操作

```C++
(*it).empty();	// 解引用后，使用对象的 empyt()
*it.empty();		// 错误，迭代器没有 empyt()
```

定义了简单的组合，使用 `->` 组合了解引用和使用成员操作。

```C++
it->empyt();		// 正确
```



#### 4.3.3 一些使迭代器无效的操作

1. 在 `for` 循环体内不能添加元素
2. `push_back` 会改变 `vector` 的大小，使得 `vector` 的迭代器无效



### 4.4 迭代器算术运算

&emsp;&emsp;所有标准库容器都支持自增，自减运算，`!=` 和 `==` 运算。对于 `string` 和 `vector` 类型支持额外的算术运算，如下表所示

| Operation     | Uses                |
| ------------- | ------------------- |
| iter + n      | iterator 向后增加 n |
| iter - n      | iterator 向前减少 n |
| iter += n     |                     |
| iter -= n     |                     |
| iter1 - iter2 |                     |
| <, <=, >, >=  |                     |

1. 找出中间元素的迭代器

```C++
auto mid = vi.begin() + vi.size()/2;
```

2. 二分搜索

```C++
auto beg = text.begin(), end = text.end();
auto mid = text.begin() + (end-begin)/2;

while(mid != end && *mid != sought){
  	if (sought < *mid)
      	end = mid;
  	else
      	beg = mid + 1;
  	mid = beg + (beg + end)/2;
}
```



##  5 Arrays

&emsp;&emsp; `Aarry` 与 `vecotr` 相似，是相同类型数据的容器，不同的是 `array` 具有固定大小，不能添加元素。如果不能确定容器大小，则使用 `vector` 。

### 5.1 定义和初始化 `array`

&emsp;&emsp; `Array` 在定义时，需要确定类型(type)和维度(dimension)。

```C++
unsigned cnt = 42;
constexpr unsigned sz = 42;

int arr[10];
int *parr[sz];
string bad[cnt];					// 错误，cnt不是常量表达式
string strs[get_size()];	// 当get_size() 是常量表达式时正确
```

#### 5.1.1 数组元素初始化

1. 当使用元素初始化时，可以忽略数组大小

```C++
const unsigned sz = 42;
int ia1[sz] = {0, 1, 2};
int a2[] = {0, 1, 2};
int a3[] = {0, 1, 2};
string a4[] = {"hi", "bye"};
int a5[2] = {0, 1, 2};			// 错误，a5大小为 2
```



#### 5.1.2 字符数组

初始化两种方式：

1. 指定字符初始化
2. 字面值常量初始化，注意字符串常量包含 `\0` ，再定义大小时 +1 ;

```C++
char a1[] = {'C', '+', '+'};
char a2[] = {'C', '+', '+', '\0'};
char a3[] = "C++";
char a4[5] = "Hello"; 		// 错误，"Hello\0" 为6个字符
```



#### 5.1.3 无法拷贝和赋值

&emsp;&emsp; 数组无法通过拷贝另一个数组进行初始化，也不能通过使用一个数组给另一个数组赋值进行初始化。

```C++
int a[] = {1, 2, 3};
int a2[] = a;			// 错误
a2 = a;						// 错误
```



#### 5.1.4 理解复杂数组声明

1. 从右往左读，定义 数组大小为10，声明为 `ptrs` 的指向 `int` 的指针

```C++
int *ptrs[10];
```

2. 由里往外读，定义 `Parray` 为指针，从右往左读，大小为 10 的 `int` 型数组。

```C++
int (*Parray)[10] = &arr;
```

3. 同上，定义 `arrRef` 为引用，大小为 10 的 `int` 型数组。

```C++
int (&arrRef)[10] = arr;
```

4. 同上，定义 `arry` 为引用，大小为 10 的 `int *` 型数组。

```C++
int *(&arry)[10] = ptrs;
```



### 5.2 获取数组元素

#### 5.2.1 使用下标获取数组元素

```C++
unsigned score[11] = {};
unsigned grade;

while (cin >> grade){
  	if (grade <= 100)
      	++score[grade / 10];
}
```



#### 5.2.2 使用 `range-for` 遍历数组

```C++
for (auto i : score)
  	cout << i << " ";
cout << endl;
```

> ⚠️警告：在使用下标获取元素时，需要检查下标是否越界。很多缓冲区溢出的错误时下标越界，错误地读取数组以外的内存数据或相似的数据结构。



### 5.3 指针和数组

&emsp;&emsp; 编译器会自动将数组等同指针，如下

```C++
string nums[] = {"one", "two", "three"};
string *p = &num[0];			// 等价于 string *p = num;
```



1. 使用 `auto` 定义，得到指针类型

```C++
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto ia2 = ia;
```

2. 使用 `decltype` 定义，返回 含有10个整型的数组类型

```C++
decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
```



#### 5.3.1 指针是迭代器

&emsp;&emsp; 指向数组元素的指针与 `vector` 和 `string` 的迭代器的操作相同。

1. 自加操作

```C++
int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = arr;
++p;
```



2. `for-range` 迭代所有元素

```C++
int *e = &arr[10]; // 指向 arr 最后一个元素

for (int *b = arr; b != e; ++b)
  	cout << *b << " ";
cout << endl;
```



#### 5.3.2 标准库中的 `begin()` 和 `end()`

&emsp;&emsp; 为了更方便和安全的使用指针，新的标准库中添加了 `begin` 和 `end` 方法，`begin()` 返回数组第一个元素的指针，`end` 返回数组最后一个元素的指针。

```C++
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int *beg = begin(ia);
int *end = end(ia);
```

1. 找出数组第一个负数

```C++
int *pbeg = begin(arr), *pend = end(arr);

while (pbeg != pend && *pbeg >= 0)
		++pbeg;
```



#### 5.3.3 指针运算

&emsp;&emsp;指针运算的结果指向 **当前数组** 元素的指针，或者数组最后一个元素的下一个位置。

```C++
constexpr size_t sz = 5;
int arr[sz] = {1, 2, 3, 4, 5};

int *ip = arr;
int *ip2 = ip+4;		// &arr[4]
```

> 只能在同一个对象（同一个数组或字符串）中进行指针运算操作。



#### 5.3.4 解引用与指针运算

```C++
int ia[] = {0, 2, 4, 6, 8};
int last = *(ia+4);		// ia[4]的值 
last = *ia + 4;				// ia 数组中第一个元素 + 4
```



#### 5.3.5 下标和指针

&emsp;&emsp; 与 `vector` 和 `string ` 不同，数组指针可以指向数组中任意一个元素，下标的内置类型不是 `unsigned` 类型 ,如下

```C++
int ia[] = {0, 2, 4, 6, 8};

int *p = ia;
i = *(p + 2);

int *p2 = &ia[2];
int j = p2[1];
int k = p2[-2];
```



## 6 Multidimensional Arrays

&emsp;&emsp; 定义一个数组：第一个维度是数组的维数，第二个维度是数组元素的个数

```C++
int arr[3][4];
int arr[10][20][30];
```



### 6.1 初始化多维数组的元素

1. 通过元素初始化

```C++
int ia[3][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {8, 9, 10, 11},
};

// 	等价于
int ia[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
```

2. 列初始化

```C++
int ia[3][4] = {{0}, {4}, {8}};	// 初始化第一列
```

3. 行初始化

```C++
int ia[3][4] = {0, 3, 6, 9};	// 初始化第一行
```



### 6.2 多维数组的下标

&emsp;&emsp; 如果下标个数为多维数组的维数则取得一个元素，下标个数少于多维数组的维数，则取(多维) 数组。

```C++
ia[2][3] = arr[0][0][0];		// 元素

int (&row)[4] = ia[1];			// row 为 ia第一行的4个元素的数组的引用
```



```C++
constexpr size_t rowCnt = 3, colCnt = 4;
int ia[rowCnt][colCnt];

for (size_t i=0; i != rowCnt; ++i)
  	for (size_t j=0; j != colCnt; ++j)
      	ia[i][j] = i * colCnt + j;
```



### 6.3 使用 `range-for` 遍历多维数组

1. 使用 `range-for` 迭代多维数组时，外层循环 必须为引用类型。

```C++
size_t cnt = 0;
for (auto &row : ia){
  	for (auto &col : row){
      	col = cnt;
     		++cnt;
    }
}

for (const auto &row : ia){
  	for (auto col : row){
      	cout << col << endl;
    }
}
```



### 6.4 指针和多维数组

1. 指针遍历二维数组

```C++
int arr[3][4] = {         
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11}
};

for (auto p=arr; p != arr+3; ++p){
    for (auto q=*p; q != *p+4; ++q){
      	cout << *q << " ";
    }
    cout << endl;
}
```

2. 使用 `begin` 和 `end` 方法

```C++
for (auto p=begin(arr); p != end(arr); ++p){
    for (auto q=begin(*p); q != end(*p); ++q){
      	cout << *q << " ";
    }
  	cout << endl;
}
```



### 6.5 多维数组指针别名

&emsp;&emsp; 使用 `using` 和 `typedef` 来给多维数组的指针起别名

```C++
using int_array = int[4];
typedef int int_array[4];

for (int_array *p = arr; p != arr + 3; ++p){
  	for (int *q = *p; p != p+4; ++q){
      	cout << *q << " ";
    }
  	cout << endl;
}
```



## 7 Summary

&emsp;&emsp;本章总结最重要的两个库 `vector` 和 `string` 。`string` 为变长字符序列， `vector` 为单个类型对象的容器。迭代器间接访问容器中的对象，避免使用指针来直接访问。 `Array` 通过指针进行访问元素。

## 参考

1. [companion type](https://stackoverflow.com/questions/41471741/string-companion-types)

2. [C++ 实现 cin 输入结束](https://blog.csdn.net/LYJ_viviani/article/details/52229517)

