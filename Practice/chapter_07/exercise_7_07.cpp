#include <iostream>
#include "exercise_7_06.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
	Sales_data total;
	
	if (read(std::cin, total)){
		Sales_data trans;
		while (read(std::cin, trans)){
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
