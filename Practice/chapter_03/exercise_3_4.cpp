#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.4: Write a program to read two strings and report whether the strings are equal. 
 * If not, report which of the two is larger. Now, change the program to report whether the
 * strings have the same length, and if not, report which is longer. */

void find_bigger(){
	string str1, str2;

	while (cin >> str1 >> str2){
		if (str1 == str2)
			cout << "The tow strings are equal." << endl;
		else
			cout << "The larger string is " << ((str1 > str2) ? str1 : str2) << endl;
	}
}

void find_longer(){
	string str1, str2;

	while (cin >> str1 >> str2){
		if (str1.size() == str2.size())
			cout << "The two strings have the same size." << endl;
		else
			cout << "The longer string is " << ((str1.size() > str2.size()) ? str1:str2) << endl;
	}
}

int main(){
	// find_bigger();
	find_longer();
}
