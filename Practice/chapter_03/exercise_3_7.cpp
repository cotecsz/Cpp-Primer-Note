#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.7: What would happen if you define the loop control variable 
 * in the previous exercise as type char? Predict the results and then change 
 * your program to use a char to see if you were right. */

int main(){
	string s;
	cin >> s;

	for (auto &c : s)
		c = 'x';

	cout << s << endl;

	return 0;
}
