#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(){
	vector<int> ivec;

	/* cout << ivec.at(0) << endl; */
	/* cout << ivec[0] << endl; */
	/* cout << *(ivec.begin()) << endl; */
	cout << ivec.front() << endl;

	return 0;
}
