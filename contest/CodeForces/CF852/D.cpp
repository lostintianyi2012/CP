#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int p[N], q[N];
int rev1[N], rev2[N];
ll s[N];
int n;
ll ans;

void lessthan(int &a, int &b){
	if(a > b)	swap(a, b);
}
ll sum(ll x){
	return (x + 1) * x / 2;
}
ll len(ll x, ll y){
	return y - x + 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &p[i]), rev1[p[i]] = i;
	for(int i = 1; i <= n; i++)
		scanf("%d", &q[i]), rev2[q[i]] = i;
	int al = n, ar = 1, bl = n, br = 1;
	for(int i = 2; i <= n; i++){
		al = min(al, rev1[i - 1]);
		ar = max(ar, rev1[i - 1]);
		bl = min(bl, rev2[i - 1]);
		br = max(br, rev2[i - 1]);
		int min_al, max_ar, min_bl, max_br;
		if(rev1[i] < al)
			min_al = rev1[i] + 1, max_ar = n;
		else
			min_al = 1, max_ar = rev1[i] - 1;
		if(rev2[i] < bl)
			min_bl = rev2[i] + 1, max_br = n;
		else
			min_bl = 1, max_br = rev2[i] - 1;
		ans += 1ll * max(len(max(min_al, min_bl), min(al, bl)), 0ll) * max(len(max(ar, br), min(max_ar, max_br)), 0ll);
	}
	int pos1 = rev1[1], pos2 = rev2[1];
	lessthan(pos1, pos2);
	ans += sum(len(1, pos1 - 1));
	ans += sum(len(pos1 + 1, pos2 - 1));
	ans += sum(len(pos2 + 1, n));
	ans++;
	printf("%lld\n", ans);
	return 0;
}
