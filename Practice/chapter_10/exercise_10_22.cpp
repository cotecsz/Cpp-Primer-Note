#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool bigerThan6(const string &s, string::size_type sz){
	return s.size() <= sz;
}

int main(){
	vector<string> v{"1234", "12345", "123456", "1234567"};
	cout << count_if(v.begin(), v.end(), bind(bigerThan6, _1, 6)) << endl;

	return 0;
}
