#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 1e5 + 10;

char s[N];
char minn;
int pos;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		cin >> (s + 1);
		minn = 'z';
		pos = 0;
		for(int i = 1; i <= n; i++)
			if(s[i] <= minn)
				minn = s[i], pos = i;
		if(!pos)
			cout << (s + 1);
		else{
			cout << minn;
			for(int i = 1; i <= n; i++)
				if(i != pos)
					cout << s[i];
		}
		cout << '\n';
	}
	return 0;
}
