#include <iostream>
#include <string>
#include <fstream>
#include "exercise_12_27.h"

using namespace std;

void runQueries(ifstream& infile){
	TextQuery tq(infile);
	while (true){
		cout << " enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

int main(){
	ifstream ifs("./exercise_12_27.h");
	runQueries(ifs);
	return 0;
}
