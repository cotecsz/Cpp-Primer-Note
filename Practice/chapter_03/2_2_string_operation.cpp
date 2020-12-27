#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(){
	// 1. contuine cin
	string s1, s2;
	cin >> s1 >> s2;
	cout << s1 << s2 << endl;

	// 2. unkown number of string
	string word;
	while(cin >> word){
		// process word
		cout << word << endl;
	}
	
	// 3. read entire line
	string line;
	while(getline(cin, line))
		if(!line.empty())
			cout << line << endl;
		else
			break;
	return 0;
}
