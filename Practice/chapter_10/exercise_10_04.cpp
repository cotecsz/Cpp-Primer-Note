#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
	vector<double> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int result = accumulate(ivec.cbegin(), ivec.cend(), 0);
	cout << result << endl;

	return 0;
}
