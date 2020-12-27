# C++学习札记（九）泛型算法

[TOC]

## 1 概述

- 大多数算法在头文件 `algorithm` 中，`numeric`定义了一组数值通用算法
- 泛型算法通过遍历给定的迭代器范围来进行操作

查找 算法

1. 在 `vector` 中查找

```C++
int val = 42;
auto result = find(vec.cbegin(), vec.cend(), val);

cout << "The value:" << val << 
  	(result == c.cend() ? "Not present" : " is Present") << endl; 
```

2. 在 `list` 中查找

```C++
string val = "a value";
auto result = find(lst.cbegin(), lst.cend(), val);
```

3. 在内置数组中查找

```C++
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int val = 3;
int* result = find(begin(ia), end(ia), val);
```

> 迭代器令算法不依赖于容器，但算法依赖于元素类型。



## 2 初识泛型算法

### 2.1 只读算法

- 对于只读取不改变元素的算法，使用 `cbegin()` `cend`，使用返回的迭代器改变元素值，使用 `begin()` `end()`

1. 求和 `accumulate`

```C++
int sum = accumulate(vec.cbegin(), vec.cend(), 0);
```

2. 判断两个序列是否相等

```C++
equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()):
```



### 2.2 写容器算法

1. `fill(iter, iter, val)` 操作

```C++
fill(vec.begin(), vec.end(), 10);
fill(vec.begin(), vec.begin+vec.size()/2, 10);
```

2. `fill_n(dest, n, val)` 操作

```C++
vector<int> vec;
fill_n(vec.begin(), vec.size(), 0);
```

3. 使用 `back_insert` 进行写入

```C++
vector<int> vec;
fill_n(back_inserter(vec), 10, 0);
```



#### 拷贝算法

1. `copy` 操作

```C++
int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int a2[sizeof(a1)/ sizeof(*a1)];

auto ret = copy(begin(a1), end(a1), a2);	// ret 执行 a2 最后一个元素后的位置
```

2. `replace` 操作

```C++
replace(lst.begin(), lst.end(), 0, 42);
```

3. `replace_copy` 操作

```C++
replace(lst.cbegin(), lst.cend(), back_inserter(ivec), 0, 42);
```



### 2.3 重排容器算法

```C++
void elimDups(vector<string> &words){
  	sort(words.begin(), words.end());
  	auto end_unique = unique(words.begin, words.end());
  	words.erase(end_unique, words.end());
}
```

> `unique` 只删除相邻的相同的元素，返回一个指向不重复范围末尾的迭代器。



## 3 定制操作

### 3.1 向算法传递参数

- 谓词是可调用的表达式，其返回结果是一个能用作条件的值。

```C++
bool isShorter(const string &s1, const string &s2){
  	return s1.size() < s2.size();
}


elimDups(words);
stable_sort(words.begin(), words.end(), isShorter);

for (const auto &s : words)
  	cout << s << " ";
cout << endl;
```



### 3.2 `lambda` 表达式

- 忽略参数和返回值类型

```C++
auto f = [] {return 42};
cout << f() << endl;
```

- 向 `lambda` 传递参数

```C++
stable_sort(words.begin(), words.end(),
            [] (const string &s1, const string)
            		{return a.size() < b.size();})
```

- 捕捉列表

```C++
auto wc = find_if(words.begin(), words.end(), 
                 [sz] (const string &a)
                  {return a.size() >= sz;});
```

- `for-each` 算法

```C++
for_each(wc, words.end(), 
        [](const string &s){count << s << " ";});
cout << endl;
```



#### 3.2.1 `lambda` 捕获与返回

##### 值捕获

```C++
size_t v1 = 42;
auto f = [v1] {return v1;};
v1 = 0;
auto j = f();
```



##### 引用捕获

```C++
size_t v1 =42;
auto f2 = [&v1] {return v1;};
v1 = 0;
auto j = f2();
```

> 当我们通过捕捉引用时，必须确保 `lambda` 执行时，变量存在。
>
> 尽量保持 `lambda` 的变量捕捉简单化。



##### 隐式捕捉

- `&` ：捕捉引用方式
- `=` ：值捕获方式

```C++
wc = find_if(words.begin(), words.end(),
            [=](const string &s)
             {return s.size() >= sz;});
```

```C++
for_each(words.begin(), words.end(),
        [&, c] (const string &s)
         {os << s << c;});

for_each(words.begin(), words.end(),
        [=, &os](const string &s)
         {os << s << c;});
```



##### 可变 `lambda`

&emsp;&emsp; 默认情况下，对于一个值被拷贝的变量， `lambda` 不会改变其值，如果需要改变被捕获变量的值，在参数列表前加关键字 `mutable`

```C++
size_t v1 = 42;
auto f1 = [v1]() mutable{return ++v1;};
v1 = 0;
auto j = f1();		// j =43
```



```C++
size_t v1 = 42;
auto f2 = [&v1]{return ++v1;};
v1 = 0;
auto j = f2(); 		// j = 1
```



##### 指定 `lambda` 返回值类型

```C++
transform(vi.begin(), vi.end(),
         [](int i){return i<0? -i:i;});

transform(vi.begin(), vi.end(),
         [](int i) -> (int)
          {if(i<0) return -i; else return i;});
```



### 3.3 参数绑定

 `bind` 标准库函数定义在 `functional` 头文件中。

```C++
#include <functional>

bool check_size(const string &s, string::size_type sz){
  	return s.size() > sz;
}
auto check6 = bind(check_size, _1, sz);

auto wc = find_if(words.begin(), words.end(),
                 [sz](const string &s){return s.size>sz;});
auto wa = find_if(word.begin(), words.end(),
                 bind(check_size, _1, sz));
```



#### 使用 `placeholder` 名字

```C++
using std::placeholder::_1;

using namespace std::placeholder;
```



## 4 迭代器再探

### 4.1 插入迭代器

- `back_inserter`：给定迭代器元素后插入， 使用 `push_back`
- `front_inserter`：给定迭代器元素前插入，使用 `push_front`
- `inserter` ：给定迭代器元素后插入，使用 `insert`



## 5 泛型算法结构

根据迭代器能力不同，分为以下类别

| 类别           | 用法                                 |
| -------------- | ------------------------------------ |
| 输入迭代器     | 只读，不写；单遍扫描，只能递增       |
| 输出迭代器     | 只写，不读，单遍扫描，只能递增       |
| 前向迭代器     | 可读写；多遍扫描，只能递增           |
| 双向迭代器     | 可读写；多遍扫描，可递增递减         |
| 随机访问迭代器 | 可读写；多遍扫描，支持全部迭代器运算 |



### 5.1 5类迭代器

迭代器也有公共操作与特定操作：

- `ostream_iterator` 只支持递增，解引用，赋值
- `vector` ，`string` 和 `deque` 支持 递增，解引用，赋值，递减，关系和算术运算



### 5.1.1 迭代器类别

1. **输入迭代器** ：可读取序列元素，支持一下操作：

- `== `, `!=`：比较两个迭代器是否相等
- `++`：用于推进迭代器前置和后置递增运算
- `*` ：用于读取元素的解引用，只出现在赋值运算符右侧
- `->`：等价于 `*it.member` 
- `find` `accumulate` `istream_iterator`



2. **输出迭代器** ：输入迭代器的补集，只写不读

- `++`：用于推进迭代器前置和后置递增运算
- `*` ：解引用运算符，只出现在赋值运算符左侧
- `copy` `ostream_iterator`



3. **前向迭代器**：可读写元素

- 支持所有输入和输出迭代器操作
- 可多次读写，多遍扫描
- `replace` `forward_list` 



4. **双向迭代器**：可以正向/反向读写元素

- 支持所有前向迭代器操作
- `--`：支持前置和后置的递减运算
- `reverse` 和 除`forward_list` 其他所有容器



5. **随机访问迭代器** ：常量时间内访问序列中任意元素

- 支持双向迭代器操作
- `<` `<=` `>` `>=` ：用于比较两个迭代器相对位置的关系运算符
- `+` `+=` `-` `-=` ：用于与整数的加减运算
- `-` ：用于两个迭代器上的减法运算
- `iter[n]` ：等价于 `*(iter[n])` 
- `sort` `array` `deque` `string` `vector` ，内置数组元素指针



### 5.2 算法形参模式

大多数算法有一下4 中形式：

- *alg(beg, end, other args)*
- *alg(beg, end, dest, other args)*
- *alg(beg, end, beg2, other args)*
- *alg(beg, end, beg2, end2, other args)*

#### 5.2.1 接受单个目标迭代器算法

&emsp;&emsp; `dest` 参数是算法可以写入目的位置的迭代器，算法假定：按其需要写入数据，不管写入多少元素都是安全的

> 向输出迭代器写入元素，都假定目标空间足够容纳写入的数据。



### 5.3 算法命名规范

#### 5.3.1 算法使用重载形式传递一个谓词

```C++
unique(beg, end);
unique(beg, end, comp);
```



#### 5.3.2 `_if` 版本的算法

```C++
find(beg, end, val);
find_if(beg, end, pred);
```



#### 5.3.3 区分拷贝元素版本和不拷贝的版本

```C++
reverse(beg, end);
reverse_copy(beg, end, dest);
```

```C++
remove_if(v1.begin(), v1.end(),
         [](int i){return i % 2;});
remove_copy_if(v1.begin(), v1.end(), back_inserter(v2),
         [](int i){return i % 2;});
```



## 6 特定容器算法

 `list` 和 `forward_list` 特有的操作

| Function                        | Use                                                  |
| ------------------------------- | ---------------------------------------------------- |
| lst.merge(lst2)                 | `lst2` 合并至 `lst` ，`lst` `lst2` 必须有序          |
| lst.merge(lst2, comp)           | 元素从 `lst2` 中删除，合并后 `lst2` 为空，默认为 `<` |
| lst.remove(val)                 | 调用 `erase` 删掉 与`val` 值相同的元素               |
| lst.remove(val, pred)           | 删除 符合 `pred` 的元素                              |
| lst.reverse                     | 反转 `lst`                                           |
| lst.sort() / lst.sort(comp)     | 使用 `<` / `comp` 排序                               |
| lst.unique() / lst.unique(pred) | 调用 `erase` 删除同一个值的连续拷贝                  |



*lst.splice(args)* / *flst.splice(args)*

| Args            | Use                                                          |
| --------------- | ------------------------------------------------------------ |
| (p, lst2)       | 将 `lst2` 合并至 `lst`。 `lst2` 中元素被删除，且不能是同一个链表 |
| (p, lst2, p2)   | 将 `lst2` 的 `p2` 位置的元素合并至 `lst` 或 `p2` 位置后的所有元素合并至 `lst` |
| (p, lst2, b, e) | 将 `lst2` 的范围中的元素移动至 `lst` ，可以是相同链表，但不能指向给定范围元素 |



> 链表特有的操作会改变容器。

























