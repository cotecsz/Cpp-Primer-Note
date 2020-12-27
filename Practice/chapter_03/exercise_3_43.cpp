#include <iostream>

using namespace std;

int main(){
	int arr[3][4] = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 10, 11}
	};

	for (int (*p)[4] =arr; p != arr+3; ++p){
		for (int *q=*p; q != *p+4; ++q){
			cout << *q << " ";
		}
		cout << endl;
	}	

	for (const int (&row)[4] : arr){
		for (int col : row){
			cout << col << " ";
		}
		cout << endl;
	}

	for (size_t i=0; i!= 3; ++i){
		for (size_t j=0; j != 4; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
