#include <iostream>

using namespace std;

void swap(int& a, int& b);

int main(){
	int a = 10, b = 42;
	
	cout << "a = " << a << " b = " << b << endl;
	swap(a, b);
	cout << "After swap():\n" << "a = " << a << " b = " << b << endl;

	return 0;
}

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}
