#include <iostream>
#include <vector>

using namespace std;
/* using F = int (int, int); */
typedef int F(int, int);

int add(int a, int b)	{return a + b;}
int subtract(int a, int b) 	{return a - b;}
int multiply(int a, int b)	{return a * b;}
int divide(int a, int b)	{return b == 0 ? 0 : a / b;}

int main(){
	int func(int, int);
	/* vector<decltype(func)*> vf; */
	vector<F*> vf;

	vf.push_back(add);
	vf.push_back(subtract);
	vf.push_back(multiply);
	vf.push_back(divide);

	for (auto f : vf)
		cout << f(6, 4) << ", ";
	cout << endl;

	return 0;
}
