#include <iostream>

using namespace std;

int main(){
	int arr[3][4];

	size_t cnt = 0;
	for (auto &row : arr){
		for (auto &col : row){
			col = cnt;
			++cnt;
		}
	}

	for (const auto &row : arr){
		for (auto col : row){
			cout << col << endl;
		}
	}

	return 0;
}
