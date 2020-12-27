#include <iostream>
#include <forward_list>

using std::cout;
using std::endl;
using std::forward_list;

int main(){
	forward_list<int> flist = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto prev = flist.before_begin();
	auto curr = flist.begin();

	while (curr != flist.end()){
		if (*curr % 2 != 0)
			curr = flist.erase_after(prev);
		else{
			prev = curr;
			++curr;
		}
	}

	for (auto i : flist)
		cout << i << " ";
	cout << endl;

	return 0;
}
