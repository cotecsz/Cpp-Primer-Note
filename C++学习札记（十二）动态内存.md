

# C++学习札记（十二）动态内存

[TOC]

&emsp;&emsp;在之前编写的程序中，对象有严格定义的生存周期：

- 全局对象在程序启动时分配，在程序结束时销毁
- 局部自动对象，在定义所在的程序块时被创建，在离开块时被销毁
- 局部静态对象，在第一次使用前被创建，在程序结束时被销毁

也仅仅使用过静态内存和栈内存：

- 静态内存：局部 `static` 对象，类`static` 数据成员，定义在函数外的变量
- 栈内存：定义在函数内的非 `static` 对象

&emsp;&emsp;除静态内存和栈内存，每个程序还拥有一个内存池存储动态分配的对象，称为`自由空间` / **`堆`** 。



## 1 动态内存与智能指针

- `C++` 中动态内存通过一对运算符来完成：`new` 在动态内存中分配空间并返回指向该对象的指针，`delete` 接受一个动态对象指针，销毁该对象，释放与之关联的内存。
- 两种智能指针：
  - `shared_ptr` ：允许多个指针指向同一个对象
  - `unique_ptr` ："独占"所指向的对象
- 标准库还定义了 `weak_ptr` 伴随类，是一种弱引用，指向 `shared_ptr` 所指向的对象



### 1.1 `shared_ptr` 类

1. 智能指针也是模版，与`vector` 一样定义

```C++
shared_ptr<string> p1;
shared_ptr<list<int>> p2;
```



2. 与普通指针一样，解引用返回其指向的对象

```C++
if (p1 & p1->empty())
  	*p1 = "hi";
```



`shared_ptr` 和 `unique_ptr` 都支持的操作：定义，判断，解引用，获取成员，获取对象，交换

| Function                                 | Use                                                   |
| ---------------------------------------- | ----------------------------------------------------- |
| shared_ptr\<T> sp<br />unique_ptr\<T> up | 空智能指针，可以指向类型为 `T` 的对象                 |
| p                                        | 将 `p` 用作条件判断，若 `p` 指向一个对象，则为 `true` |
| *p                                       | 解引用 `p` ，获得它所指向的对象                       |
| p->mem                                   | 等价于 `*p.mem`                                       |
| p.get()                                  | 返回 `p` 中保存的指针                                 |
| swap(p, q)<br />p.swap(q)                | 交换 `p` 和 `q` 中的指针                              |



`shared_ptr` 独有的操作：初始化，拷贝

| Function                | Use                                                          |
| ----------------------- | ------------------------------------------------------------ |
| make_shared\<T>*(args)* | 返回一个 `shared_ptr` 指针，指向动态分配类型为 `T`  使用 `args` 初始化的对象 |
| shared_ptr\<T>p(q)      | `p` 是 `shared_ptr q` 的拷贝，此操作会递增`q` 中计数器， `q` 中指针能转换为 `T*` |
| p = q                   | `p` 和 `q` 都为 `shared_ptr` ，此操作会递减 `p` 的引用指数，递增 `q` 引用指数，`p` 递减为0，则释放内存 |
| p.unique()              | 若 `p.use_count()` 为 1，返回 `true` ，否则返回 `false`      |
| p.use_count()           | 返回 `p` 共享对象的智能指针数量，可能很慢，用于调试          |



#### 1.1.1 `make_shared` 函数

1. 定义方式与模版类相同

```C++
shared_ptr<int> p3 = make_shared<int>(42);		// 指向 值为42的 int
shared_ptr<string> p4 = make_shared<string>(10, 'h');	// 指向 值为 'hhhhhhhhh' 的string
shared_ptr<int> p5 = make_shared<int>();			// 指向值初始化为0的 int
```



2. 使用 `auto` 较为简单

```C++
auto p6 = make_shared<vector<string>>();	// 指向动态分配的 vector<string>
```



#### 1.1.2 `shared_ptr` 拷贝与赋值

&emsp;&emsp; 当进行拷贝和赋值时，`shared_ptr` 都会记录有多少其他的 `shared_ptr` 指向相同的对象，该关联的计数器称为 **`引用计数`** 。

```C++
auto p = make_shared<int>(42);
auto q = p;
```

当计数器变为 0 时，会自动释放自己所管理的对象。

```C++
auto r = make_shared<int>(42);
r = q;			// 1. 令它指向另一个地址
						// 2. 递增 q 所指向的对象的引用计数
						// 3. 递减 r 原来指向的对象的引用计数
						// 4. r 原来指向的对象已没有饮用者，会自动释放
```



#### 1.1.3 `shared_ptr` 会自动释放相关联的内存

1. 返回 一个 `shared_ptr` 

```C++
shared_ptr<Foo> factory(T args){
  	// 处理 args
  	
  	return make_shared<Foo>(args);
}
```



2. 当 `p` 销毁时，会检测是否为 0

```C++
void use_factory(T arg){
  	shared_ptr<Foo> p = factory(args);
  	// 使用 p
}	// p 离开作用域，所指向的内存将会被释放
```



3. 返回 `p` 的拷贝

```C++
void use_factory(T args){
  	shared_ptr<Foo> p = factory(args);
  	// 使用 p
  	return p;		// 返回 p 的拷贝，引用计数 + 1
}	// p 离开作用域，但所指向的内存不会被释放
```



>如果将 `shared_ptr` 存放在一个容器中，当不再需要全部元素时，记得使用 `erase` 删除不再需要的元素。



#### 1.1.4 使用了动态生存期的资源的类

程序使用动态内存的三个原因：

1. 程序不知道使用多少对象，如 `容器类`
2. 程序不知道使用对象的准确类型
3. 程序需要在多个多个对象间共享数据

> 使用动态内存的一个常见原因是允许多个对象共享相同的状态。



#### 1.1.5 `StrBlob` 类

```C++
class StrBlob{
public:
  	typedef std::vector<std::string>::size_type size_type;
  	StrBlob();
  	StrBlob(std::initializer_list<std::string> il);
  	size_type size() const {return data->size();}
  	bool empty() const {return data->empyt();}
  	void push_back(const std::string &t) {data->push_back(t);}
  	void pop_back();
  	std::string &front();
  	std::string &back();

private:
  	std::shared_ptr<std::vector<std::string>> data;
  	void check(size_type i, const std::string &msg) const;
}
```



构造函数

```C++
StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initlizer_list<string> il):
								data(make_shared<vector<string>>(il)){}
```



元素访问成员函数

```C++
void StrBlob::check(size_type i, const string &msg) const{
  	if (i >= data->size())
      	throw out_of_range(msg);
}

string& StrBlob::front(){
  	check(0, "front on empty StrBlob");
  	return data->front();
}

string& StrBlob::back(){
  	check(0, "back on empty StrBlob");
  	return data->back();
}

void StrBlob::pop_back(){
  	check(0, "pop_back on empty StrBlob");
  	return data->pop_back();
}
```



### 1.2 直接管理内存

#### 1.2.1 使用 `new` 动态分配和初始化对象

&emsp;&emsp;默认情况下，动态分配的对象是默认初始化的：

- 内置类型/组合类型的对象值是未定义的
- 类类型对象将用默认构造函数进行初始化

```C++
int *pi = new int;		// pi 指向动态分配的，未初始化的无名对象
string *ps = new string;	// 初始化为 空string
```



初始化方法：

- 默认为默认初始化
- 值初始化
- 列表初始化

```C++
// 默认初始化
string *ps = new string;
int *pi = new int;

// 2. 值初始化
int *pi = new int(1024);
int *string = new string(10, 'h');

// 3. 列表初始化
vector<int> *pv = new vector<int>{0, 1, 2, 4, 5, 6, 7, 8, 9};

// 4. auto: 当且仅当括号中有一个初始化器
auto p1 = new auto(obj);
```

> 对动态分配的对象进行初始化通常是个好主意。



#### 1.2.2 动态分配 `const`对象

```C++
const int *pi = new const int(1024);
const string *ps = new const string;
```



#### 1.2.3 内存耗尽

```C++
#include <
int *p1 = new int;
int *p2 = new (nothrow) int;
```



#### 1.2.4 释放动态内存

```C++
delete p;		//	p必须指向一个动态分配的对象/空指针
						//  delete的两个动作：1. 销毁给定指针指向的对象  2. 释放对应的内存
```



#### 1.2.5 指针值和 `delete`

```C++
int i, *pi1 = &i, *pi2 = nullptr;
double *pd = new double(33), *pd2 = pd;
const int *pci = new const int(1024);

delete i;			// 错误，i 不是指针
delete pi1;		// 未定义：pil 指向一个局部变量
delete pd;		// 正确
delete pd2;		// 未定义，pd2 指向的内存已经被释放
delete pi2;		// 正确
delete pci;		// 正确，释放一个 const 对象
```



#### 1.2.6 动态对象的生存期直到被释放为止

```C++
Foo* factory(T arg){
  	// 处理 args
  	return new Foo(arg);
}

void use_factory(T arg){
  	Foo *p = factory(arg);
}// 局部变量离开作用域，则被销毁，但动态内存无法释放
```



> 使用 `new` 和 `delete` 管理内存的三个常见问题：
>
> 1. 忘记 `delete` 动态分配的内存导致的内存泄漏
> 2. 使用已释放掉的内存
> 3. 同一块内存释放两次
>
> 使用智能指针可以避免以上这些问题，对于同一块内存，没有在任何智能指针指向的情况下，智能指针才会自动释放。



#### 1.2.7 `delete` 之后要重置指针

**空悬指针** ：在 `delete` 之后，指针为空悬指针，即指向一块曾经保存数据但现在已经无效的内存的指针。

解决方案：

1.  在指针即将离开作用域之前，释放掉它所关联的内存
2. 如果需要保留指针，则在释放内存后，将指针赋予 `nullptr` 



### 1.3 `shared_ptr` 与 `new` 结合使用

- 可以使用直接初始化方式初始化一个智能指针

```C++
shared_ptr<int> p1 = new int(42);		// 错误，必须使用直接初始化方式
shared_ptr<int> p2(new int(1024));	// 正确
```



定义和改变 `shared_ptr` 的其他方法

| Function                | Use                                                          |
| ----------------------- | ------------------------------------------------------------ |
| shared_ptr\<T> p(q)     | `p` 管理内置指针 `q` 所指向的对象；`q` 必须为 `new` 分配的内存且可转换为`T*` |
| shared_ptr\<T> p(u)     | `p` 从 `unique_ptr u` 那里接管对象的所有权，将 `u` 置为空    |
| shared_ptr\<T> p(q, d)  | `p` 接管内置指针 `q` 所指向的对象的所有权，`p` 使用可调用对象 `d` 代替 `delete` |
| shared_ptr\<T> p(p2, d) | `p` 是 `shared_ptr p2` 的拷贝，唯一区别为 `p` 调用 `d` 代替 `delete` |
| p.reset()               | 释放对象                                                     |
| p.reset(q)              | 令 `p` 指向 `q`                                              |
| p.reset(q, d)           | `p` 调用 `d` 代替 `delete`                                   |



#### 1.3.1 不能混合使用普通指针和智能指针

1. 普通指针转换为智能指针

```C++
void process(shared_ptr<int> ptr){
  	//...
}// ptr 离开作用域被销毁

int *x(new int(1024));
process(x);			// 错误，不能将 int* 转换为 shared_ptr<int>
process(shared_ptr<int>(x));		// 当process 结束，会释放 x 所指向的内存
int j = *x;			// 未定义：x 是空悬指针
```



2. 智能指针转换为普通指针

```C++
shared_ptr<int> p(new int(42));
int *q = p.get();		// 正确：但使用时需注意，不要让它管理的指针被释放
{
  	shared_ptr<int> (q);
}		// 程序块结束，则释放q 所指向的内存
int foo = *p;	//未定义：p 所指向的内存已经被释放
```



#### 1.3.2 其他 `shared_ptr` 操作

1. 将新的指针赋予 一个 `shared_ptr`

```C++
p = new int(42);		// 错误：不能讲一个指针赋予 shared_ptr
p.reset(new int(1024));	// 正确：p 指向一个新对象
```



2. 与 `uniqye` 一起使用，控制共享对象

```C++
if (!q.unique())
  	p.reset(new string(*p));		//	如果我们不是唯一的用户，则重新分配新的拷贝
*p += newVal;				// 唯一用户，可进行修改
```



### 1.4 智能指针和异常

- 智能指针在程序正常结束/ 发生异常都会被释放内存
- `new` 开辟的内存，在 `new` 与 `delete` 发生异常时，内存将无法释放



#### 1.4.1 智能指针与哑类

```C++
struct destination;
struct connection;
connection connect(destination* );
void disconnect(connection);

void f(destination& d){
  	connnection c = connect(destination);
  	// 使用连接
  	// 在退出前没有 disconnect ,就无法关闭连接了
}
```



在这种情况下，与 `new` 分配的动态内存类似，在发生异常 / 程序没有调用 `disconnect` 时，程序无法关闭连接。那么可以使用 `shared_ptr` 并给定 `deleter` 来管理关闭操作。

```C++
void f(destionation& d){
  	connection c = connect(&d);
  	shared_ptr<connect> p(&c, end_connection);
  	// 使用连接
  	// 在 f退出/ 发生异常时，connection 会被正确关闭
}
```



> 智能指针陷阱
>
> 1. 不使用相同的内置指针初始化(或 `reset` ) 多个智能指针
> 2. 不 `delete` `get()`  返回的指针
> 3. 不使用 `get()` 初始化或 `reset` 令一个智能指针
> 4. 如果使用了 `get()` 返回的指针，当最后一个智能指针销毁后，指针就无效了
> 5. 如果使用智能指针管理的资源不是 `new` 分配的资源，记得传递给它一个 `deleter`



### 1.5 `unique_ptr`

- 定义时，需要绑定到 `new` 返回的指针上，必须直接初始化
- 不支持普通的拷贝和赋值操作

```C++
unique_ptr<double> p1;
unique_ptr<int> p2(new int(42));

unique_ptr<string> ps(new string("hello"));
unique_ptr<string> ps2(ps);		// 错误：unique_ptr 不支持拷贝
unique_ptr<string> ps3;
ps3 = ps;											// 错误：unique_ptr 不支持赋值
```



可以通过 `release` / `reset` 将指针所有权从一个 (非 `const` )  `unique_ptr` 转移至另一个

```C++
unique_ptr<string> p2(p1.release());
unique_ptr<string> p3(new string("hello"));
p2.reset(p3.release());

p2.release();			// 错误：p2 不会释放内存，而且丢失指针
auto p = p2.release();	// 正确：但必须记得 delete(p);
```



`unique_ptr` 操作

| Function                                    | Use                                                          |
| ------------------------------------------- | ------------------------------------------------------------ |
| unique_ptr\<T> u1<br />unique_ptr\<T, D> u2 | 定义 空的 `unique_ptr` ，默认使用 `delete`，`u2` 使用类型为 `D`  的可调用对象释放对象 |
| unique_ptr\<T, D> u(d)                      | 空 `unique_ptr` ，指向类型为 `T` 的对象，用类型为 `D` 的对象 `d` 代替 `delete` |
| u = nullptr                                 | 释放 `u` 指向的对象，将 `u` 置为空                           |
| u.release()                                 | `u` 放弃对指针的控制权，返回指针，并将 `u` 置为空            |
| u.reset()                                   | 释放 `u` 指向的对象                                          |
| u.reset(q)<br />u.reset(nullptr)            | 如果提供内置对象，则令 `u` 指向该对象，否则将 `u` 置为空     |



#### 1.5.1 传递 `unique_ptr` 和 返回 `unique_ptr` 

不能拷贝 `unique_ptr` 的一个例外：将要销毁的 `unique_ptr` 可以拷贝和赋值

```C++
unique_ptr<int> clone(int p){
  	// 正确，从 int* 创建一个 unique_ptr
  	return unique_ptr<int> (new int(p));
}

// 返回局部对象的拷贝
unique_ptr<int> clone(int p){
  	unique_ptr<int> ret(new int(p));
  	// ... 
  	return ret;
}
```



#### 1.5.2 向 `unique_ptr` 传递 删除器

```C++
unique_ptr<objT, delT> p(new objT, fcn);
```

```C++
void f(destination &d){
  	connection c = connect(&d);
  	unique_ptr<connection, decltype(end_connection)*> 
      	p(&c, end_connection);
  	// 使用连接
  	// 在 f退出 / 发生异常时，connection 会被正确关闭
}
```



### 1.6 `weak_ptr` 

&emsp;&emsp; `weak_ptr` 指向一个 `shared_ptr` 管理的对象，但不会改变 其引用计数，一旦 `shared_ptr` 被销毁，对象就会被释放。

| Function           | Use                                                          |
| ------------------ | ------------------------------------------------------------ |
| weak_ptr\<T> w     | 空 `weak_ptr`                                                |
| weak_ptr\<T> w(sp) | 与 `shared_ptr` 指向相同的对象                               |
| w = p              | `p` 可以是`shared_ptr` / `weak_ptr` ，赋之后 `w` 和 `p` 共享对象 |
| w.reset()          | 将 `w` 置为空                                                |
| w.use_count()      | 与 `w` 共享的 `shared_ptr` 的数量                            |
| w.expired()        | 若 `w.use_count=0` 返回 `true` ，否则返回 `false`            |
| w.lock()           | 若 `expired()` 为 `true` ，返回一个空的 `shared_ptr`， 否则返回指向`w` 的`shared_ptr` |

```C++
auto p = shared_ptr<int>(42);
weak_ptr<int> wp(p);		// 弱共享 p，p 的引用计数未改变

if (shared_ptr<int> np = wp.lock()){	// np 不为空，条件成立
  	// if 中，np 与 wp 共享对象
}
```



## 2 动态数组

容器在重新分配内存时，必须一次性为很多元素分配内存：

1. `new` 表达式
2. 标准库中的 `allocator` 类



### 2.1 `new` 和数组

1. 调用 `get_size` , 方括号中必须是整数，但不必是常量

```C++
int *pia = new int[get_size()];
```



2. 使用类型别名

```C++
using arrT = int[42];
typedef int arrT[42];

int *p = new arrT;
```



> 分配数组内存会得到一个元素类型的指针，动态数组并不是数组类型。



#### 2.1.1 初始化动态分配对象的数组

1. 值初始化

```C++
int *pia = new int[10];			// 10 个未初始化的 int
int *pia2 = new int[10]();	// 10 个初始化为 0 的int

int *psa = new string[10];		// 10个空string
int *psa2 = new string[10](); // 10个空string
```



2. 列表初始化

```C++
int *pia3 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
string *psa3 = new string[10]{"a", "an", "the", string(3, "x")};
```



#### 2.1.2 分配一个空数组是合法的

```C++
size_t = get_size();
int *p = new int[n];
for (int *q = p; q != p+n; ++q)
  	// ... 
  
char arr[0];		// 错误：不能定义长度为 0 的数组
char *cp = new char[0];	// 正确：但cp 不能解引用
```



#### 2.1.3 释放动态数组

```C++
delete p;
delete[] pa;
```



#### 2.1.4 智能指针与动态数组

1. `unique_ptr` 管理动态数组

```C++
unique_ptr<int[]> up(new int[10]);
up.release();			// 自动调用 delete[] 销毁其指针

for (size_t i = 0; i != 10; ++i)
  	up[i] = i;
```



2. `shared_ptr` 不直接支持，但可以通过提供自己的 `deleter`

```C++
shared_ptr<int> sp (new int[10], [](int* p){delete[] p;});
sp.reset();

for (size_t i = 0; i != 10; ++i)
  	*(sp.get() + i) = i;
```



### 2.2 `allocator` 类

```C++
#include <memory>
allocator<string> alloc;
auto const p = alloc.allocator(n);	// 分配 n 个未初始化的 string
```



标准库 `allocator` 类及其算法

| Function               | Use                                                          |
| ---------------------- | ------------------------------------------------------------ |
| allocator\<T> a        | 定义一个 名为 `a` 的 `allocator` 对象，可以为 类型 `T` 分配内存 |
| a.allocator(n)         | 分配一段原始的，未构造的内存，保存 `n` 个 `T` 对象           |
| a.deallocator(p, n)    | 释放从 `T*` 指针 `p` 开始的内存，内存中的 `n` 个 `T` 对象，在调用前，必须将 创建的每个对象调用 `destroy` |
| a.construct(p, *args*) | `p` 是一段原始的内存，*args* 传递为 `T` 的构造函数参数       |
| a.destory(p)           | 对 `p` 指向的函数的析构函数                                  |



#### 2.2.1 `allocator` 分配未构造的内存

1. 构造对象

```C++
auto p = q;
alloc.construct(q++);						// *q 为空字符串
alloc.construct(q++, 10, 'c');	// *q 为 'cccccccccc'
alloc.construct(q++, "hi");			// *q 为 hi

cout << *p << endl;			// 正确：使用 string 的输出运算符
cout << *q << endl;			// 灾难：q 指向未构造的内存
```



2. 销毁对象

```C++
while(q != p)
  	alloc.destory(--q);
```



3. 释放内存

```C++
alloc.deallocate(p, n);
```



#### 2.2.2 拷贝和填充未初始化的算法

| Function                       | Use                                                          |
| ------------------------------ | ------------------------------------------------------------ |
| uninitialized_copy(b, e, b2)   | 将迭代器范围 `b` `e` 中的元素拷贝至 `b2`                     |
| uninitialized_copy_n(b, n, b2) | 从迭代器`b` 指向的元素开始，拷贝 `n` 个元素至 `b2` 开始的内存 |
| uninitialized_fill(b, e, t)    | 将迭代器范围 `b` `e` 创建对象，对象的值为 `t` 的拷贝         |
| uninitialized_fill_n(b, n, t)  | 从迭代器`b` 指向的元素开始，拷贝 `n` 个值为 `t` 的元素       |



```C++
auto p = alloc.allocate(vi.size()*2);
auto q = uninitialized_copy(vi.begin(), vi.end(), p);
uninitialized_fill_n(q, vi.size(), 42);
```





















