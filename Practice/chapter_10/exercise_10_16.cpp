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

	stable_sort(svec.begin(), svec.end(),
			[] (string const& lhs, string const &rhs)
			{return lhs.size() < rhs.size();}
			);

	auto wc = find_if(svec.begin(), svec.end(),
			[sz](string const & s){return s.size() >= sz;}
			);

	for_each(wc, svec.end(), 
			[](const string &s)
			{cout << s << " ";}
			);
}

int main(){
	vector<string> svec{"123", "1234", "1234", "hi", "hello", "copy"};
	biggies(svec, 3);
	std::cout << endl;

	return 0;
	
}
