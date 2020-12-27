#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.10: Write a program that reads a string of characters including punctuation 
 * and writes what was read but with the punctuation removed. */

int main(){
	string str("Hello, world!");
	string result;

	for (auto c : str){
		if (!(ispunct(c)))
			result += c;
	}

	cout << result << endl;
}
