#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

void elimdups(vector<string> &svec){
	std::sort(svec.begin(), svec.end());
	auto new_end = unique(svec.begin(), svec.end());
	svec.erase(new_end, svec.end());
}

bool check_size(const string &s, string::size_type sz){
	return s.size() >= sz;
}

void biggies(vector<string> &svec, size_t sz){
	elimdups(svec);

	auto iter = stable_partition(svec.begin(), svec.end(), bind(check_size, _1, sz));	

	for_each(svec.begin(), iter, [](const string &s){cout << s << " ";});
}


int main(){
	vector<string> svec{"123", "1234", "1234", "hi", "hello", "copy"};
	biggies(svec, 3);
	std::cout << endl;

	return 0;
	
}
