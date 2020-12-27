# C++ 学习札记（四）函数

[TOC]

&emsp;&emsp;本章学习函数相关内容，主要包括：

- 函数定义及声明，包括参数传递和返回值
- 重载函数
- 函数匹配
- 函数指针
- ...



## 1 函数基础

&emsp;&emsp;函数定义由返回值类型，函数名，函数参数和一个函数体组成。

### 1.1 局部对象

&emsp;&emsp;在 C++ 中，名字有范围，对象有生命周期。理解下面两个概念是重要的：

- 名称范围是在程序代码中变量名可视的部分
- 生命周期是对象从程序执行到对象退出

参数和定义在函数中的变量被称为局部变量。



#### 1.1.1 自动变量

&emsp;&emsp;与局部变量对应的对象在执行函数中的变量定义时被创建，变量定义的块执行结束后退出。在块执行结束后退出的对象称为 **自动变量** 。参数即自动变量。



#### 1.1.2 局部 `static` 对象

&emsp;&emsp;定义为 `static` 的局部变量的生命周期周期贯穿函数的调用期间，在第一次执行变量定义时被初始化，在程序结束后被销毁。

```C++
size_t count_calls(){
  	static size_t ctr = 0;
  	return ++ctr;
}

int main(){
  	for (int i=0; i != 10; ++i)
      	cout << count_calls() << endl;
  	return 0;
}
```

&emsp;&emsp; 如果一个局部变量未被明确地初始化，则被初始值初始化，内置类型被初始化为0。



### 1.2 函数声明

&emsp;&emsp;函数声明即函数定义去掉函数体，以 `;` 结尾。返回值类型，函数名和参数类型也被称为函数接口。函数声明也被称为函数原型。



#### 1.2.1 函数声明应放在头文件中

> 声明函数的头文件应该被包含在定义函数的源文件中。



#### 1.2.2 分离编译

&emsp;&emsp;C++ 支持分离编译，分离编译使得程序分成多个文件，每个文件支持独立编译。



#### 1.2.3 编译和链接多个文件

```bash
gcc -lstdc++ fact.cpp factMain.cpp -o main
./main
```



## 2 传递参数

&emsp;&emsp;当函数被调用时，函数的形参数被传进来的实参创建和初始化。形参初始化与变量初始化相同，不同的是形参的类型由实参与形参传递方式决定。如果传递的是引用，则形参绑定的是实参，否则形参的值为实参的拷贝。根据传递的方式不同分为

- 引用传递
- 值传递



### 2.1 值传递

#### 指针参数

&emsp;&emsp;指针参数与非引用类型相同，当传递一个指针类型时，拷贝其指针值。即两个指针同时指向同一个对象，可以通过指针修改对象。

> 在C语言中，经常通过指针类型传递在函数外修改对象。但在C++ 中通常使用引用代替 指针类型。



### 2.2 引用传递

&emsp;&emsp;引用传参可以改变一个或多个实参，与其他引用相同，引用参数在初始化时直接被绑定在对象上。



#### 2.2.1 使用引用避免拷贝

&emsp;&emsp;拷贝较大的类类型或者容器是十分低效的。比如在比较两个很长的字符串时，避免拷贝花费很长时间，直接传递引用，避免修改字符串，将其声明为 `const` 类型即可。

```C++
bool isShorter(const string &s1, const string &s2){
  	return s1.size() < s2.size();
}
```



> 在函数中，引用的参数不需改变时，必须将其声明为 `const` 类型。

 

#### 2.2.2 使用引用参数返回额外的信息

&emsp;&emsp;函数只能返回单个返回值，如果需要返回多个值，可通过引用传递返回，如下面计算字符串的某个字符的个数和第一次出现的位置：

```C++
string::size_type find_char(const string &s, char c, string::size_type &occurs){
  	auto ret = s.size();
  	occurs = 0;
  
  	for (decltype(s.size())=0; i != s.size(); ++i){
      if (s[i] == c){
        	if (ret == s.size())
        	  	ret = i;
        	++occurs;
      }	
    }
  
  	return ret;
}
```



#### 2.2.3 `const` 形参与实参

&emsp;&emsp;当实参为 `const` 类型，传递给形参时，则被忽略，即 `top-level const` 被忽略。

> · `top-level` ：指针为 `const` 类型
>
>  `low-level`  ：指针所指的对象为 `const` 类型



1. 指针 / 引用形参 与 `const`
2. 尽可能使用 `const` 类型的引用



#### 2.2.4 数组形参

数组两个特殊的属性：1. 无法拷贝   2. 使用时会被转换为指针。下面三种方式等价

```C++
void print(const int*);
void print(const int[]);		// const int*
void print(const int[10]);  // const int*
```



##### 三种方式管理指针参数

1. C 语言用法，使用 `null` 字符判断

```C++
void print(const char *p){
  	if (*p)		// 判断指针是否为空指针
  			while(*p)
      			cout << *p++ << endl;
}
```



2. 使用标准库

```C++
void print(const int* beg, const int* end){
  	while (beg != end)
      	cout << *beg++ << endl;
}

int j[2] = {0, 1};
print(begin(j), end(j));
```



3. C语言和 老版本的C++ 中，传一个 `size` 参数

```C++
void print(const int* ia, size_t size){
  	for (size_t i=0; i != size; ++i)
      	cout << ia[i] << endl;
}

int j[2] = {0, 2};
print(j, end(j)-begin(j));
```



##### 数组参数与 `const`

`const` 类型的数组参数相当于指针的引用。



##### 数组引用参数

```C++
void print(int (&arr)[10]){		// size 也是参数的一部分
  	for (auto elem : arr)
      	cout << elem << endl;
}
```



##### 多维数组 参数

```C++
void print(int (*matrix)[10], int rowSize);
void print(int matrix[][10], int rowSize);
```



#### 2.2.5 多种参数的函数

1. 类型相同（常量，无法修改）

```C++
void error_msg(initializer_list<string> il){
  	for (auto beg = il.begin(); beg != il.end(); ++beg)
      	cout << *beg << " ";
  	cout << endl;
}
```

```C++
void error_msg(ErrCode e, initerlize_list<string> il){
  	cout << e.msg() << ": ";
  	for (const auto &elem : il)
      	cout << elem << " ";
  	cout << endl;
}
```



2. 类型不同

```C++
void foo(parm_list, ...);
void foo(...);
```





## 3 返回值类型及返回值语句

返回值类型：

- 值
- 引用
- 不能返回局部变量的引用 / 指针

### 3.1 函数无返回值



### 3.2 函数返回一个值

&emsp;&emsp;函数的返回值与定义的返回值必须匹配。

#### 那么值时如何被返回的？

&emsp;&emsp;值返回的方式与变量和参数初始化的方式相同：返回值在调用的地方初始化一个暂时值，该值为函数调用的结果。

```C++
const string &shorterString(const string &s1, const string &s2){
  	return s1.size() <= s2.size() ? s1 : s2;
}
```



#### 返回的类类型可以直接调用

```C++
auto sz = shorterString(s1, s2).size();
```



#### 引用类型返回值为左值

```C++
char &get_val(string &str, string::size_type ix){
  	return str[ix];
}

int main(){
  	string s("a value");
  	cout << s << endl;
  	get_val(s, 0) = 'A';
  	cout << s << endl;
  
  	return 0;
}
```



#### 列表初始化返回值

```C++
vector<string> process(){
  	// ...
  	
  	if (expected.empty())
      	return {};
  	else if (expected == actual)
      	return {"functionX", "okey"};
  	else
      	return {"functionX", expected, actual};
}
```



####  `main` 函数返回值

```C++
#include <cstdlib>

int main(){
  	if (some_failure)
      	return EXIT_FAILURE;
  	else
      	return EXIT_SUCCESS;
}
```



### 3.3 返回指向数组的指针

&emsp;&emsp;由于数组无法拷贝，函数不能返回一个数组，通过指针或者引用来代替。使用一下的声明方式简化

```C++
typedef int arrT[10];
using arrT = int[10];
arrT* func(int i);
```

声明一个返回数组指针的函数

```C++
type (*function(parameter_list))[dimention];

int arr[10];
int *arr[10];
int (*arr)[10];  // int (*func(para))[10]
```

#### 使用悬垂表示返回值类型

```C++
auto func(int i) -> int(*)[10];
```



#### 使用 `decltype` 声明

```C++
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

decltype(odd) *arrPtr(int i){
  	return (i % 2) ? &odd : &even;
}
```



## 4 函数重载

&emsp;&emsp;函数有相同名字但是参数不同称为函数重载。

```C++
void print(const char *cp);
void print(const int* beg, const int* end);
void print(const int ia[], size_t size);

int j[2] = {0, 1};
print("Hello world");
print(j, end(j) - begin(j));
print(begin(j), end(j));
```



不能用于重载函数的：

- 返回值类型不同
- 同一参数名不同
- 同一参数是否为 `top-const`



#### 重载与 `const`

1. `top-const` 并不能重载函数

```C++
Record lookup(Phone);
Record lookup(const Phone);		// redeclear
```



2. 指针/引用类型参数

```C++
Record lookup(Account&);
Record lookup(const Account&);
Record lookup(Account*);
Record lookup(const Account*);
```



#### 重载与 `const_cast`

```C++
const string &shorterString(const string &s1, const string &s2){
  	return s1.size() < s2.size() ? s1 : s2;
}

string &shorterString(string s1, string s2){
  	auto &r = shorterString(const_cast<const string&> s1, const_cast<const string&> s2);
  	return const_cast<const string&> (r);
}
```



重载函数有三个可能的结果

- `best match` ：编译器匹配至最佳的函数
- `no match` ：没有函数匹配
- `ambiguous call` ：超过一个函数匹配



#### 函数重载与作用域

&emsp;&emsp; 通常，在内部作用域声明函数名，则会隐藏外部作用域相同函数名的所有函数。

```C++
string read();
void print(const string &);
void print(double);

void fooBar(int ival){
  	bool read = false;
  	string s = read();	// 错误，read 在内部声明为 bool 类型
  	
  	void print(int);		// 隐藏外部的 print() 
  	print("Value");			// 错误， print(const string &) 被隐藏
  	print(ival);				// print(int)
  	print(3.14);				// print(int)
}
```

> C++ 中，名称寻找在类型匹配之前。



## 5 特殊用法

### 5.1 默认参数

&emsp;&emsp;函数可以声明在一个头文件中，也可在多个文件中声明，但是默认参数只能在给定的范围内声明一次。

> 默认参数应该在合适的头文件中的函数声明中具体化。



### 5.2 `Inline` 和 `constexpr` 函数

&emsp;&emsp;函数声明为 `inline` ，即每次调用被扩展至 `in line` 。 

```C++
cout << shorterString(s1, s2) << endl;
cout << (s1.size() < s2.size()) ? s1 : s2; << endl;

inline const string &
  shorterString(const string &s1, const string &s2){
  	return (s1.size() < s2.size()) ? s1 : s2;
}
```



&emsp;&emsp; `constexpr` 函数被用作常量表达式。

```C++
constexpr int new_sz() {return 42;}
constexpr int foo = new_sz();
```



## 6 函数匹配



## 7 函数指针

&emsp;&emsp;函数指针由函数返回值和它的参数决定，如下

```C++
bool lengthCompare(const string &, const string &);

bool (*pf)(const string &, const string&);
```

#### 使用函数指针

&emsp;&emsp;将函数名看作一个值，函数可自动转化为指针。

```C++
// 两个等价， & 取地址符可选
pf = lengthCompare;
pf = &lengthCompare;

bool b1 = pf("Hello", "Goodbye");
bool b2 = (*pf)("Hello", "Goodbye");
bool b3 = lengthCompare("Hello", "Goodbye");
```





#### 函数指针作为参数

```C++
void useBigger(const string &s1, const string &s2, 
              bool pf(const string &, const string &));
void useBigger(const string &s1, const string &s2, 
              bool (*pf)(const string &, const string &));

useBigger(s1, s2, lengthCompare);
```



使用别名定义：

```C++
typedef bool Func(const string &, const string &);
typedef decltype(lengthCompare) Func2;

typedef bool (FuncP*)(const string &, const string &);
typedef decltype(lengthCompare) FuncP2;
```



#### 返回函数指针

&emsp;&emsp;与数组相同，函数也无法返回，但可以返回函数指针，使用别名定义

```C++
using F = int(int* , int);
using PF = int(*)(int*, int);

PF f1(int);
F *f1(int);

int (*f1(int))(int*, int);
```



#### 使用 `auto` 或 `decltype` 声明

```C++
auto f1(int) -> int (*)(int*, int);

string::size_type sumLength(const string &, const string &);
string::size_type largerLength(const string &, const string &);
decltype(sumLength) *getFun(const string &);
```

