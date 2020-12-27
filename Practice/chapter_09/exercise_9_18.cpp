#include <iostream>
#include <deque>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::deque;

int main(){
	deque<string> dst;

	string word;
	while (cin >> word)
		dst.push_front(word);

	for (auto s : dst)
		cout << s << " ";
	cout << endl;

	return 0;
}
