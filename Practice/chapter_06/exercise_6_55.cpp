int func(int, int);
vector<decltype(func)*> vf;

int add(int a, int b)	{return a + b};
int	subtract(int a, int b)	{return a - b};
int multiply(int a, int b)	{return a * b};
int divide(int a, int b)	{return a / b};

vf.push_back(add);
vf.push_back(subtract);
vf.push_back(multiply);
vf.push_back(divide);
