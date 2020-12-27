#include <iostream>
#include <fstream>
#include "exercise_12_09.h"
#include "exercise_12_09_ptr.h"

using namespace std;

int main(){
	ifstream ifs("./input.txt");
	StrBlob sb;
	string s;

	while (getline(ifs, s)){
		sb.push_back(s);
	}

	for (StrBlobPtr sbp = sb.begin(); sbp != sb.end(); sbp.incr()){
		cout << sbp.deref() << endl;
	}
	return 0;
}
