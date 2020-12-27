#include <iostream>
#include <forward_list>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::forward_list;

void find_str(forward_list<string>& flist,const string &, const string&);

int main(){
	forward_list<string> flist = {"Hello", "MrYang", "Fine"};
	string str1 = "Fine";
	string str2 = "Thanks";

	find_str(flist, str1, str2);
	for (auto s : flist)
		cout << s << " ";
	cout << endl;

	return 0;
}

void find_str(forward_list<string>& flist, const string &str1, const string& str2){
	auto prev = flist.before_begin();
	auto curr = flist.begin();

	while (curr != flist.end()){
		if (*curr == str1){
			flist.insert_after(curr, str2);
			return ;
		}
		else{
			prev = curr;
			++curr;
		}
	}
	flist.insert_after(prev, str2);
}
