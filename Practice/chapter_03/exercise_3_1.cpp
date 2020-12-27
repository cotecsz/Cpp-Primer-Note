include <iostream>

/* Exercise 3.1: Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
 * with appropriate using declarations. */

using std::cin;
using std::cout;
using std::endl;

int main(){
	int sum = 0;
	for (int val=0; val <= 100; ++val)
		sum += val;

	cout << "Sum of 0 to 100 result is :" << sum << endl;
	return 0;
}
	
