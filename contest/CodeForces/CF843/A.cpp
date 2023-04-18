#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
string s;
int n;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		cin >> s;
		if(s[0] == 'a'){
			if(s[1] == 'a')
				cout << s[0] << ' ' << s[1] << ' ' << s.substr(2) << '\n';
			else{
				bool flag = false;
				for(int i = 2; i < (int)s.length(); i++)
					if(s[i] == 'a'){
						cout << s[0] << ' '  << s.substr(1, i - 1) << ' ' << s.substr(i) << '\n';
						flag = true;
						break;
					}
				if(!flag)
					cout << s.substr(0, s.length() - 2) << ' ' << s[s.length() - 2] << ' ' << s[s.length() - 1] << '\n';
			}
		}
		else{
			cout << s[0] << ' ' << s[1] << ' ' << s.substr(2) << '\n';
		}
	}
	return 0;
}
