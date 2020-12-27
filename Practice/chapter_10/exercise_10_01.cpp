#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	vector<int> ivec = {0, 1, 1, 2, 3, 4, 5, 6, 3, 1, 1, 2, 4, 1};
	int val = 1;

	auto cnt = count(ivec.cbegin(), ivec.cend(), val);
	cout << cnt << endl;

	return 0;
}
