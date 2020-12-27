#include <iostream>
#include "exercise_7_02.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
	Sales_data total;
	
	if (cin >> total.bookNo >> total.units_sold >> total.revenue){
		Sales_data trans;
		while (cin >> trans.bookNo >> trans.units_sold >> trans.revenue){
			if (total.bookNo == trans.bookNo){
				total.combine(trans);
			}
			else {
				cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
				total = trans;
			}
		}
		cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
	}	
	else{
		std::cerr << "No data?!" << endl;
		return -1;
	}

	return 0;
}
