#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;
typedef long long ll;

char gc(){
	static char buf[1 << 20], *p1, *p2;
	if(p1 == p2)
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	return p1 == p2 ? EOF : *p1++;
}

inline ll read(){
	ll s = 0, w = 1;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')
			w = -1;
		c = gc();
	}
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s * w;
}

int main(){
	
	return 0;
}
