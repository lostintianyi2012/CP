#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int M = 1e5 + 10;
int a[M];
int n, m, k;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-')
			w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = getchar();
	}
	return s * w;
}

void solve(){
	int rep = n / k;
	int cnt = n % k;
	int time = 0;

	if(cnt)
		rep ++;

	for(int i = 1; i <= m; i++){
		if(a[i] == rep && cnt){
			time++;
			if(time > cnt){
				puts("NO");
				return ;
			}
		}
			
		if(a[i] > rep){
			puts("NO");
			return;
		}
	}
	puts("YES");
	return ;
}

int main(){
	int t;
	t = read();
	while(t--){
		n = read(), m = read(), k = read();
		for(int i = 1; i <= m; i++)
			a[i] = read();
		solve();
	}
	return 0;
}
