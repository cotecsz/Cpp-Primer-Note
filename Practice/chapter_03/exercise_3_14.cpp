#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(){
	int num;
	vector<int> ivec;

	while(cin >> num){
		ivec.push_back(num);
	}

	for (auto i : ivec)
		cout << i ;
	return 0;
}
