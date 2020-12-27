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

int main(){
	vector<int> ivec;
	int num;

	while (cin >> num){
		ivec.push_back(num);
	}

	for (decltype(ivec.size()) i=0; i < ivec.size()-1; ++i)
		cout << ivec[i] + ivec[i+1] << endl;

	decltype(ivec.size()) m = 0;
	decltype(ivec.size()) n = ivec.size() - 1;

	while(m < n){
		cout << ivec[m] + ivec[n] << endl;
		++m;
		--n;
	}

	return 0;
}
