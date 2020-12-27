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

int main(){
	std::vector<std::string> words{"a", "fox", "and", "another", "fox", "a", "and", "fox"};
	printIn(words);
	printIn(eliminame_duplicates(words));

	return 0;
}
