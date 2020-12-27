#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	auto pbeg = ivec.begin();
	while (pbeg != ivec.end() && *pbeg >= 0)
		cout << *pbeg++ << endl;

	return 0;
}
