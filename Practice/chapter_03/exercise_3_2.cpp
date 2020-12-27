#include <iostream>
#include <string>

/* Exercise 3.2: Write a program to read the standard input a line at a time.
 * Modify your program to read a word at a time. */

using std::cin;
using std::cout;
using std::endl;
using std::string;

void get_line(){
	string s;
	while(getline(cin, s))
		cout << s << endl;
}

void get_word(){
	string s;
	while(cin >> s)
		cout << s << endl;
}

int main(){
	// get_line();
	get_word();
	return 0;
}
