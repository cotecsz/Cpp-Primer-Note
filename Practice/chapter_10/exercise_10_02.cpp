#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(){
	list<string> lst;
	string str;
   	while (cin >> str)
		lst.push_back(str);

	string s = "hello";

	auto cnt = count(lst.cbegin(), lst.cend(), s);
	cout << cnt << endl;

	return 0;
}
