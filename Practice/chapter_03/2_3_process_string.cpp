#include <iostream>
#include <cctype>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void process_str_for(){
	
	string str("Hello, Alice!!!");

	// 1. print all character in string
	for(auto c : str)
		cout << c << endl;

	// 2. calculate punctuation characters in string
	decltype (str.size())punct_cnt = 0;
	for(auto c : str){
		if(ispunct(c))
			++punct_cnt;	
	}

	cout << punct_cnt << " punctuation characters in " << str << endl;
	
	// 3. convert all characters to upper
	for (auto &c : str)
		c = toupper(c);
	cout << str << endl;

}

void process_str_charac(){
	//1. print first character
	string s("some string");
	if(!s.empty())
		cout << s[0] << endl;

	// 2. convert first character to upper
	if (!s.empty())
		s[0] = toupper(s[0]);
	cout << s << endl;

	// 3. convert first word to upper
	for (decltype(s.size()) index = 0; index != s.size() && !isspace(s[index]); ++index)
		s[index] = toupper(s[index]);
	cout << s << endl;
		
}

void num2hex(){
	const string hexdigits = "0123456789ABCDEF";
	string::size_type n;
	string result;

	while (cin >> n)
		if (n < hexdigits.size())
			result += hexdigits[n];

	cout << result << endl;
}

int main(){
	process_str_for();
	process_str_charac();
	num2hex();
	return 0;
}
