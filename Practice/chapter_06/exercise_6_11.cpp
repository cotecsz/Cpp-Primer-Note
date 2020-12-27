#include <iostream>

using namespace std;

void reset(int &i);

int main(){
	int a = 42;

	cout << "a = " << a << endl;
	reset(a);
	cout << "After reset():\n" << "a = " << a << endl;

	return 0;
}

void reset(int &i){
	i = 0;
}
