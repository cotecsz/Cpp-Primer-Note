#include <iostream>
#include <list>
#include <deque>

using std::cout;
using std::endl;
using std::list;
using std::deque;


int main(){
	list<int> il = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
	deque<int> odd;
	deque<int> even;

	/* for (auto i : il)
	 *     if (i % 2 == 0)	even.push_back(i);
	 *     else	odd.push_back(i); */
	for (auto i : il)
		(i & 0x01? odd : even).push_back(i);

	for (auto i : odd)
		cout << i << " ";
	cout << endl;
	for (auto i : even)
		cout << i << " ";
	cout << endl;
	return 0;
}
