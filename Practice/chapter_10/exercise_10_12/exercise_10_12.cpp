#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "exercise_7_41.h"

inline bool compareIsbn(const Sales_data &sd1, const Sales_data &sd2){
	return sd1.isbn().size() < sd2.isbn().size();
}

int main(){
	Sales_data da("x"), d2("xy"), d3("xyz"), d4("abcd"), d5("abcde");
	std::vector<Sales_data> v{da, d2, d3, d4, d5};

	std::sort(v.begin(), v.end(), compareIsbn);

	for (const auto &element : v)
		std::cout << element.isbn() << " ";
	std::cout << std::endl;

	return 0;
}
