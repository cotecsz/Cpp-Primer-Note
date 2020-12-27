#include <iostream>
#include "exercise_12_02.h"


int main(){
	StrBlob sb{"hello", "world"};
	const StrBlob csb{"const", "hello", "world"};

	std::cout << "sb: " << sb.front() << " " << sb.back() << std::endl;
	std::cout << "csb: " << csb.front() << " " << csb.back() << std::endl;

	return 0;
}
