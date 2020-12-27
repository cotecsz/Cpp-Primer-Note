#include <iostream>
#include "Chapter6.h"

int fact(int val){
	return val < 1 ? 1 : val * fact(val-1);
}

void interact(){
	const std::string prompt = "Enter a number within [1. 12]: \n";
	const std::string out_of_range = "Out of range, please try again! \n";

	int i = 0, tryCnt = 0;
	std::cout << prompt;
	while (std::cin >> i){
		if (i < 1 || i > 12){
			if (tryCnt > 3)
				break;
			std::cout << out_of_range;
			++tryCnt;
		}
		else{
			std::cout << "fact(" << i << ") = " << fact(i) << std::endl;
			tryCnt = 0;
		}
	}
}
