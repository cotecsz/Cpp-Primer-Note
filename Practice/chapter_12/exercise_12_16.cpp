#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main(){
	unique_ptr<string> p1(new string("hello"));
	/* unique_ptr<string> p2 = p1; */

	unique_ptr<string> p3(p1);
	cout << *p1 << endl;
	p1.reset(nullptr);

	return 0;
}
