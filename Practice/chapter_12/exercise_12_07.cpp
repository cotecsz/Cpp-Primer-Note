#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;


shared_ptr<vector<int>> create(){
	return std::make_shared<vector<int>>();
}

shared_ptr<vector<int>> read(shared_ptr<vector<int>> ivec){
	int n;
	while (cin >> n){
		ivec->push_back(n);
	}

	return ivec;
}

void println(shared_ptr<vector<int>> ivec){
	for (auto i : *ivec)
		cout << i << " ";
	cout << endl;
}

int main(){
	println(read(create()));

	return 0;
}
