#include <iostream>
#include <vector>
#include <memory>

using std::vector;
using std::cin;
using std::cout;
using std::endl;


vector<int> *create(){
	return new vector<int>();
}

vector<int> *read(vector<int> *ivec){
	int n;
	while (cin >> n){
		ivec->push_back(n);
	}

	return ivec;
}

void println(vector<int> *ivec){
	for (auto i : *ivec)
		cout << i << " ";
	cout << endl;

	delete ivec;
}

int main(){
	println(read(create()));

	return 0;
}
