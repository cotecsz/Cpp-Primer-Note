#include <iostream>
#include <cctype>
#include <string>

/* using namespace std; */

using std::cout;
using std::endl;
using std::string;

bool anyCaptial(const string &s);
void toLowCase(string &s);

int main(){
	string s("Hello world!");

	if (anyCaptial(s))
		cout << "Has Captial" << endl;	

	toLowCase(s);
	cout << s << endl;
	return 0;
}

bool anyCaptial(const string &s){
	for (auto c : s)
		if (isupper(c)) return true;
	
	return false;
}

void toLowCase(string& s){
	for (auto & c : s)
		c = tolower(c);
}
