#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void elimdups(vector<string> &svec){
	std::sort(svec.begin(), svec.end());
	auto new_end = unique(svec.begin(), svec.end());
	svec.erase(new_end, svec.end());
}

void biggies(vector<string> &svec, size_t sz){
	elimdups(svec);

	auto pivot = partition(svec.begin(), svec.end(), 
			[sz](const string &s)
			{ return s.size() >= sz;});
	
	for (auto it = svec.cbegin(); it != pivot; ++it)
		std::cout << *it << " ";
}

int main(){
	vector<string> svec{"123", "1234", "1234", "hi", "hello", "copy"};
	biggies(svec, 3);
	std::cout << endl;

	return 0;
	
}
