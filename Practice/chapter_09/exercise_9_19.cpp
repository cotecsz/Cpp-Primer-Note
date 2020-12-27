#include <iostream>
#include <list>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;

int main(){
	list<string> lst;

	string word;
	while (cin >> word)
		lst.push_front(word);

	for (auto s : lst)
		cout << s << " ";
	cout << endl;

	return 0;
}
