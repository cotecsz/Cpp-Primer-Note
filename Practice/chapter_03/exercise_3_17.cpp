#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* Exercise 3.17: Read a sequence of words from cin and store the values a vector.
 * After you’ve read all the words, process the vector and change each word to uppercase.
 * Print the transformed elements, eight words to a line. */

int main(){
	string word;
	vector<string> text;

	while(cin >> word)
		text.push_back(word);

	for (auto & w : text)
		for (auto & c : w)
			c = toupper(c);

	for (decltype(text.size()) i=0; i != text.size(); ++i){
		cout << text[i] << " ";
		if ((i+1) % 8 == 0 && i != 0)
			cout << endl;
	}

	return 0;
}
