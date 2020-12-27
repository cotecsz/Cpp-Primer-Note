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
/* Exercise 3.21: Redo the first exercise from § 3.3.3 (p. 105) using iterators. */

void checkAndPrint(vector<int>& ivec);
void checkAndPrint(vector<string>& svec);

int main(){
	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10, 42);
	vector<int> v4{10};
	vector<int> v5{10, 42};
	vector<string> v6{10};
	vector<string> v7(10, "hi");

	checkAndPrint(v1);
	checkAndPrint(v2);
	checkAndPrint(v3);
	checkAndPrint(v4);
	checkAndPrint(v5);
	checkAndPrint(v6);
	checkAndPrint(v7);

	return 0;
}

void checkAndPrint(vector<int>& ivec){
	cout << "vector size: " << ivec.size() << " ";

	cout << "vector content: ";
	for (auto it=ivec.begin(); it != ivec.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

void checkAndPrint(vector<string>& svec){
	cout << "vector size: " << svec.size() << " ";

	cout << "vector content: ";
	for (auto it=svec.begin(); it != svec.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

