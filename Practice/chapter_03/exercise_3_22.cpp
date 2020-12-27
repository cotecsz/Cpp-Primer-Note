#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/* Exercise 3.22: Revise the loop that printed the first paragraph in text to 
 * instead change the elements in text that correspond to the first paragraph
 * to all uppercase. After you’ve updated text, print its contents. */

int main(){
	vector<string> text;
	
	text.push_back("This is the first sentence.");
	text.push_back("This is the second sentence.");
	text.push_back("This is the third sentence.");

	for (auto it=text.begin(); it != text.end() && !it->empty(); ++it){
		for (auto& c: *it){
			if (isalpha(c))
				c = toupper(c); 
		}
	}

	for (auto it : text)
		cout << it << endl;
	return 0;
}
