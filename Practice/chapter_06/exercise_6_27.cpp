#include <iostream>
#include <initializer_list>

int sum(std::initializer_list<int> il);

int main(){
	auto il = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::cout << sum(il) << std::endl;
	
	return 0;
}

int sum(std::initializer_list<int> il){
	int sum = 0;
	for (auto i : il)
		sum += i;

	return sum;
}
