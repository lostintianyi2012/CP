#include <iostream>
#include <string.h>

using namespace std;

string S;
int main(){
	cin >> S;
	for(int i = 0; i < S.length(); i++){
		if(S[i] >= 'A' && S[i] <= 'Z'){
			printf("%d\n", i + 1);
			break;
		}
	}
	return 0;
}
