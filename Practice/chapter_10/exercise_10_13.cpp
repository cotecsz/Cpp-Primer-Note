#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::endl;
using std::cout;
using std::vector;

inline bool moreFiveWords(const string& str){
	return str.size() >= 5;
}

int main(){
	vector<string> svec{"hello", "the", "name", "world"};

	auto end_true = std::partition(svec.begin(), svec.end(), moreFiveWords);
	/* svec.erase(end_true, svec.end()); */

	/* for (const auto &elem : svec)
	 *     cout << elem << " ";
	 * cout << endl; */

	for (auto it = svec.cbegin(); it != end_true; ++it)
		cout << *it << " ";
	cout << endl;

	return 0;
}
