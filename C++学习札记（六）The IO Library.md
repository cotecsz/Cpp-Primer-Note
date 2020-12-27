# C++学习札记（六）The IO Library

[TOC]

本章将介绍一下操作：

- `istream` 类型：输入类型，提供输入操作
- `ostream` 类型：输出类型，提供输出操作
- `cin` ：一个 `istream` 对象，标准输入
- `cout` ：一个 `ostream` 对象，标准输出
- `cerr` ：一个 `ostream` 对象，用于输出程序错误信息
- `>>` ：从 `istream` 读取输入
- `<<` ：将输出写至 `ostream`



## 1 IO 类

&emsp;&emsp; IO 类型头文件及类型

| 头文件   | 类型                                                         |
| -------- | ------------------------------------------------------------ |
| iostream | istream, wistream 从流中读写数据<br />ostream, wostream 向流写入数据<br />iostream, wiostream 读写流 |
| fstream  | ifstream, ofstream 从文件读取数据<br />ofstream, wofstream 向文件写入数据<br />fstream, wfstream 读写文件 |
| sstream  | istringstream, wistringstream 从 string 读取数据<br />ostringstream, wostringstrem 向 string 写入数据<br />stringstream, wstringstream 读写string |

&emsp;&emsp;由于类型 `ifstream` 和 `istringstream` 与 `istream` 之间的继承关系，可以与使用 `istream` 对象来使用它们。



### 1.1 IO 对象无拷贝/赋值

&emsp;&emsp;因为不能拷贝一个 `IO` 类型，参数和返回值不能为流类型。函数通常通过 **引用** 传递/ 返回流类型。由于流类型会被修改，所以不能声明为 `const` .



### 1.2 条件状态

&emsp;&emsp;一旦流发生错误，后续 IO 将会失败，所以在读取时，需要检测输入是否正确。最简单的办法为：

```C++
while(cin >> word){
  	// 读取成功
}
```



### 1.3 管理输出缓冲

缓冲区刷新原因：

1. 程序正常结束，缓冲区刷新
2. 缓冲区已满，需要刷新缓冲
3. 操作符 `endl` 显式刷新缓冲区
4. 输出操作后，可以用操作符 `unitbuf` 设置流的状态
5. 输出流关联到另一个流，当读写被关联的流时，另一个流的缓冲区会刷新



#### 1.3.1 `unitbuf` 操作符

```C++
cout << unitbuf;	// 所有输出操作后，立即刷新缓冲区
cout << nounitbuf;// 任何输出都立即刷新，无缓冲
```

> 当程序崩溃时，输出缓冲区不会被刷新。



#### 1.3.2 关联输入和输出流

&emsp;&emsp;当一个流被关联到另一个流时，任何试图从输入流读取的操作都会先刷新输出流。标准库中的 `cout` 与 `cin` 关联在一起。



## 2 文件输入与输出

`fstream` 头文件中定义了三个类型来支持文件：

- `ifstream` ：从一个给定文件中读取数据
- `ofstream` ：向一个给定文件中写入数据
- `fstream` ：读写给定文件

下表为 `fstream` 特有操作

| function               | Uses                                        |
| ---------------------- | ------------------------------------------- |
| fstream fstrm;         | 创建一个未绑定的文件流                      |
| fstream fstrm(s);      | 创建一个 `fstream` ，并打开 s 文件          |
| fstream fstrm(s, mode) | 同上，以 mode 打开 s 文件                   |
| fstrm.open(s);         | 打开名为 s 文件，并将文件与 `fstrm` 绑定    |
| fstrm.close();         | 关闭与 `fstrm` 绑定的文件，返回 void        |
| fstrm.is_open();       | 指出 与 `fstrm` 绑定的文件是否成功打开/关闭 |



### 2.1 使用文件流对象

```C++
ifstream in(ifile);		// 创建一个 ifstream , 并打开文件
ofstream out;					// 输出文件流，未关联文件
```



#### 2.1.1 用 `ofstream` 代替 `iostream&`

```C++
ifstream input(argv[1]);
ofstream output(argv[2]);
Sales_data total;

if (read(input, total)){
  	Sales_data trans;
  	while (read(input, trans)){
      	if (total.isbn() == trans.isbn())
        		total.combine(trans);
      	else{
          	print(output, total) << endl;
          	total = trans;
        }
    }
  	print(output, total) << endl;
}
else
  	cerr << "No data?!" << endl;
```



#### 2.1.2 `open` 和 `close` 成员

```C++
ifstream in(file);
in.close();				// 关闭打开的文件

ofstream out;
out.open(ifle + ".copy");
if (out)		// 判断是否打开成功
  	// ...
else
  	cerr << "Cannot open!" << endl;
```



#### 2.1.3 自动构造与析构

```C++
for (auto p = argv+1; p != argv + argc; ++p){
  	ifstream input(*p);
  	if (input)
      	process(input)
    else
      	cerr << "Couldn't open: " + string(*p);
}		// 每次执行，input 会离开作用域，因此会被销毁
```

> 当一个 `fstream` 对象被销毁时， `close` 会被自动调用。



### 2.2 文件模式

| Mode   | Use                        |
| ------ | -------------------------- |
| in     | 以读方式打开               |
| out    | 以写方式打开               |
| app    | 每次操作前定位至文件末尾   |
| ate    | 打开文件立即定位到文件末尾 |
| trunc  | 截断文件                   |
| binary | 以二进制方式进行 IO        |

使用文件模式又如下限制：

- 只能对 `ofstream` 和 `fstream` 设定 `out` 模式
- 只能对 `istream`  和 `fstream` 设定 `in` 模式
- 只有设定 `out` 模式，才可以设定 `trunc` 模式
- 只要不设定 `trunc` 模式，就可以设定 `app` 模式
- 默认情况下，以 `out` 打开的文件会被截断，必须同时指定 `app` 追加至文件末尾
- `ate` 和 `binary` 可用于任何类型的文件流对象



#### 以 `out` 模式打开文件会丢弃已有数据

```C++
// file 文件被截断
ofstream out("file1");		// 隐含 out, turnc
ofstream out2("file1", ofstream::out);	// 隐含 trunc
ofstream out3("file1", ofstream::out | ofstream::trunc);

// 为保留文件内容， 必须显式指定 app 模式
ofstream app("file2", ofstream::app);		// 隐含 out
ofstream app2("file2", ofstream::out | ofstream::app);
```

> 保留 ofstream 打开的文件已有数据唯一方式是显式指定 `app` 模式 / `in` 模式。



#### 每次调用 `open` 需要确定文件模式

```C++
ofstream out;
out.open("file");			// 隐含 out trunc
out.close();

out.open("file2", ofstream::app);	// 隐含 out
out.close();
```



## 3 `string` Stream

`sstream` 头文件定义了三种类型：

- `istringstream` ：从 `string` 读取数据
- `ostringstream` ：向 `string` 写入数据
- `stringsream` ：在 `string` 中读写数据

| Function         | Uses                                            |
| ---------------- | ----------------------------------------------- |
| sstream strm;    | 未绑定的`stringstream` 对象                     |
| sstream strm(s); | 一个 `sstream` 对象，保存 `string s` 的一个拷贝 |
| strm.str();      | 返回 `stem` 所保存的 `string` 的拷贝            |
| strm.str(s);     | 将 `string s` 拷贝至 `strm` 中，返回 `void`     |























