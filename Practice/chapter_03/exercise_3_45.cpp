#include <iostream>

using namespace std;
typedef int int_array[4];

int main(){
	int arr[3][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 10, 11}
	};
	
	for (auto &p : arr){
		for (auto q : p){
			cout << q << " ";
		}
		cout << endl;
	}

	for (auto i=0; i < 3; ++i){
		for (auto j=0; j < 4; ++j){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	for ( auto p = arr; p != arr + 3; ++p){
		for (auto q = *p; q != *p + 4; ++q){
			cout << *q << " ";
		}
		cout << endl;
	}
	return 0;
}
