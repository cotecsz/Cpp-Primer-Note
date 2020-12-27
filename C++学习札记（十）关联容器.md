# C++学习札记（十）关联容器

[TOC]

&emsp;&emsp; 关联容器支持高效的访问和查找操作，两个主要的关联容器为 **`map`** 和 **`set`** 。标准库提供 8 个关联容器，体现在三个不同维度：

- map / set
- 要求不重复关键字，或允许重复关键字 `multi`
- 顺序保存，或无序保存 `unordered`

| Container Type     | User                                |
| ------------------ | ----------------------------------- |
| map                | 关联数组，保存键值对                |
| set                | 关键字即值，即保存关键字的容器      |
| multimap           | 关键字可重复出现的 `map`            |
| multiset           | 关键字可重复出现的 `set`            |
| unordered_map      | 用哈希函数组织的 `map`              |
| unordered_set      | 用哈希函数组织的 `set`              |
| unordered_multimap | 哈希组织的 `map` ；关键字可重复出现 |
| unordered_multiset | 哈希组织的 `set` ；关系字可重复出现 |



## 1 使用关联容器

1. 单词计数程序

```C++
map<string, size_t> word_count;

string word;
while (cin >> word)
  	++word_count[word];

for (const auto &w : word_count)
  	cout << w.first << " occurs " << w.second
  			 << ((w.second > 1) ? "times" : "time") << endl;
```



2. 单词计数程序，忽略常见单词

````C++
map<string, size_t> word_count;
set<string> exclude = {"The", "But", "And", "Or", "An", "A", 
                       "the", "but", "and", "or", "an", "a"};

string word;
while (cin >> word){
  	if (exclude.find(word) == exclude.end())
      	++word_count[word];

}

for (const auto &w : word_count)
  	cout << w.first << " occurs " << w.second
  			 << ((w.second > 1) ? " times" : "time ") << endl;
````



## 2 关联容器概述

### 2.1 定义关联容器

```C++
map<string, size_t> word_count;
set<string> exclude = {"The", "But", "And", "Or", "An", "A", 
                       "the", "but", "and", "or", "an", "a"};

map<string, string> authors = {{"Jordan", "James"},
                               {"Austen", "Jane"},
                               {"Dickens", "Charles"}};
```



### 2.2 关键字类型要求

### 2.3 `pair` 类型



## 3 关联容器操作

关联容器的表示容器的关键字和值的类型

| Type        | Use                                                          |
| ----------- | ------------------------------------------------------------ |
| key_type    | 此容器类型的关键字类型                                       |
| mapped_type | 每个关键字关联的类型；只适用于 `map`                         |
| value_type  | 对于 `set` ，与 `key_type` 相同；<br />对于 `map` ，为 `pair<const key_type, mapped type>` |



### 3.1 关联容器迭代器

- 对于 `map` ，`value_type` 是一个 `pair` 类型
- 对于 `set` ，关键字也是 `const` 类型，迭代器也是 `const` 类型

1. `map` 操作

```C++
auto map_it = word_count.begin();
cout << map_it->first;
cout << ": " << map_it->second;

map_it->first = "new key";			// 错误， 关键字是 const 类型
++map_it->second;
```



2. `set` 操作

```C++
set<int> iset = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
set<int>::iterator set_it = iset.begin();
if (set_it != iset.end()){
  	*set_it = 42;						// 错误，set 关键字为 const 类型
  	cout << *set_it << endl;
}
```



3. 遍历操作

```C++
auto map_it = word_count.cbegin();

while (map_it != word_count.cend()){
  	cout << map_it->first << " occurs " 
         << map_it->second << " times " << endl;
  	++map_it;
}
```



### 3.2 添加元素

1. `set` 插入元素

```C++
vector<int> ivec = {2, 4, 6, 8};
set<int> set2;

set.insert(ivec.cbegin(), ivec.cend());
set2.insert({1, 3, 5, 7, 1, 3, 5, 7});	// set 中有8 个元素
```



2. `map` 插入元素

```C++
word_count.insert({word, 1});
word_count.insert(make_pair{word, 1});
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(map<string, size_t>::value_type(word, 1));
```



关联容器的 `insert` 操作

| Function                               | Use                                                          | Return                                                 |
| -------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------ |
| c.insert(v)<br />c.emplace(args)       | `v` 是`value_type` 类型的对象，`args` 用于构造一个元素       | 返回 `pair` 类型，迭代器和指示是否插入成功的 `bool` 值 |
| c.insert(b, e)<br />c.insert(il)       | `b` `e` 是迭代器，表示 `c::value_type` 类型的范围，`il` 为花括号列表 | `void`                                                 |
| c.insert(p, v)<br />c.emplace(p, args) | 类似 `c.insert(v)` ，但将 迭代器 `p` 从哪里开始搜索新元素插入的位置 | 返回 迭代器，指向具有给定关键字元素                    |



### 3.3 删除元素

关联容器的 `erase` 操作

| Function      | Use                              | Return                                  |
| ------------- | -------------------------------- | --------------------------------------- |
| c.erase(k)    | 从 `c` 中删除关键字为 `k` 的元素 | 返回删除元素的数量， 类型为 `size_type` |
| c.erase(p)    | 从 `c` 中删除 `p` 指向的元素     | 返回 `p` 之后的元素                     |
| c.erase(b, e) | 返回 `b` `e` 范围内的元素        | 返回 `e`                                |



### 3.4 `map` 的下标操作

- 对 `map` 进行下标操作，返回 `mapped_type` 对象
- 当解引用一个 `map` 迭代器，会得到一个 `value_type` 对象

| Function | Use                                                  |
| -------- | ---------------------------------------------------- |
| c[k]     | 返回关键字为 `k` 的元素，如果不在 `c` 中则添加改元素 |
| c.at(k)  | 访问关键字为 `k` 的元素，带参数检查                  |



### 3.5 访问元素

| Function         | Use                                                     |
| ---------------- | ------------------------------------------------------- |
| c.find(k)        | 返回第一个指向 `k` 元素的迭代器，若不存在，返回尾迭代器 |
| c.count(k)       | 返回关键字等于 `k` 的元素数量                           |
| c.low_bound(k)   | 返回第一个关键字 不小于 `k` 的元素的迭代器              |
| c.upper_bound(k) | 返回第一个关键字大于 `k` 元素的迭代器                   |
| c.equal_range(k) | 返回一个迭代器 `pair` ，表示关键字等于 `k` 的范围       |



- 对 `map` 使用`find` 代替下标操作
- 在 `multimap` 和 `multiset` 中查找元素，可以得到序列中所有具有给定关键字的元素































