#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool check_size(const string &s, size_t i){
	return i > s.size();
}

int main(){
	vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8};
	string s("12345");

	auto it = find_if(ivec.cbegin(), ivec.cend(), bind(check_size, s, _1));
	if (it != ivec.end())
		cout << *it << endl;

	return 0;
}
