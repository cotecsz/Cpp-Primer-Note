#include <iostream>
#include <vector>
#include <vector>
#include <list>
#include <iterator>

int main(){
	std::vector<int> vec{1, 1, 2, 3, 5, 5, 7, 7, 9};

	std::list<int> lst;
	
	std::unique_copy(vec.begin(), vec.end(), std::back_inserter(lst));
	for (auto i : lst)
		std::cout << i << " ";
	return 0;
}
