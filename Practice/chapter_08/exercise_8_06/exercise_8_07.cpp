#include <iostream>
#include <fstream>
#include "exercise_7_41.h"

using namespace std;

int main(int argc, char *argv[]){
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	Sales_data total;
	if (read(input, total)){
		Sales_data trans;
		while (read(input, trans)){
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else{
				print(output, total) << endl;
				total = trans;
			}
		}
		print(output, total) << endl;
	}
	else
		cerr << "No Data?!" << endl;

	return 0;
}
