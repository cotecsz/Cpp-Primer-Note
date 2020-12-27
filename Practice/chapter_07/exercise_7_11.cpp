#include <iostream>
#include <string>
#include "exercise_7_11.h"

using namespace std;

int main(){
	Sales_data item1;
	print(std::cout, item1)  << endl;

	Sales_data item2("0-123-45678-X");
	print(std::cout, item2) << endl;

	Sales_data item3("0-123-45678-X", 3, 1);
	print(std::cout, item3) << endl;

	Sales_data item4(std::cin);
	print(std::cout, item4) << endl;
}
