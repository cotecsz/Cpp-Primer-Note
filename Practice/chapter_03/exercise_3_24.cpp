#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* Exercise 3.20: Read a set of integers into a vector. Print the sum of each pair of 
 * adjacent elements. Change your program so that it prints the sum of the first and
 * last elements, followed by the sum of the second and second-to- last, and so on. */

/* Exercise 3.24: Redo the last exercise from § 3.3.3 (p. 105) using iterators. */

int main(){
	vector<int> ivec;
	int num;

	while (cin >> num){
		ivec.push_back(num);
	}

	for (auto it=ivec.begin(); it != ivec.end(); ++it)
		cout << *it + *(it+1) << " ";
	cout << endl;

	for (auto it=ivec.begin(), ie=ivec.end()-1; it < ie; ++it, --ie)
		cout << *it + *ie << " ";
	cout << endl;

	return 0;
}
