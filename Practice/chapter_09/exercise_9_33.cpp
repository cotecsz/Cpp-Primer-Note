#include <iostream>
#include <vector>

using std::endl;
using std::cout;
using std::vector;

int main(){
	vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto begin = ivec.begin();
	while(begin != ivec.end()){
		++begin;
		begin = ivec.insert(begin, 42);
		++begin;
	}
	for (auto i : ivec)
		cout << i << " ";
	cout << endl;

	return 0;
}
