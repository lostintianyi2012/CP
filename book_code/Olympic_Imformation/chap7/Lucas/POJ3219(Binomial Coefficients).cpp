#include <iostream>
#include <string.h>

int n, k;

int main(){
	while(std::cin >> n >> k){
		if((n & k) == k)
			puts("1");
		else
			puts("0");
	}
	return 0;
}
