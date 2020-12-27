#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void elimDups(vector<string> &words);

int main(){
	vector<string> words = {"a", "fox", "is", "running", "the", "and", "fox"};
	elimDups(words);

	for (auto s : words)
		cout << s << " ";
	cout << endl;

	return 0;
}

void elimDups(vector<string> &words){
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}
