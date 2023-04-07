#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;
string s;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		cin >> s;
		bool ok = false;
		for(int i = 0; i < s.length() - 1; i++){
			if(s[i] == 'L' && s[i + 1] == 'R'){
				printf("%d\n", i + 1);
				ok = true;
				break;
			}
			else if(s[i] == 'R' && s[i + 1] == 'L'){
				printf("%d\n", 0);
				ok = true;
				break;
			}
		}
		if(ok)
			continue;
		else
			puts("-1");
	}
	return 0;
}
