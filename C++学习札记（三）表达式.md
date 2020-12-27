# C++学习札记（三）表达式

[TOC]

&emsp;&emsp; C++ 中定义了很多操作符，应用在内置类型的操作元，也可以在自定义的类中定义操作符。本章介绍标准库中的操作符。

## 1 Fundamentals

### 1.1 基本概念

#### 左值和右值

右值：当使用一个对象作为右值，使用对象的值（它的内容）

左值：当使用一个对象作为左值，使用对象的标识（它在内存中的地址）

重要的是，当需要右值时，可以使用左值来代替（左值可以表示右值）；但不能在需要左值时，使用右值代替（右值不能表示左值）。



> 注意：在写组合表达式时，遵循两个规则：
>
> 1. 尽可能使用括号消除歧义
> 2. 在表达式中改变操作数的值，则在同一个表达式中不要使用该操作数



## 2 Arthmetic Operators

取余与除法运算

1. 取余运算

- m % -n = m % n
- -m % n = - (m % n)

2. 除法运算

- m / -n = -m / n

## 3 Increment and Decrement Operators

自增，自减运算符

- ++pbeg：pbeg + 1，返回 pbeg+1 的值的副本
- pbeg++：peg + 1，返回pbeg 之前的值

```C++
int i=0, j;
j = ++i;	// j=1, i=1
j = i++;	// j=1, i=2
```

2. 解引用和自增

```C++
auto pbeg = v.begin();
while(pbeg != v.end() && *pbeg >= 0)
  	cout << *pbeg++ << endl;
```

 `*pbeg++` 等价于 `*(pbeg++)` ，先自增后返回自增后的结果的前一个值，然后解引用。

> ⚠️注意：逻辑运算符左右两边有求值顺序，而关系运算符和等号运算符左右两边无求值顺序。



## 4 Member Access Operators

解引用的优先级小于 `.` 运算符

```C++
string s1 = "a string", *p = &s1;

auto n = s1.size();
n = (*p).size();
n = p->size();
```



## 7 The Conditional Operators

## 8 The Bitwise Operators

## 9 The `sizeof` Operators

## 10 Comma Operators

## 11 Type Operators

## 12 Operator Precedence Table

## Summary