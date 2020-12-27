#include <iostream>

using namespace std;

int main(){
	cout << "How long do you want the string" << endl;
	int size{0};
	cin >> size;

	char *input = new char[size+1]();
	cin.ignore();
	cout << "input the string: " ;
	cin.get(input, size + 1);
	cout << input;

	delete[] input;
	return 0;	
}
