#include "exercise_7_41.h"

using std::cout;
using std::endl;

int main(){
	cout << "1. default way" << endl;
	cout << "--------------" << endl;
	Sales_data s1;
	
	cout << "\n2. use string parameter" << endl;
	cout << "--------------" << endl;
	Sales_data s2("CPP_Primer_5th");

	cout << "\n3. complete parameter" << endl;
	cout << "-----------------------" << endl;
	Sales_data s3("CPP_Primer_5th", 3, 2);

	cout << "\n4. use istream as parameter" << endl;
	cout << "-----------------------------" << endl;
	Sales_data s4(std::cin);

	return 0;
}
