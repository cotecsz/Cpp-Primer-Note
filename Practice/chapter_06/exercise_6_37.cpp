
typedef string arrStr[10];
arrStr &func(param);

using arrStr = string[10];
arrStr &func(param);

auto func(param) -> string(&)[10]

string str[10] = {};
decltype(str) &func(param);
