#include <iostream>
#include "exercise_7_12.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
	Sales_data total(std::cin);
	
	if (!total.isbn().empty()){
		std::istream &is = std::cin;
		while (is){
			Sales_data trans(is);
			if (total.bookNo == trans.bookNo){
				total.combine(trans);
			}
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
		print(std::cout, total) << std::endl;
	}	
	else{
		std::cerr << "No data?!" << endl;
		return -1;
	}

	return 0;
}
