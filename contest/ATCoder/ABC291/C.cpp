#include <iostream>
#include <algorithm>
#include <string.h>
#include <map>

using namespace std;
typedef pair<int, int> PII;
const int N = 2e5 + 10;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int x = 0, y = 0;
int n, idx;
char s[N];
map<PII, int> mp;

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	mp[make_pair(0, 0)] = ++idx;

	bool flag = false;
	for(int i = 0; i < n; i++){
		if(s[i] == 'U'){
			x += dx[0];
			y += dy[0];
		}
		if(s[i] == 'R'){
			x += dx[1];
			y += dy[1];
		}
		if(s[i] == 'D'){
			x += dx[2];
			y += dy[2];
		}
		if(s[i] == 'L'){
			x += dx[3];
			y += dy[3];
		}
		if(mp[make_pair(x, y)]){
			flag = true;
			break;
		}
		mp[make_pair(x, y)] = ++idx;
	}
	if(flag)
		puts("Yes");
	else
		puts("No");
	return 0;
}
