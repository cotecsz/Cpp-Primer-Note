#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename Sequence>
auto printIn(Sequence const& seq) -> std::ostream&
{
	for (auto const& elem : seq)
		std::cout << elem << " ";
	return std::cout << std::endl;
}

auto eliminame_duplicates(std::vector<std::string> &words) -> std::vector<std::string>&
{
	std::sort(words.begin(), words.end());
	printIn(words);

	auto unique_end = std::unique(words.begin(), words.end());
	printIn(words);

	words.erase(unique_end, words.end());
	return words;
}

bool isShorter(const std::string &s1, const std::string &s2){
	return s1.size() < s2.size();
}

int main(){
	std::vector<std::string> words{"a", "fox", "and", "another", "fox", "a", "and", "fox"};
	printIn(words);
	printIn(eliminame_duplicates(words));
	std::stable_sort(words.begin(), words.end(), isShorter);
	printIn(words);

	return 0;
}
