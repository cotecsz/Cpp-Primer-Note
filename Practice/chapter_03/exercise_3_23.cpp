#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* Exercise 3.23: Write a program to create a vector with ten int elements. 
 * Using an iterator, assign each element a value that is twice its current value.
 * Test your program by printing the vector. */

int main(){
	vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	for (auto it=ivec.begin(); it != ivec.end(); ++it)
		*it = 2 * *it;

	for (auto i : ivec)
		cout << i << " ";
	cout << endl;

	return 0;
}
