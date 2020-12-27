#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(){
	vector<int> ivec; 
	ivec.resize(10);
	fill_n(ivec.begin(), 10, 0);
	/* fill_n(back_inserter(ivec), 10, 0); */
	for (auto i : ivec)
		cout << i << " ";
	cout << endl;

	return 0;
}
