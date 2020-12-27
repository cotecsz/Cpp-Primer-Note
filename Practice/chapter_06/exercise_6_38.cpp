#include <iostream>

int odd[] = {1, 3, 5, 7, 9};
int even[] = {2, 4, 6, 8, 10};

decltype(odd) &func(int i){
	return (i % 2) ? odd : even;
}
