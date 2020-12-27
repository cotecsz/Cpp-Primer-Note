#include <iostream>
#include <vector>
#include <vector>
#include <list>
#include <iterator>

using std::list;
using std::copy;
using std::cout;
using std::endl;
using std::vector;

template<typename Sequence>
void printIn(Sequence const& seq){
	for (const auto & i : seq)
		cout << i << " ";
	cout << endl;
}

int main(){
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::list<int> lst1;
	copy(vec.cbegin(), vec.cend(), inserter(lst1, lst1.begin()));
	printIn(lst1);

	std::list<int> lst2;
	copy(vec.cbegin(), vec.cend(), back_inserter(lst2));
	printIn(lst2);

	std::list<int> lst3;
	copy(vec.cbegin(), vec.cend(), front_inserter(lst3));
	printIn(lst3);	
	
	return 0;
}
