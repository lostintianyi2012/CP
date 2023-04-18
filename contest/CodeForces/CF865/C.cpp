#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 3e5 + 10;
const int inf = 0x3f3f3f3f;
ll a[N];
int n;

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		long long ans = 0;
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			if(i & 1)
				ans -= a[i];
			else
				ans += a[i];
		}
			
		if(ans >= 0 || (n & 1))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
