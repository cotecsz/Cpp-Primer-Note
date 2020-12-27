# C++学习札记（八）序列容器

[TOC]

## 1 序列容器概览

下表给出所有顺序容器，顺序容器提供了快速顺序访问元素的能力

| Type         | Use                                                          |
| ------------ | ------------------------------------------------------------ |
| vector       | 可变大小的`array` ,支持随机访问。<br />除了尾部，在其他地方插入删除很慢。 |
| deque        | 双端队列，支持快速随机访问。<br />在头尾快速插入和删除。     |
| list         | 双向链表，仅支持双向顺序访问。<br />在链表中任何位置插入/删除很快 |
| forward_list | 单向链表，仅支持单向顺序访问。<br />在链表中任何位置插入删除很快。 |
| array        | 固定大小的`array`，支持快速随机访问。<br />不能添加/删除元素。 |
| string       | 与 `vector` 相似的含有字符序列容器。<br />快速随机访问，在尾部插入和删除很快。 |



### 确定使用哪种顺序容器

> 通常，使用 `vector` 是最好的选择，除非有更好的理由选择其他容器。

选择容器的基本原则：

- 除非有更好的理由选择其他容器，否则选择 **`vector`**
- 程序含有 **小的元素且空间的额外开销** 很重要，不要使用 `list` 和 `forward_list`
- 程序需要在容器 **中间** 插入/删除元素，应使用 `list` 和 `forward_list`
- 程序需要在 **头尾** 插入/删除元素，但不会在中间插入/删除，应使用 `deque`
- 如果程序在读取输入时才需要在容器 **中间插入** 元素，随后需要随机访问元素：
  - 确定是否真的需要在容器中间添加元素。在 `vector` 中追加数据，再用 `sort()` 重排数据，避免在中间位置添加元素。
  - 如果必须在中间插入元素，考虑在输入阶段使用 `list` ，输入完成将 `list` 中的内容拷贝到 `vector` 中。



## 2 容器标准库概览

&emsp;&emsp;一般来说，每个容器都定义在一个头文件中，`deque` 定义在头文件 `deque` 中，`list` 定义在头文件 `list` 中。

下表为容器操作：

| Type Aliases    |                                                      |
| --------------- | ---------------------------------------------------- |
| iterator        | 该容器类型的迭代器类型                               |
| const_iterator  | 可以读取但不能修改的迭代器类型                       |
| size_type       | 无符号整数类型，足以保存此种容器类型最大可能容器大小 |
| difference_type | 带符号整型类型，足够保存两个迭代器之间的距离         |
| value_type      | 元素类型                                             |
| reference       | 元素的左值类型，等价于 `value_type &`                |
| const_reference | 元素的 `const` 左值类型，等价于 `const value_type &` |

| Construction      |                                                              |
| ----------------- | ------------------------------------------------------------ |
| C c;              | 默认构造函数，构造空容器                                     |
| C c1(c2);         | 构造 `c2` 的拷贝 `c1`                                        |
| C c(b, e);        | 构造 `c` ，将迭代器 `b` 和 `e` 指定范围内的元素拷贝至 `c`（`array` 不支持） |
| C c{a, b, c, ...} | 初始化列表 `c`                                               |

| Assignement and swap |                                                      |
| -------------------- | ---------------------------------------------------- |
| c1 = c2              | 将 `c1` 的元素替换为 `c2` 中的元素                   |
| c1 = {a, b, c, ...}  | 将 `c1` 中的元素替换为列表中的元素，不适用于 `array` |
| a.swap(b)            | 交换 `a` 和 `b` 的元素                               |
| swap(a, b)           | 同 `a.swap(b)`                                       |

| size         |                                                  |
| ------------ | ------------------------------------------------ |
| c.size()     | `c` 中元素的数目 （不支持 `forwad_list`）        |
| c.max_size() | `c` 可保存的最大元素的数目                       |
| c.empty()    | 若 `c` 中存储元素，返回 `true`，否则返回 `false` |

| Add/Remove Elements |                                 |
| ------------------- | ------------------------------- |
| c.insert(args)      | 将 `arg` 元素拷贝至 `c`         |
| c.emplace(inits)    | 用 `init` 构造 `c` 中的一个元素 |
| c.erase(args)       | 删除 `arg` 指定元素             |
| c.clear()           | 删除 `c` 中所有元素             |

| Equality and Relational Operation |                                  |
| --------------------------------- | -------------------------------- |
| ==, !=                            | 所有容器都支持等于/不等于运算符  |
| <, <=, >, >=                      | 关系运算符（无序关联容器不支持） |

| Obtain Iterator      |                                             |
| -------------------- | ------------------------------------------- |
| c.begin(), c.end()   | 返回 `c` 的首元素和尾元素之后的位置的迭代器 |
| c.cbegin(), c.cend() | 返回 `const_iterator`                       |

| Reversible Containers(not valid for forward list) |                                             |
| ------------------------------------------------- | ------------------------------------------- |
| reverse_iterator                                  | 逆序寻址元素的迭代器                        |
| const_reverse_iterator                            | 不能修改的逆序寻址元素的迭代器              |
| c.rbegin(), c.rend()                              | 指向 `c` 的尾元素和首元素之前的位置的迭代器 |
| c.crbegin, c.crend()                              | 返回 `const_reverse_iterator`               |



### 2.1 迭代器

#### 迭代器范围

&emsp;&emsp;一个 **迭代器范围**（iterator range)由一对迭代器表示，两个迭代器分别指向同一个容器的元素或者是尾元素后的位置，即左闭右开，称为 **左闭合区间** ，记为 `[begin, end)`

> 构成范围的迭代器要求：
>
> 1. 指向同一个容器中的元素，或者是容器最后一个元素之后的位置
> 2. 可以通过反复递增 `begin` 到达 `end` ，即 `end` 不在 `begin`之前



#### 左闭合范围蕴含的编程假设

1. `begin == end` ：范围为空
2. `begin != end` ：范围至少包含一个元素，且 `begin` 指向该范围的第一个元素
3. 可以对 `begin` 递增若干次，使得 `begin == end`



### 2.2 容器类型成员

容器类型：`size_type` ，`iterator` ，`const_iterator` , `value_type`，`reference` ，`const_reference`

```C++
list<string>::itertor iter;
vector<int>::difference_type count;
```



### 2.3 `begin` 和 `end` 成员

```C++
list<string> a = {"Milton", "Shakespeare", "Austen"};
auto it1 = a.begin();		// list<string>::iterator
auto it2 = a.rbegin();	// list<string>::reverse_iterator
auto it3 = a.cbegin();	// list<string>::const_iterator
auto it4 = a.crbegin();	// list<string>::const_reverse_iterator
```



```C++
// 显式指定
list<string>::iterator it5 = a.begin();
list<string>::const_iterator it6 = a.begin();

// C++11 
// 依赖于 a 的类型
auto it7 = a.begin();		// 仅当 a 为 const 类型时，it7 为 const_iterator
auto it8 = a.cbegin();	// it8 为 const_iterator
```

> 当不需要写访问时，应使用 `cbegin` 和 `cend`。



### 2.4 容器定义和初始化

| Init                   |                                                              |
| ---------------------- | ------------------------------------------------------------ |
| C c;                   | 默认构造函数，若 `C` 为 `array` ，则默认初始化，否则为空     |
| C c1(c2); / C c1 = c2; | `c1` 初始化为 `c2` 的拷贝                                    |
| C c{a, b, c, ...};     | `C` 初始化为 初始化列表元素的拷贝，列表中的元素必须与 `c`    |
| C c = {a, b, c, ...};  | 元素类型相容                                                 |
| C c(b, e);             | `c` 初始化为迭代器 `b` 和 `e` 指定范围中的元素的拷贝         |
| C seq(n);              | `seq` 包含 `n` 个元素，对元素进行值初始化，此构造函数为 `explicit` |
| C seq(n, t)            | `seq` 包含 `n` 个初始值为 `t` 的元素                         |



#### 2.4.1 拷贝初始化（`C c1(c2); / C c1 = c2` and `C c(b, e)`）

```C++
list<string> autor = {"Milton", "Shakespeare", "Austen"};
vector<const char *> articles = {"a", "an", "the"};

list<string> l2(author);
deque<string> authList(author);		// 错误，容器类型不匹配
vector<string> words(author);			// 错误，容器类型不匹配

// 使用迭代器范围初始化，支持类型转换
forward_list<string> words(articles.begin(), articles.end());
```



#### 2.4.2 列表初始化（`C c{a, b, c, ...}/ C c={a, b, c, ...}`）

```C++
list<string> autor = {"Milton", "Shakespeare", "Austen"};
vector<const char *> articles = {"a", "an", "the"};
```



#### 2.4.3 与顺序容器大小相关的构造函数	

```C++
vector<int> ivec(10, -1);			// 10 个元素，初始化为 -1
list<string> svec(10, "hi!");	// 10 个元素，初始化为 "hi!"
forward_list<int> ivec(10);		// 10 个元素，默认初始化为 0
deque<string> svec(10);				// 10 个元素，默认初始化为 ""
```



#### 2.4.4 标准库 `array` 具有固定大小

与内置数组相同，标准库 `array` 的大小也是类型的一部分。

```C++
array<int, 42>
array<string, 10>
```

与内置数组不同，标准库 `array` 可以进行拷贝和赋值操作

```C++
int digit[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int cpy[10] = digit;				//错误
array<int, 10> digs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
array<int, 10> copy = digs;	// 正确
```



### 2.5 赋值和 `swap`

| Operation                               | --                                                   |
| --------------------------------------- | ---------------------------------------------------- |
| c1 = c2                                 | 将 `c2` 元素拷贝至 `c1`                              |
| c = {a, b, c, ...}                      | 将 `c1` 中元素替换为初始化列表的拷贝，`array` 不支持 |
| swap(c1, c2)                            | 交换 `c1 / c2` 中的元素，交换比拷贝快得多            |
| c1.swap(c2)                             |                                                      |
| assign 操作**不适用**于关联容器和 array |                                                      |
| seq.assign(b, e)                        | 将 `seq` 元素替换为 迭代器范围的元素                 |
| seq.assign(il)                          | 将 `seq` 元素替换为 初始化列表 `il` 的元素           |
| seq.assign(n ,t)                        | 将 `seq` 元素替换为 `n` 个值为 `t` 的元素            |



#### 2.5.1 使用 `assign` (仅适用于顺序容器)

&emsp;&emsp;赋值运算要求左右两边的运算对象具有相同的类型，但`assign` 使得不同但相容的类型赋值

```C++
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;			// 错误，类型不匹配

// 1. assign(b, e)
names.assign(oldstype.cbegin(), oldstyle.cend());

// 2. assign(n, t)
// 等价于 
// slist1.clear();
// slist1.insert(slist1.begin(), 10, "Hiya!");
list<string> slist1(1);		// 1个元素，为空字符串
slist.assign(10, "Hiya!");// 10 个元素
```



#### 2.5.2 使用 `swap`

```C++
vector<string> svec1(10);
vector<string> svec2(42);
swap(svec1, svec2);
```

交换的特点：

1. 除`array` 外，`swap` 不对任何元素进行拷贝，赋值或插入操作，因此保证在常数时间内完成
2. 除`string` 外，`swap` 之后指向容器的迭代器，引用或指针都不会失效
3. 与其他容器不同， `array` 的 `swap` 会交换它们的元素，因此所需时间与 `array` 大小成正比

> 统一使用非成员版本的 `swap（）`是一个好习惯。



### 2.6 容器大小操作

- size()
- empty()
- max_size()

除 `forward_list` 不支持 `size()` ，其他容器都支持以上三种操作。



### 2.7 关系运算符

- 所有容器都支持 `==` 和 `!=`
- 除无序关联容器外，所有容器都支持 `>` , `>=`, `<`, `<=`

关系运算与 `string` 的关系运算类似：

1. 两个容器大小且所有元素两两对应相等，则两容器相等
2. 两个容器大小不等，较小容器是较大容器的对应元素，则较小容器小于较大容器
3. 如果两个容器都不是另一个容器的前缀子序列，则比较第一个不相等的元素

> 只有当元素类型也定义了相应的关系运算符时，才可以使用关系运算符比较两个容器。



## 3 序列容器操作

1. `array` 不支持改变容器大小的操作
2. `forward_list` 有自己专有的 `insert` 和 `emplace`
3. `forward_list` 不支持 `push_back` 和 `emplace_back`
4. `vector` 和 `string` 不支持 `push_front` 和 `emplace_front`

| Function                                  | Use                                                    | Return                                    |
| ----------------------------------------- | ------------------------------------------------------ | ----------------------------------------- |
| c.push_back(t)<br />c.emplace_back(arg)   | 在 `c` 的尾部创建一个值为`t` / `arg` 创建的元素        | void                                      |
| c.push_front(t)<br />c.emplace_front(arg) | 在 `c` 的头部创建一个值为`t` / `arg` 创建的元素        | void                                      |
| c.insert(p, t)<br />c.emplace(p, arg)     | 在迭代器 `p` 指向的元素前插入 `t` / `arg` 创建的元素   | 指向新添加元素的迭代器                    |
| c.insert(p, n, t)                         | 在迭代器 `p` 指向的元素前插入 `n` 个值为 `t` 元素      | 指向新添加元素的迭代器，若范围为空，返回p |
| c.insert(p, b, e)                         | 在迭代器 `p` 指向的元素前插入 迭代器 `p` `e`之间的元素 | 指向新添加元素的迭代器，若范围为空，返回p |
| c.insert(p, il)                           | `il` 为花括号包围的元素值列表                          | 指向新添加元素的迭代器，若范围为空，返回p |



### 3.1 向容器中添加元素

####  3.1.1 使用 `push_back`

- 除 `array` 和 `forward_list` 不支持外，其他容器都支持 `push_back`
- 容器元素是 **拷贝**

```C++
string word;
while (cin >> word)
  	container.push_back(word);
```



#### 3.1.2 使用 `push_front`

- `list`，`forward_list`， `deque` 还支持 `push_front`
- `deque` 像 `vector` 一样有随机访问元素的能力，但支持 `push_front`
- `deque` 首尾插入是常量时间，中间插入与 `vector` 一样会很耗时

```C++
list<int> ilist;
for (size_t ix=0; ix !=4 ++ix)
  	ilist.push_front(ix);				// 3 2 1 0
```



#### 3.1.3 在容器的特定位置添加元素

- `vector` ，`string` ，`list`，`deque` 支持 `insert` 成员在任意位置插入元素
- `forward_list` 有特殊版本的 `insert`

```C++
vector<string> svec;
list<string> slist;

// 等价于
// slist.push_front("Hello");
slist.insert(slist.begin(), "Hello");

// vector 不支持 push_front，但可以插入在 begin之前
// vector 插入尾部以外的位置会很慢
svec.insert(svec.begin(), "Hello");
```



#### 3.1.4 插入范围内

```C++
// 1. c.insert(p, n, t);
svec.insert(svec.end(), 10, "Anna");

// 2. c.insert(p, b, e);
slist.insert(slist.begin(), slist.end()-2, slist.end());

// 3. c.insert(p, il);
slist.insert(slist.end(), {"these", "words", "will", "go", "at", "the", "end"});
```



#### 3.1.5 使用 `insert` 的返回值

```C++
list<string> lst;
auto iter = lst.begin();

while (cin >> word)
  	// 等价于
  	// lst.push_front(word)
  	iter = lst.insert(iter, word);		
```



#### 3.1.6 使用 `emplace` 操作

- `emplace_back`   -----   `push_back`
- `emplace_front`   -----   `push_front`
- `emplace`              -----   `insert`

```C++
// 使用 Sale_data 默认构造函数
c.emplace_back();

// 使用 Sale_data(string)
c.emplace(iter, "99999-9999-999");
// 使用 Sales_data(string, double, double)
c.emplace_front("978-05783404-987", 25, 25.2);
```



### 3.2 访问元素

-  `at` 和下标操作只适用于 `string` ，`vector` ，`deque` ，`array`
-  `back` 不适用于 `forward_list`
- 访问成员函数返回的是引用

| Function  | Use                                                          |
| --------- | ------------------------------------------------------------ |
| c.back()  | 返回 `c` 中尾元素的引用，若 `c` 为空，则函数未定义           |
| c.front() | 返回 `c` 中首元素的应用，若 `c` 为空，则函数未定义           |
| c[n]      | 返回 `c` 中下标为 `n` 的引用，若 `n >= size()` ，则函数行为未定义 |
| c.at(n)   | 返回 `c` 中下标为 `n` 的引用，如果下标越界，则抛出异常       |

```C++
if (!c.empty()){
  	// 首元素
  	auto val = *c.begin(), val2 = c.front();
  	
  	// 尾元素
  	auto last = c.end();
  	auto val3 = *(--last);
  	auto val4 = c.back();
}
```



#### 下标操作和安全的随机访问

```C++
vector<string> svec;
cout << svec[0];			// 运行时错误
cout << svec.at(0);		// 抛出 out_of_range 异常
```



### 3.3 删除元素

- `forward_list` 有特殊版本的 `erase`
- `forward_list` 不支持 `pop_back`
- `vector` ，`string` 不支持 `pop_front`

| Function      | Use                                           |                                                              |
| ------------- | --------------------------------------------- | ------------------------------------------------------------ |
| c.pop_back()  | 删除 `c`尾元素，若 `c` 为空，函数行为未定义。 | void                                                         |
| c.pop_front() | 删除 `c`首元素，若 `c` 为空，函数行为未定义。 | void                                                         |
| c.erase(b, e) | 删除 `b` `e` 所指定范围的元素                 | 被删元素之后的元素迭代器，<br />若 `e` 为 最后一个元素，返回 尾后迭代器<br />若 `e` 为尾后迭代器，则函数行为未定义 |
| c.erase(p)    | 删除迭代器 `p` 所指的元素                     | 最后被删元素之后的元素迭代器<br />若 `e`为尾后迭代器，则返回尾后迭代器 |
| c.clear()     | 删除 `c` 中所有元素                           | void                                                         |



#### 3.4 特殊的 `forward_list` 操作

| Function                  | Use                                 |
| ------------------------- | ----------------------------------- |
| lst.before_begin()        | 返回链表首元素的前一个位置的迭代器  |
| lst.cbefor_begin()        | 返回 `const_iterator`               |
| lst.insert_after(p, t)    | 在迭代器 `p` 之后的位置插入元素     |
| lst.insert_after(p, n, t) |                                     |
| lst.insert_after(p, il)   |                                     |
| emplace_after(p, args)    | 使用 `args` 在 `p` 位置之后创建对象 |
| lst.erase_after(p)        | 删除 `p` 位置之后的元素             |
| lst.erase_after(b, e)     |                                     |

```C++
forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto prev = flst.before_begin();
auto curr = flst.begin();

while (curr != flst.end()){
  			if (*curr % 2)
          	curr = flst.erase_after(prev);
  			else{
          	prev = curr;
          	++curr;
        }
}
  	
```



### 3.5 改变容器大小

| Function       | Use                                   |
| -------------- | ------------------------------------- |
| c.resize(n)    | 调整 `c` 的大小为 `n`                 |
| c.resize(n, t) | 调整 `c` 的大小为 `n`，且初始值为 `t` |



### 3.6 **容器操作可能是迭代器失效**

向容器中添加元素

- 容器为 `vector` / `string` 
  - 存储空间重新分配：指向容器的迭代器、指针、引用都会失效
  - 存储空间未分配：插入之前的元素的迭代器、指针、引用有效，插入位置之后的元素失效
- 容器为 `deque`
  - 在首尾插入：迭代器失效，指向存在的元素的指针引用不失效
  - 在首尾以外的：迭代器，指针/引用都失效
- 容器为 `list` / `forward_list`
  - 指向容器的迭代器，指针/引用有效

在容器中删除元素

- 容器为 `list`/`forward_list`
  - 指向容器其他位置的迭代器，指针/引用有效
- 容器为 `deque`
  - 在首尾以外的：迭代器，指针/引用都失效
  - 删除尾部：尾后迭代器失效，指向存在的元素的指针引用不失效
  - 删除头部：不受影响
- 容器为 `vector` / `string` 
  - 指向被删元素之前的元素的迭代器，指针/引用仍有效

> 每次改变容器操作后，都需要正确的重新定位迭代器。



## 4  `vector` 增长

&emsp;&emsp;`vector` 是顺序存储，必须是连续的，但实际中比 `list` 和 `deque` 还要快，因为采取了减少容器重新分配的策略，当不得不获取新的内存空间时， `vector` 和 `string` 通常会分配比新空间需求更大的内存空间。

主要有以下几个函数：

- c.shrink_to_fit()：将 capatity() 减少至与 size() 相同
- c.capacity()：不重新分配空间， c 能存储多少元素
- c.reserve()：分配至少能容纳 `n` 个元素的空间



### 4.1 `capatity` 与 `size`

```C++
vector<int> ivec;

cout << "ivec: size: " << ivec.size()											// 0
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 0

for (auto ix=0; ix != 24; ++ix)
  	ivec.push_back(ix);

cout << "ivec: size: " << ivec.size()											// 24
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 32

ivec.reserve(50);
cout << "ivec: size: " << ivec.size()											// 24
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 50

while (ivec.size() != ivec.capacity())
  	ivec.push_back(0);
cout << "ivec: size: " << ivec.size()											// 50
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 50

ivec.push_back(42);
cout << "ivec: size: " << ivec.size()											// 51
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 100

ivec.shrink_to_fit();
cout << "ivec: size: " << ivec.size()											// 51
  	 << "ivec: capacity: " << ivec.capacity() << endl;		// 
```

​	

## 5 `string` 的其他操作

&emsp;&emsp;除了顺序容器的共同操作外， `string` 还提供额外的操作

- `string` 与 `C` 风格字符的转换
- 下标代替迭代版本



### 5.1 构造 `string` 的其他方法

| Function             | Use                                            |
| -------------------- | ---------------------------------------------- |
| string s(cp, n)      | `s` 是 `cp` 的前`n` 个字符的拷贝               |
| string s(cp, pos)    | `s` 是 `cp` 的`pos` 到结束的字符拷贝           |
| string s(cp, pos, n) | `s` 是 `cp` 从 `pos` 到之后的 `n` 个字符的拷贝 |

```C++
const char* cp = "Hello World!!!";
char noNull[] = {'H', 'i'};

string s1(cp);
string s2(noNull, 2);
string s3(noNull);		// 错误，noNull不是以空字符结尾

string s4(cp + 6, 5);
string s5(s1, 6, 5);

string s6(s1, 6);
string s7(s1, 6, 20);

string s8(s1, 16);		// 错误， out_of_range
```



| Function         | Use                                  |
| ---------------- | ------------------------------------ |
| s.substr(pos, n) | 返回从 `pos` 到之后 `n` 个字符的拷贝 |

```C++
string s("Hello World");
string s2 = s.substr(0, 5);		// Hello
string s3 = s.substr(6);			// World
string s4 = s.substr(6, 11);	// World
string s5 = s.substr(12);			// 错误， out_of_range
```



### 5.2 改变 `string` 的其他方法

P363 表9.13



## 6 容器适配器

三种容器适配器：`stack` `queue` `priority_queue`



### 6.1 初始化一个适配器

1. 容器的构造函数拷贝该容器来初始化适配器

```C++
stack<int> stk(deq);
```

2. 将命名的容器作为第二参数

```C++
stack<string, vector<string>> str_stk;
stack<string, vector<string>> str_stk(svec);
```



对于给定的适配器，使用哪些容器是有限制的：

- 适配器具有添加和删除的能力，因此 `array`， `forward_list` 不能用于构造适配器
- `stack` 操作 ：`push_back` `pop_back` `back` ，除 `array` 和 `forward_list` 都可以构造
- `queue` 操作：`back` `push_back` `front` ，`list` 和 `deque` 可用于构造
- `priority_queue` 操作：`front` `push_back` `pop_back` ，`vector` 和 `deque` 可用于构造



### 6.2 栈适配器

`stack` 默认基于 `deque` 实现，也可在 `vector` 和 `list` 上实现

```C++
#include <stack>

stack<int> intstack;

for (size_t ix=0; ix != 10; ++ix)
  	intstack.push(ix);
while(!intstack.empty()){
  	int value = intstack.top();
  	intstack.pop();
}
```



### 6.3 队列适配器

 `queue` 和 `priority_queue` 定义在 `queue` 头文件中。

`queue` 默认基于 `deque` 实现，priority_queue 默认基于 `vector` 实现。











