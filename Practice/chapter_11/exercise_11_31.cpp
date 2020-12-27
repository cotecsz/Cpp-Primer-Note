#include <iostream>
#include <string>
#include <map>

using std::string;
using std::cout;
using std::endl;
using std::multimap;

int main(){
	std::multimap<string, string> authors{
			{"alan", "DMA"},
			{"pezy", "leetcode"},
			{"alan", "FTP"},
			{"pezy", "CPP_Primer"},
			{"wang", "CP5"}
	};

	string author = "pezy";
	string work = "leetcode";

	auto found = authors.find(author);
	auto count = authors.count(author);

	while(count){
		if (found->second == work){
			authors.erase(found);
			break;
		}
		++found;
		--count;
	}

	for (const auto &author : authors)
		cout << author.first << " " << author.second << endl;

	return 0;
}
