#include <iostream>
#include <vector>

using namespace std;
using Iter = vector<int>::const_iterator;

void print_vec(Iter first, Iter last);

int main(){
	vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	print_vec(ivec.begin(), ivec.end());

	return 0;	
}

void print_vec(Iter first, Iter last){
	if (first == last){
		cout << "over!" << endl;
		return;
	}
	cout << *first << " ";
	print_vec(++first, last);
}
