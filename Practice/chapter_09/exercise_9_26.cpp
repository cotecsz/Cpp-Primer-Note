#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::begin;
using std::end;

int main(){
	int ia[] = {0, 1, 1, 2, 3,  5, 8, 13, 21, 55, 89};

	vector<int> ivec(ia, end(ia));
	list<int> ilist(begin(ia), end(ia));

	for (auto it = ilist.begin(); it != ilist.end();)
		if (*it & 0x01)
			it = ilist.erase(it);
		else
			++it;
	for (auto it = ivec.begin(); it != ivec.end();)
		if(!(*it & 0x01))
			it = ivec.erase(it);
		else
			++it;

	for (auto i : ivec)
		cout << i << " ";
	cout << endl;
	for (auto i : ilist)
		cout << i << " ";
	cout << endl;
}
