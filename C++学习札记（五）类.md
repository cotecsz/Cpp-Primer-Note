# C++学习札记（五）类

[TOC]

&emsp;&emsp;在 C++ 中，可以通过类来定义数据类型。本章阐述数据抽象的重要性，将对象的操作分别实现。基本概念是类是数据抽象和封装。数据抽象是将接口与实现分离的编程技术，接口是用户对类可以执行的操作，实现包含类成员，接口的函数实现和其他类使用而非用户使用的函数。

&emsp;&emsp;封装确保类的接口与实现的分离。类的封装隐藏了其实现，用户可以访问接口但无法查看实现。使用数据抽象与封装定义抽象数据类型。类的设计者关注其如何实现，使用者关注其如何使用。



## 1 定义抽象类型

&emsp;&emsp; `Sale_data` 接口有以下操作：

1. isbn() ：返回对象的 `ISBN`
2. combine()：将 `Sale_data` 对象加到另一个对象上
3. add()：两个 `Sale_data` 相加
4. read()：从一个 `istream` 读取一个 `Sale_data` 对象
5. print()：将一个 `Sale_data` 输出到 `ostream`

### 1.1  `Sales_data` 类

定义 `Sales_data` 结构体：

```C++
struct Sales_data{
  	std::string isbn() const {return bookNo;}
  	Sales_data& combine(const Sales_data&);
  	double avg_price() const;
  
  	std::string bookNo;
  	unsigned unit_sold = 0;
  	double revenue = 0.0;
}

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, const Sales_data&);
```

> 定义在类中的 **函数** 隐式转换为 `inline` 类型。

&emsp;&emsp;类成员函数声明必须在类中，但函数实现可以写在类中，也可以写在类外。

#### 1.1.1 this 指针

&emsp;&emsp; 类成员函数被调用时，会隐式地传递一个 `this` 参数。即在调用成员函数时，`this` 被初始化为对象的地址，如下

```C++
// 声明
Sales_data::isbn(const Sales_data* this);

// 调用
total.isbn();
Sales_data::isbn(&total);

return bookNo;
return this->bookNo;
```



#### 1.1.2  `const` 成员函数

```C++
std::string isbn() const {return bookNo;}
```

&emsp;&emsp; `const` 表示 `this` 指针所指的对象为 常量类型，也被称为 `const 成员函数` ，如下

```C++
Sales_data::std::string isbn(const Sales_data* const this)	{return this->bookNo;}
```



#### 1.1.3 在类外定义成员函数

```C++
double Sales_data::avg_price()const {
  	if (units_sold)
      	return revenue / unit_sold;
  	else
      	return 0;
}
```



#### 1.1.4 定义一个返回 "this" 对象

```C++
Sales_data& Sales_data::combine(const Sales_data rhs){
  	unit_sold += rhs.unit_sold;
  	revenue += rhs.revenue;
  	return *this;
}
```



### 1.2 定义与类相关的非成员函数

&emsp;&emsp; 非成员函数也是类接口的一部分，定义在类的头文件中。

#### 1.2.1 定义 `read` 和 `print`

```C++
istream &read(istream &is, Sales_data &item){
  	double price = 0;
  	is >> item.bookNo >> item.units_sold >> price;
  	item.revenue = price * item.units_sold;
  	return is;
}

ostream &print(ostream &os, Sales_data &item){
  	os << item.isbn() << " " << item.units_sold << " " 
       << item.revenue << " " << item.avg_price();
  	reutrn os;
}
```



#### 1.2.2 定义 `add`

```C++
Sales_data add(const Sales_data &lhs, const Sales-data &rhs){
  	Sales_data sum = lhs;
  	sum.combine(rhs);
  	return sum;
}
```



### 1.3 构造函数

&emsp;&emsp;构造函数在对象被创建时运行，用于初始化函数的成员变量。构造函数有如下特点：

1. 与类名相同
2. 参数列表可为空
3. 可以重载
4. 不能声明为 `const` 



#### 1.3.1 合成默认构造函数

&emsp;&emsp;在没有定义构造函数时，编译器会隐式定义一个构造函数， 称为 **合成默认构造函数** (synthesized default constructor)。



#### 1.3.2 无法使用合成默认构造函数

1. 类中定义构造函数
2. 无法正确初始化
3. 类中含有其他类且该类没有构造函数



#### 1.3.3 定义 `Sales_data` 的构造函数

&emsp;&emsp; 定义 4 种 构造函数

```C++
struct Sales_data{
  	Sales_data() = default;
  	Sales_data(const string s): bookNo(s){ }
  	Sales_data(const string s, unsigned n, double p):
  							bookNo(s), unit_sold(n), revenue(p*n){ }
  	Sales_data(std::istream&);
  
  	std::string isbn() const {return bookNo;}
  	Sales_data& combine(const Sales_data&);
  	double avg_price() const;
  
  	std::string bookNo;
  	unsigned unit_sold = 0;
  	double revenue = 0.0;
}
```

#####  `=default` 

```C++
Sales_data() = default;
```

&emsp;&emsp; `=default` 表示与默认构造函数相同。

> 这里使用默认构造函数是由于内置类型提供初始值，当类内成员没有初始值，应该使用初始化列表初始化。



##### 构造初始化列表

```C++
Sales_data(const string s): bookNo(s){ }
Sales_data(const string s, unsigned n, double p):
						bookNo(s), unit_sold(n), revenue(p*n){}
```

第一种构造初始化，当类成员被省略时，将被隐式的以合成默认构造函数初始化，写成如下形式

```C++
Sales_data(const string s):
						bookNo(s), unit_sold(0), revenue(0){ }
```

> 注意：构造函数不应该轻易覆盖类内初始值，除非新值与原值不同。如果不能使用类内初始值，则所有构造函数应该显式初始化每个内置类型的成员。



##### 在函数体外定义构造函数

```C++
Sales_data::Sales_data(std::istream &is){
  	read(is, *this);
}
```



#### 1.3.4 拷贝、赋值与析构



## 2 访问控制与封装

&emsp;&emsp; 在 C++ 中，使用访问说明符加强类的封装性：

**public** ：定义在 public 后的成员可被整个程序使用，定义了类的接口

**private** ：类成员可以访问，但不能被使用该类的代码访问，封装了实现

```C++
class Sales_data{
public:
  	Sales_data() = default;
  	Sales_data(const string s): bookNo(s){ }
  	Sales_data(const string s, unsigned n, double p):
  							bookNo(s), unit_sold(n), revenue(p*n){ }
  	Sales_data(std::istream&);
  
  	std::string isbn() const {return bookNo;}
  	Sales_data& combine(const Sales_data&);

private:
  	double avg_price() const;
  	std::string bookNo;
  	unsigned unit_sold = 0;
  	double revenue = 0.0;
}
```



### 2.1 `class` 与 `struct` 关键字

&emsp;&emsp; **class** 与 **struct** 唯一不同的是其默认访问权限不同。**class** 类成员默认为 `private` ，**struct** 类成员默认为 `public` 权限。

> 定义类的所有成员为 `public` 时，使用 **struct**。
>
> 定义类的所有成员为 `private` 时，使用 **class**。



### 2.2 友元

&emsp;&emsp; 一个类允许其他类或函数访问 `non-public` 成员，可以将其在类中声明为友元类型（friend）。

```C++
class Sales_data{
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
friend std::istream &read(std::istream&, const Sales_data&); 
  
public:
  	Sales_data() = default;
  	Sales_data(const string s): bookNo(s){ }
  	Sales_data(const string s, unsigned n, double p):
  							bookNo(s), unit_sold(n), revenue(p*n){ }
  	Sales_data(std::istream&);
  
  	std::string isbn() const {return bookNo;}
  	Sales_data& combine(const Sales_data&);

private:
  	double avg_price() const;
  	std::string bookNo;
  	unsigned unit_sold = 0;
  	double revenue = 0.0;
}

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, const Sales_data&);
```

> 将类中友元集中写在类的开头或结尾，方便查看。



## 3 类的其他特征

### 3.1 类成员再探

#### 3.1.1 定义类型成员

&emsp;&emsp;为了定义类的数据和函数成员，类可以定义自己的局部类型。局部类型必须定义在使用之前，因此在类开头定义。

```C++
class Screen{
public:
  	// 等价于
  	// using pos = std::string::size_type;
		typedef std::string::size_type pos;  
  
private:
  	pos cursor = 0;
  	pos widht = 0;
  	pos height = 0;
  	std::string contents;
}
```



#### 3.1.2 成员函数（constructor & inline & overloading）

```C++
class Screen{
public:
  	using pos = std::string::size_type;
  	Screen() = default;
  	Screeen(pos ht, pos wd, char c):height(ht), width(wd), content(ht*wd, c){ }
  	
  	char get() const
    		{return content[curson];}						// 隐式 inline
  	inline char get(pos r, pos wd) const;		// 显式 inline	
  	Screen &move(pos r, pos c);							// 可被 inline
  
private:
  	pos cursor = 0;
  	pos widht = 0;
  	pos height = 0;
  	std::string contents;
}

inline Screen &Screen::move(pos r, pos c){
  	pos row = r * width;
  	cursor = row + c;
  	return *this;
}

char get(pos r, pos wd) const{
  	pos row = r * width;
  	return content[row+c];
}

Screen myscreen;
char ch = myscreen.get();
ch = myscreen.get(0, 0);
```

1. 在定义构造函数后，编译器则不生成默认构造函数，需要显式定义默认构造函数
2. 第二个构造函数隐式的使用默认初始值进行初始化 `cursor`，如果 `cursor` 没有初始值，则需要显式初始化
3. 在类内定义的函数默认为 `inline` ，如构造函数和 `get()`
4. `inline` 在声明或定义处都可以，在类外函数定义处方便阅读
5. 编译器通过参数的个数选择重载函数

> `inline` 函数应定义在类的头文件中。



#### 3.1.3 `mutable` 数据成员

&emsp;&emsp;当一个成员需要修改，甚至在 `const` 成员函数中需要修改，则将其声明为 `mutable` 。

```C++
class Screen{
public:
  	void some_member() const;
		// ...
private:
  	mutable size_t access_ctr;
  	// ...
}

void some_member() const{
  	++access_ctr;
}
```



#### 3.1.4 类作为成员数据

```C++
class Window_mgr{
private:
  	std::vector<Screen> screens{Screen(24, 80, ' ')};
}
```

> 类内初始值使用 `= ` 或者 `{}` 来进行初始化。



### 3.2 返回 `this` 的函数

```C++
class Screen{
public:
  	Screen &set(char);
  	Screen &set(pos, pos, char);
}

inline Screen::Screen &set(char c){
  	content[cursor] = c;
  	return *this;
}

inline Screen::Screen &set(pos r, pos col, char ch){
  	content [r*width+c] = ch;
  	return *this;
}

Screen myscreen;
myscreen.move(4, 0).set('#');
```

&emsp;&emsp;这里返回的是 引用类型，相当于

```C++
myscreen.move(4, 0);
myscreen.set('#');
```



#### 3.2.1 `const` 成员函数返回 `*this` 

&emsp;&emsp; `const` 成员函数是 传进来的 `this` 所指的对象类型为 `const` ，所以不能改变

```C++
const Screen &display() const;
// 等同于
// const Screen &display(const Screen* const this);
```

> 一个返回 `*this` 引用的 `const` 成员函数，返回值应该为 `const` 引用。



##### 基于 `const` 重载

```C++
class Screen{
public:
		Screen &display(std::ostream os)
    								{do_display(os), return *this;}
  	const Screen &display(std::ostream os) const
    								{do_display(os), return *this;}

private:
  	void do_display(std::ostream &os) const {os << contents;}
};

Screen myscreen(5,3);
const Screen blank(5, 3);
myscreen.set('#').display(cout);
blank.display(cout);
```



### 3.3 类类型

1. 类名不同，类的类型不同

#### 类的声明

```C++ 
class Screen;		// forward declaration
```

&emsp;&emsp;类在声明后，但未定义前是不完整的类型（incomplete type）。可用于：

1. 定义指针/引用类型
2. 作为参数或者引用

```C++
class Link_screen{
  	Screen window;
  	Link_screen *next;
  	Link_screen *prev;
};
```



### 3.4 友元再探

#### 3.4.1 友元类

```C++
class Screen{
  	friend class Window_mgr;
  	// ...
};

class Window_mgr{
public:
  	using ScreenIndex = std::vector<Screen>::size_type;
  	void clear(ScreenIndex);
private:
  	std::vector<Screen> screens{Screen(24, 80, ' ')};
}

void Window_mgt::clear(ScreenIndex){
  	Screen &s = screens[ScreenIndex];
  	s.contents = string(s.height * s.width, ' ');
}
```

> 类的友元的友元不是类的友元。



#### 3.4.2 友元成员函数

要使类 `Window_mgr` 成员函数 `clear()` 成为类`Screen` 的友元，必须：

1. 定义成员函数的类 `Window_mgr` ，`clear` 必须仅声明，不能定义
2. 定义类 `Screen` ，包含友元成员函数 `clear()` 的声明
3. 定义友元成员函数 `clear()` 

```C++
class Screen(){
  	// clear() 在之前声明，在之后定义
  	friend void Window_mgr::clear(ScreenIndex);
}
```



#### 3.4.3 重载函数的友元

&emsp;&emsp;重载函数虽然拥有相同的名字，但实际为不同的函数，所以在声明重载函数作为友元时，仅仅友元声明的友元函数。

```C++
extern std::ostream& storeOn(std::ostream &, Screen &);
extern BitMap&StroeOn(BitMap &, Screen &);

class Screen{
  	friend std::ostream& storeOn(std::ostream &, Screen &);
}
```



#### 3.4.4 友元声明和作用域

```C++
struct X {
  	friend void f();

public:
  	X(){	f();	}		//	错误，f() 没有声明
  	void g();
  	void h();
};

void X::g()	{return f();}	// 错误，f() 没有声明
void f();
void X::h() {return f();}
```



## 4 类的作用域



```C++
void Window_mgr::clear(ScreenIndex i){
  	Screen &s = screens[i];
  	s.contents = string(s.height*s.width, ' ');
}
```



```C++
class Window_mgr{
public:
  	ScreenIndex addScreen(const Screen&);
}

Window_mgr::ScreenIndex;
ScreenIndex Window_mgr::addScreen(const Screen& s){
  	screens.push_back(s);
  	return screens.size()-1;
}
```



### 4.1 名称查找和类作用域

对于普通变量对象的名称查找分为以下三步：

1. 在名称的块中查找，仅查找名称使用前的声明
2. 在外层作用域中查找
3. 未找到声明，报错

对于类的名称查找：

1. 类成员声明被编译
2. 在整个类可见后，函数体被编译

#### 4.1.1 类成员声明的名称查找

&emsp;&emsp;类成员的声明在类中查找，然后在外层作用域查找。

```C++
typedef double Money;
string bal;

class Account{
public:
  	Money balance(){return bal;}		// bal 为类内定义的 Money 类型
private:
  	Money bal;
}
```



#### 4.1.2 特殊的类型名

```C++
typedef double Money;
class Account{
public:
  	Money balance(){return bal;}		// bal 为类内定义的 Money 类型
private:
  	typedef double Money;				// 错误，不能重新定义 Money
  	Money bal;
}
```

> 类型名定义一般在类的开始处。



#### 4.1.3 成员定义中块作用域的名称查找

1. 在成员函数内部查找声明
2. 若成员函数内没有，则在类中查找声明
3. 若类中没有，则在定义成员函数的作用域中查找

```C++
int height;

class Screen{
public:
  	typedef std::string::size_type pos;
  	void dummy_fcn(pos height){
      	// height 为参数 height
      	cursor = width * height;	
      
      	// 若使用成员 heiht
      	cursor = width * this->height;
      	cursor = width * Screen::height;
      
      	// 若使用 全局 height
      	cursor = width * ::height;
    }
private:
  	pos cursor = 0;
  	pos width = 0, height = 0;
}
```



## 5 构造函数再探

### 5.1 构造函数初始化列表

&emsp;&emsp; 在构造函数执行时，提供初始化列表为初始化，赋值为默认初始化再赋值。

```C++
// 赋值
Sales_data::Sales_data(const string &s, unsigned cnt, double price){
  	bookNo = s;
  	unit_sold = cnt;
  	revenur = cnt * price;
}

// 初始化
Sales_data::Sales_data(const string &s, unsigned cnt, double price):
									bookNo(s), unit_sold(cnt), revenue(cnt*price){}
```



#### 5.1.1 `const` / 引用 必须提供初始化列表

```C++
class ConstRef { 
public:
	ConstRef(int ii); 
private:
		int i;
		const int ci; 
  	int &ri;
};

ConstRef::ConstRef(int ii)
{ 
		i=ii; 		// 正确
		ci = ii;	// 错误， const 无法赋值
  	ri = i; 	// 错误，ri 未初始化
}
```

赋值构造函数与初始化列表

1. 赋值构造函数：在构造函数执行之前，完成初始化，在构造函数中进行赋值。
2. 初始化列表：构造函数执行时进行初始化

对于 `const` / 引用 / 类 类型必须进行列表初始化。



#### 5.1.2 成员初始化顺序

&emsp;&emsp;成员初始化顺序由类成员在类中的定义顺序决定。

> 在初始化成员时，尽量按照其定义顺序进行初始化。也尽量避免使用成员初始化其他成员。



#### 5.1.3 默认参数与构造函数

```C++
class Sales_data { 
public:
		Sales_data(std::string s = ""): bookNo(s) { }
		Sales_data(std::string s, unsigned cnt, double rev):
							bookNo(s), units_sold(cnt), revenue(rev*cnt) { } 
    Sales_data(std::istream &is) { read(is, *this); }
}
```

> 默认构造函数为所有的参数提供默认参数，则定义了默认构造函数。



### 5.2 委托构造函数

```C++
class Sales_data { 
public:
		Sales_data(std::string s, unsigned cnt, double price):
							bookNo(s), units_sold(cnt), revenue(cnt*price){}
		Sales_data(): Sales_data("", 0, 0) {} 
    Sales_data(std::string s): Sales_data(s, 0,0) {} 
   	Sales_data(std::istream &is): Sales_data(){read(&is, *this);}
};
```



### 5.3 默认构造函数的作用

&emsp;&emsp;当对象被默认初始化或者值初始化时，使用默认构造函数

默认初始化：

1. 在块作用域中不使用初始值初始化 `static`  / 数组时
2. 类中有类类型的成员且该类成员使用合成构造函数
3. 类类型的成员没有在初始化列表中显式初始化

值初始化：

1. 数组初始化时，提供的初始值小于数组的大小
2. 定义没有初始值的静态变量时
3. 写 `T()` 的表达式显式请求值初始化



> 在实际编码中，如果定义了其他构造函数，那么最好也提供默认构造函数。



#### 使用默认构造函数



### 5.4 隐式类类型转换

&emsp;&emsp;带有单个参数的构造函数定义了类类型的隐式转换，也称为 **转换构造函数** 。

```C++
string null_book = "9-999-9999-99";
item.combine(null_book);		

void Sales_data::combime(const Sales_data&);
// string 传入参数， 转换构造函数， 生成临时对象传入。
```



#### 5.4.1 仅支持一步类型转换

```C++
// 错误，两步转换：转为string，string -> Sales_data
item.combine("99-99999-99-9");

// 正确
item.combine(string("99-99999-99-9"));
item.combine(Sales_data("99-99999-99-9"));
```



#### 5.4.2 类型转换并不总是有效的

```C++
item.combin(cin);
```

&emsp;&emsp;将标准输入隐式转换为 `Sales_data` 类型，在 `combine` 结束后，对象也会被丢弃。



#### 5.4.3 通过构造函数取消隐式转换

```C++
class Sales_data { 
public:
		Sales_data() = default;
		Sales_data(const std::string &s, unsigned n, double p):
						bookNo(s), units_sold(n), revenue(p*n) { } 
  	explicit Sales_data(const std::string &s): 		bookNo(s) { } 
  	explicit Sales_data(std::istream&);
};
```

&emsp;&emsp; `explicit` 关键字在只含有单个参数的构造函数是意义的，且仅在头文件声明时加 `explicit` ，在定义时不能写 `explicit` 关键字。



#### 5.4.4 `explicit` 仅在直接初始化时使用

```C++
// 直接初始化
Sales_data item1(null_book);
```

> 构造函数声明为 `explicit` ：
>
> 1. 仅用于直接初始化
> 2. 编译器不能用于自动转换



#### 5.4.5 显式使用构造函数可以进行转换

```C++
item.combine(Sales_data(null_book));
item.combine(static_cast<Sales_data>(cin));
```



### 5.5 聚合类

聚合类定义满足如下几点：

1. 所有数据成员为 `public`
2. 没有构造函数
3. 没有类内初始值
4. 没有基类和虚函数

```C++
struct Data{
  	int ival;
  	string s;
};
Data val1 = {0, "Anna"};
```



### 5.6 字面值常量类

&emsp;&emsp;数据成员都是字面值类型的聚合类称为字面值常量类。

如果一个类不是聚合类，但满足以下要求，也称为字面值常量类：

1. 类成员都是字面值
2. 至少有一个 `constexpr` 的构造函数
3. 如果有类内初始值则必须为 `constexpr` 声明
4. 必须使用析构函数的默认定义



#### 5.6.1 `constexpr` 构造函数

```C++
class Debug { 
public:
		constexpr Debug(bool b = true): hw(b), io(b), other(b) {}
		constexpr Debug(bool h, bool i, bool o): hw(h), io(i), other(o) {}
		constexpr bool any() { return hw || io || other; } void set_io(bool b) { io = b; }
		void set_hw(bool b) { hw = b; }
		void set_other(bool b) { hw = b; }
private:
		bool hw; // hardware errors other than IO errors bool io; // IO errors
		bool other; // other errors
};
```



## 6 静态类成员

### 6.1 声明静态成员

&emsp;&emsp;静态成员变量和函数并不绑定至任何的对象，也没有 `this` 指针。

```C++
class Account{
public:	
  	void calculate(){ amount += amount * interestRate; }
  	static double rate(){return interestRate;}
  	static void rate(double);
private:
  	std::string owner;
  	double amount;
  	static double interestRate;
  	static double initRate();
};
```



### 6.2 使用静态变量

```C++
// 1. 使用类
double r;
r = Account::rate();

// 2. 类对象引用/指针
Account ac1;
Account *ac2 = &ac1;
r = ac1.rate();
r = ac2->rate();

// 3. 在类内可直接使用
```



### 6.3 定义静态变量

1. 仅在类内声明时写 `static` 关键字，在类外定义不能写 `static`
2. 不能在构造函数中定义静态变量
3. 也可访问私有成员

```C++
double Account::interestRate = initRate();
```





### 6.4 静态成员的类内初始化

```C++
class Account{
public:
  	static double rate(){ return interestRate;}
  	static void rate(double);
private:
  	static constexpr int period = 30;
  	double daily_tbl[period];
}
```

&emsp;&emsp;在编译时，会将 `period`  替换为 `30`， 如果类成员函数需要传入 `period` 参数，则不能在类内进行初始化。

```C++
static constexpr int period;
```



> 即使一个常量静态成员在类内初始化，也应该在类的外部定义一下该成员。



### 6.5 静态成员与普通成员不同

1. 静态成员与指针/引用相似，可以使用不完整类型声明
2. 静态成员可以作为默认参数