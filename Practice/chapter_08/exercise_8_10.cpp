#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

void ReadFileToVec(const string& fileName, vector<string>& vec);

int main(){
	vector<string> code;
	ReadFileToVec("exercise_8_01.cpp", code);

	for (auto &line : code){
		istringstream iss(line);
		string word;
		while (iss >> word)
			cout << word <<", ";
		cout << endl;	
	}

	return 0;
}

void ReadFileToVec(const string& fileName, vector<string>& vec){
	ifstream ifs(fileName);
	if (ifs){
		string buf;
		while (getline(ifs, buf))
			vec.push_back(buf);
	}
	else
		cerr << "NoData?!" << endl;
}
