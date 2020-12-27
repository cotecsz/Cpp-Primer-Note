#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.6: Use a range for to change all the characters in 
 * a string to X. */

int main(){
	string s;
	cin >> s;

	for (auto &c : s)
		c = 'x';

	cout << s << endl;

	return 0;
}
