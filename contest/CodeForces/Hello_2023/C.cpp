#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>

typedef long long ll;
using namespace std;
const int N = 2e5 + 10;
int a[N];
ll s[N];
int n, m;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}
		ll prefix = 0, suffix = 0;
		priority_queue<int, vector<int>, less<int>> pre;
		priority_queue<int, vector<int>, greater<int>> suf;

		int cnt = 0;
		for(int i = m; i > 1; i--){
			prefix += a[i];
			pre.push(a[i]);
			while(prefix > 0){
				prefix -= 2 * pre.top();
				pre.pop();
				cnt++;
			}
		}
		for(int i = m + 1; i <= n; i++){
			suffix += a[i];
			suf.push(a[i]);
			while(suffix < 0){
				suffix -= 2 * suf.top();
				suf.pop();
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
