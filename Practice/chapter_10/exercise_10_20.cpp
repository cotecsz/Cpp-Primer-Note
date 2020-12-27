#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

size_t bigerThan6(vector<string> &v){
	return count_if(v.cbegin(), v.cend(),
			[](string const&s) { return s.size() > 6;}
			);
}

inline void bigerThan6_cp(string &s){
	return s.size() > 6;
}

int main(){
	vector<string> v{"1234", "12345", "123456", "1234567"};
	cout << bigerThan6(v) << endl;
	cout << count_if(v.begin(), v.end(), bigerThan6_cp);

	return 0;
}
