#include <map>
#include <string>
#include <iostream>

using std::string;
using std::multimap;
using std::cin;
using std::cout;
using std::endl;

int main(){
	multimap<string, string> families;
	for (string lname, fname; cin >> fname >> lname; families.emplace(lname, fname));
	for (auto const& family: families)
		cout << family.second << " " << family.first << endl;

	return 0;
}
