#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void ReadFileToVec(const string& fileName, vector<string>& vec);

int main(){
	vector<string> words;
	ReadFileToVec("exercise_8_01.cpp", words);

	for (auto word : words)
		cout << word << endl;

	return 0;
}

void ReadFileToVec(const string& fileName, vector<string>& vec){
	ifstream ifs(fileName);
	if (ifs){
		string buf;
		while (ifs >> buf)
			vec.push_back(buf);
	}
}
