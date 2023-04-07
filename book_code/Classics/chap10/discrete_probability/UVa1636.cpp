#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>

std::string s;
int a, b, n;
int main(){
	while(std::cin >> s){
		a = 0, b = 0;
		n = s.length();
		for(int i = 0; i < s.length(); i++)
			if(s[i] == '0')
				b++;
		for(int i = 1; i < s.length(); i++)
			if(s[i] == '0' && s[i-1] == '0')
				a++;
		if(s[0] == '0' && s[s.length() - 1] == '0')
			a++;
		if(a * n > b * b)
			puts("SHOOT");
		else if(a * n == b * b)
			puts("EQUAL");
		else
			puts("ROTATE");
	}
	return 0;
}
