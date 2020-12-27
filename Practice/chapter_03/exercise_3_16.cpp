#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* Exercise 3.16: Write a program to print the size and contents of the vectors from exercise 3.13. 
 * Check whether your answers to that exercise were correct. If not, restudy § 3.3.1 (p. 97) until
 * you understand why you were wrong. */

int main(){
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10, 42);
	vector<int> v4{10};
	vector<int> v5{10, 42};
	vector<string> v6{10};
	vector<string> v7(10, "hi");

	cout << "v1 size: " << v1.size() << endl;
	cout << "v2 size: " << v2.size() << endl;
	cout << "v3 size: " << v3.size() << endl;
	cout << "v4 size: " << v4.size() << endl;
	cout << "v5 size: " << v5.size() << endl;
	cout << "v6 size: " << v6.size() << endl;
	cout << "v7 size: " << v7.size() << endl;

	cout << "v1 content: ";
	for (auto i : v1)
		cout << i << " ";
	cout << endl;

	cout << "v2 content: ";
	for (auto i : v2)
		cout << i << " ";
	cout << endl;

	cout << "v3 content: ";
	for (auto i : v3)
		cout << i << " ";
	cout << endl;

	cout << "v4 content: ";
	for (auto i : v4)
		cout << i << " ";
	cout << endl;

	cout << "v5 content: ";
	for (auto i : v5)
		cout << i << " ";
	cout << endl;
	
	cout << "v6 content: ";
	for (auto i : v6)
		cout << i << " ";
	cout << endl;
	
	cout << "v7 content: ";
	for (auto i : v7)
		cout << i << " ";
	cout << endl;

	return 0;
}
