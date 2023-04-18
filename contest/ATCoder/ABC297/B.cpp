#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6 + 10;
int Bpos1, Bpos2;
int Rpos1, Rpos2;
char S[N];

int main(){
	scanf("%s", S + 1);
	Bpos1 = Bpos2 = 0;
	Rpos1 = Rpos2 = 0;
	for(int i = 1; i <= 8; i++)
		if(S[i] == 'B'){
			if(!Bpos1)
				Bpos1 = i;
			else
				Bpos2 = i;
		}
		else if(S[i] == 'R'){
			if(!Rpos1)
				Rpos1 = i;
			else
				Rpos2 = i;
		}

	bool flag = (Bpos1 - Bpos2) % 2;
	for(int k = 1; k <= 8; k++){
		if(S[k] == 'K')
			if(!(Rpos1 < k && k < Rpos2))
				flag = false;
				
	}
	if(flag)
		puts("Yes");
	else
		puts("No");
	return 0;
}

