#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

/* Exercise 3.25: Rewrite the grade clustering program from § 3.3.3 (p. 104) using iterators instead of subscripts. */

int main(){
	vector<unsigned> score(11, 0);

	unsigned grade;
	while (cin >> grade){
		if (grade <= 100)
			++*(score.begin()+grade/10);
	}

	for (auto s : score)
		cout << s << " ";
	cout << endl;

	return 0;
}
