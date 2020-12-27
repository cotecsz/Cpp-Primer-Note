# C++学习札记（十三）拷贝控制

[TOC]

&emsp;&emsp;在定义一个类时，会显式/隐式的定义在此类型的对象的拷贝、移动、赋值和销毁操作。类通过五个特殊的成员函数定义：

- 拷贝构造函数
- 拷贝赋值函数
- 移动构造函数
- 移动赋值函数
- 析构函数



## 1 拷贝 赋值与销毁

### 1.1 拷贝构造函数

&emsp;&emsp;拷贝构造函数的第一个参数是自身类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数

```C++
class Foo{
public:
  	Foo();						// 默认构造函数
  	Foo(const Foo&);	// 拷贝构造函数
};
```



#### 1.1.1 合成拷贝构造函数

&emsp;&emsp; 在类中没有定义 `合成拷贝构造函数` ，编译器会为我们定义一个，对于某些类，**合成拷贝构造函数** 用来阻止拷贝该类型的对象，在一般情况，会将参数的成员（非 `static` 对象）逐个拷贝到正在创建的对象中。

```C++
class Sales_data{
public:
  	Sales_data(const Sales_data&);
};

Sales_data::Sales_data(const Sales_data &orig):
  	bookNo(orig.bookNo),			// 使用 string 的拷贝构造函数
  	units_sold(orign.units_sold),	// 拷贝 orign.units_sold
  	revenue(orign.revenue)		// 拷贝 orign.revenue
    {		}
```



#### 1.1.2 拷贝初始化

直接初始化 v.s. 拷贝初始化

直接初始化：编译器使用函数匹配，选择参数最匹配的构造函数

拷贝初始化：编译器将右侧对象拷贝到正在创建的对象中

```C++
string dots(10, '.');		// 直接初始化
string s(dots);					// 直接初始化
string s2 = dots;				// 拷贝初始化
string null_book = "9-9999-9999";		// 拷贝初始化
string nine = string(100, '9');			// 拷贝初始化
```



拷贝初始化的几种情形：

- `=` 定义变量时
- 将一个对象作为实参传递给一个非引用的形参
- 从返回类型为非引用类型函数返回一个对象
- 用花括号列表初始化一个数组中的元素/ 一个聚合类中的成员

某些类类型对分配对象使用拷贝初始化`insert` 和 `push` ，使用 `emplace` 进行直接初始化。



#### 1.1.3 参数和返回值

拷贝初始化

- 将一个对象作为实参传递给一个非引用的形参
- 从返回类型为非引用类型函数返回一个对象

拷贝构造函数的参数必须是引用类型，如果不是引用类型，则永远不会 成功—— 为了调用拷贝构造函数，必须拷贝实参，为了拷贝实参，调用拷贝构造函数，...



#### 1.1.3 拷贝初始化的限制

如果构造函数是 `explicit` ，则使用拷贝初始化和直接初始化就无关紧要了

```C++
vector<int> v1(10);	// 直接初始化
vector<int> v2 = 10;// 错误：构造函数为 explicit
void f(vector<int>);// 参数构造初始化
f(10);							// 错误，不能用一个 explicit 的构造函数拷贝一个实参
f(vector<int>(10));	// 正确
```



#### 1.1.4 编译器可以绕过拷贝构造函数

在拷贝初始化过程中，编译器可以（但不是必须）跳过拷贝/移动构造函数，直接创建对象。

```C++
string null_book = "9-9999-999";	// 拷贝初始化

// 编译器被允许改写为
string null_book("9-9999-999");		// 略过
```



### 1.2 拷贝赋值运算符

类可以控制其对象如何赋值

```C++
Sales_data trans, accum;
trans = accum;
```



#### 1.2.1 重载赋值运算符

&emsp;&emsp;重载运算符本质为函数

- 函数名：`operator` + `=` （要重载的运算符）
- 参数表示运算符的运算对象
- 返回值

```C++
class Foo{
public:
  	Foo& operator=(const Foo&);
};
```

>  赋值运算符通常应该返回指向左侧运算对象的引用。



#### 1.2.2 合成拷贝赋值函数

&emsp;&emsp; 合成拷贝赋值函数

- 对于某些类，用来禁止该对象的赋值，详见 `1.6`
- 如果不是出于上述目的，将右侧的对象的每个非 `static` 成员赋值左侧对象成员

```C++
// 合成的默认拷贝赋值函数
Sales_data& 
Sales_data::operator=(const Sales_data &rhs){
  	bookNo = rhs.bookNo;			// 调用 string::operator=
  	unit_sold = rhs.unit_sold;// 使用内置 int 赋值
  	revenue = rhs.revenue;		// 使用内置 double 赋值
  	return *this;							// 返回一个此对象的引用
}
```



### 1.3 析构函数

- 构造函数：初始化对象的非 `static` 成员
- 析构函数：释放对象使用的资源，并销毁对象的非 `static` 成员

```C++
class Foo{
  	~Foo();		//析构函数
}
```

> 隐式销毁一个内置指针类型的成员，不会 `delete` 它所指的对象。



#### 1.3.1 什么时候调用析构函数

- 变量离开其作用域被销毁
- 当一个变量被销毁时，成员也被销毁
- 容器被销毁时，其元素被销毁
- 对于动态分配的对象，当指向它的指针应用 `delete` 运算符时被销毁
- 对于临时对象，当创建它的完整表达式结束时被销毁

```C++
{
  	Sales_data *p = new Sales_data;				// p 是一个内置指针
  	auto p2 = make_shared<Sales_data>();	// p2 是一个 shared_ptr 
  	Sales_data item(*p);									// 拷贝构造函数将 *p 拷贝到 item 中
  	vector<Sales_data> vec;								// 局部对象
  	vec.push_back(*p2);										// 拷贝 p2 指向的对象
  	delete p;															// 对 p 指向的对象执行析构函数
}		// 退出局部作用域，对 item p2 vec 调用析构函数
		// 销毁 p2 会递减其引用计数，如果为0，则释放对象
		// 销毁 vec 会销毁其对象
```

> 当指向一个对象的指针/引用离开作用域时，析构函数不会执行。



#### 1.3.2 合成析构函数

合成析构函数：

- 对于某些类，用来阻止该对象被销毁
- 如果不是，合成析构函数为空

```C++
class Sales_data{
public:
  	// ...
  	~Sales_data{}
}
```



### 1.4 三/五法则

#### 1.4.1 需要析构函数的类也需要拷贝和赋值操作

> 如果一个类需要自定义的析构函数，几乎可以肯定它也需要自定义的拷贝赋值运算符和拷贝构造函数。



如果一个类需要拷贝构造函数，几乎可以肯定它需要一个拷贝赋值运算符，反之亦然。



### 1.5 使用 `=default`

- 在类内用 `=default` 修饰成员声明时，合成的函数将隐式地声明为 `inline`
- 在类外，对成员的定义使用 `=default` ，就不是内联函数

```C++
class Sales_data{
public:
  	// 拷贝控制成员使用 default
  	Sales_data() = default;
  	Sales_data(const Sales_data&) = default;
  	Sales_data& operator=(const Sales_data&) = default;
  	~Sales_data() = default;
  	// ...
}
```

> 只能对具有合成版本的成员函数使用 `=default` ，即默认构造函数或拷贝控制成员（拷贝构造函数和拷贝赋值函数）



### 1.6 阻止拷贝

> 大多数类应该定义默认构造函数，拷贝构造函数和拷贝赋值函数，无论是显式还是隐式的。



#### 1.6.1 定义删除函数

&emsp;&emsp;可以通过将拷贝构造函数和拷贝赋值运算符定义为 **被删除的函数** （`delete` 函数）

```C++
struct NoCopy{
  	NoCopy() = default;			// 使用合成默认构造函数
  	NoCopy(const NoCopy &) = delete;							// 阻止拷贝
  	NoCopy &operator=(const NoCopy &) = delete;		// 阻止赋值
  	~NoCopy() = default;		// 使用合成默认析构函数
};
```



#### 1.6.2 析构函数不能是删除的成员

```C++
struct NoDtor{
  	NoDtor() = default;	// 使用合成默认构造函数
  	~NoDtor() = delete;	// 不能销毁 NoDtor 类型的成员
};

NoDtor nd;		// 错误：NoDtor 的析构函数是删除的
NoDtor *p = new NoDtor();	// 正确：但不能 delete p
delete p;			// 错误：NoDtor 的析构函数是删除的
```

> 对于析构函数已删除的类型，不能定义该类型的变量或释放指向该类型动态分配对象的指针。



#### 1.6.3 合成的拷贝控制成员可能是删除的

- 类的某个成员的**析构函数**是删除的或不可访问的（`private` ），类的**合成析构函数**被定义为删除的
- 类的某个成员的**拷贝构造函数**是删除/不可访问的，则类的**拷贝构造函数**是删除的
- 类的某个成员的**析构函数**是删除的或不可访问的，则类的**拷贝构造函数**是删除的
- 类的某个成员的**拷贝赋值运算符**是删除的/不可访问的，或类有一个 `const` 或一个引用成员，则类的**合成拷贝赋值运算符**被定义为删除的
- 类内某个成员的**析构函数**是删除的或不可访问的，或有一个引用成员，没有类内初始化器，或有一个 `const` 成员，没有类内初始化器且类型未显式定义默认构造函数，则该类的**默认构造函数**是删除的

**本质上，这些规则的含义：如果一个类有数据成员不能默认构造、拷贝、复制或销毁，则对应的成员函数将被定义为是删除的。**



#### 1.6.4 `private` 拷贝控制

```C++
class PrivateCopy{
  	// 默认为 private
  	PrivateCopy(const PrivateCopy&);
  	PrivateCopy &operator=(const PrivateCopy&);
public:
  	PrivateCopy() = default;
  	~PrivateCopy() = default;
};
```

> 希望阻止拷贝的类应该使用 `=delete` 来定义它们自己的拷贝构造函数和拷贝赋值运算符，而不应该将其声明为 `private` 的。



## 2 拷贝控制与资源管理

### 2.1 行为像值的类

```C++
class HasPtr { 
public:
		HasPtr(const std::string &s = std::string())
      :ps(new std::string(s)), i(0) { }
		// each HasPtr has its own copy of the string to 
  	// which ps points HasPtr(const HasPtr &p):
		ps(new std::string(*p.ps)), i(p.i) { } 
  	HasPtr& operator=(const HasPtr &); 
  	~HasPtr() { 		delete ps; }
private:
		std::string *ps;
		int i;
};
```



#### 2.1.1 类值拷贝赋值运算符

```C++
HasPtr& HasPtr::operator=(const HasPtr& rhs){
  	auto newp = new string(*rhs.ps);
  	delete ps;
  	ps = newp;
  	i = rhs.i;
  	return *this;	
}
```

> 赋值运算符：
>
> - 如果将一个对象赋值给自己，赋值运算符必须能正常工作
> - 大多数赋值运算符组合了析构函数和拷贝函数的工作



### 2.2 定义行为像指针的类

令一个类展现类似指针的行为最好的方式是使用 `shared_ptr` 来管理类中的资源。



#### 2.2.1 引用计数

- 构造函数创建引用计数，用来记录有多少对象与正在创建的对象共享
- 拷贝构造函数拷贝对象的数据成员，包括计数器
- 析构函数递减计数器
- 拷贝赋值运算符，递增右侧对象的计数器，递减左侧对象的计数器

```C++
class HasPtr { 
public:
		// constructor allocates a new string and a new counter, which it sets to 1 				
  	HasPtr(const std::string &s = std::string()):
						ps(new std::string(s)), i(0), use(new std::size_t(1)){}
		// copy constructor copies all three data members and increments the counter 
  	HasPtr(const HasPtr &p):
						ps(p.ps), i(p.i), use(p.use) { ++*use; } 
  	HasPtr& operator=(const HasPtr&);
		~HasPtr();
private:
	std::string *ps;
  int i; 
  std::size_t *use;
};

HasPtr::~HasPtr(){
  	if (--*use == 0){
      	delete ps;
  			delete use;
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs){
  	++*rhs.use;
  	if (--*use == 0){
      	delete ps;
      	delete use;
    }
  	ps = rhs.ps;
  	i = rhs.i;
  	use = rhs.use;
  	return *this;
}
```



## 3 交换操作



















## 4 拷贝控制示例



## 5 动态内存管理类



## 6 对象移动