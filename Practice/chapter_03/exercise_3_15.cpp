#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

int main(){
	string str;
	vector<string> ivec;

	while(cin >> str){
		ivec.push_back(str);
	}

	for (auto c : ivec)
		cout << c ;
	return 0;
}
