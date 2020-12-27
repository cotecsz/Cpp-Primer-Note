#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

bool find(vector<int>::const_iterator begin, vector<int>::const_iterator end, int i);

int main(){
	vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	bool res = find(ivec.cbegin(), ivec.cend(), 9);

	cout << res << endl;
	return 0;
}

bool find(vector<int>::const_iterator begin, vector<int>::const_iterator end, int i){
	while (begin != end){
		if (*begin++ == i)
			return true;
	}
	return false;
}
