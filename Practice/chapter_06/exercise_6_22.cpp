#include <iostream>

using std::cout;
using std::endl;

void swap(int* &pa, int* &pb);

int main(int argc, char* argv[]){
	int a = 1, b = 2;
	int *pa = &a, *pb = &b;

	swap(pa, pb);
	cout << "a = " << *pa << ", b = " << *pb << endl;

	return 0;
}

void swap(int* &pa, int* &pb){
	int* temp = pa;
	pa = pb;
	pb = temp;
	
}
