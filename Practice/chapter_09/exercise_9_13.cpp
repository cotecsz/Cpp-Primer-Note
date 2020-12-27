#include <iostream>
#include <vector>
#include <list>
#include <string>

using std::list;
using std::vector;
using std::cout;
using std::endl;

int main(){
	list<int> ilist(5, 4);
	vector<int> ivec(5, 5);

	vector<double> dvec(ilist.begin(), ilist.end());
	for (auto i : ilist)
		cout << i << " ";
	cout << endl;

	vector<double> dvec2(ivec.begin(), ivec.end());
	for (auto i : ivec)
		cout << i << " ";
	cout << endl;

	return 0;
}
