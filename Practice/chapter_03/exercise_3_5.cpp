#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Exercise 3.5: Write a program to read strings from the standard input, concatenating 
 * what is read into one large string. Print the concatenated string. Next, change the
 * program to separate adjacent input strings by a space. */

void concatenate_words(){
	string s, result;

	while(cin >> s){
		result += s;
	}
	cout << result << endl;

}

void concatenate_words_space(){
	string s, result;

	while(cin >> s){
		result += s + " ";
	}
	cout << result << endl;
}

int main(){
	concatenate_words();
	concatenate_words_space();
	return 0;
}
