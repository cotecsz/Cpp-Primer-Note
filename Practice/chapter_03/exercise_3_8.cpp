#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.8: Rewrite the program in the first exercise, first using a
 * while and again using a traditional for loop. Which of the three approaches
 * do you prefer and why? */

int main(){
	string s;
	cin >> s;

	decltype(s.size()) i = 0;
	while (i != s.size()){
		s[i] = 'x';
		++i;
	}
	cout << s << endl;

	string s("Hello");
	for (i=0; i < s.size(); ++i)
		s[i] = 'x';
	cout << s << endl;

	return 0;
}
