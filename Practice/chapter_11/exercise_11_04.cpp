#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void word_count_pro(map<string, size_t> & m);

int main(){
	map<string, size_t> m;
	word_count_pro(m);

	return 0;
}

void word_count_pro(map<string, size_t> &m){
	string word;
	while (cin >> word){
		for (auto &ch : word)
			ch = tolower(ch);

		word.erase(remove_if(word.begin(), word.end(), ispunct),
				word.end());
		++m[word];
	}

	for (const auto &e : m)
		cout << e.first << " : " << e.second << endl;
}
