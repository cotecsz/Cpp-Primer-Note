#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(){
	vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (auto it=ivec.begin(); it != ivec.end(); ++it)
		*it *= *it;

	for (auto i : ivec)
		cout << i << " ";
	cout << endl;

	return 0;
}
