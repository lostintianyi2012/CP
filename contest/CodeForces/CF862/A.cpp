#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;
int a[N];
int num[8];
int n;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		memset(num, 0, sizeof num);

		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		for(int b = 0; b < 8; b++)
			for(int i = 1; i <= n; i++)
				if((a[i] >> b) & 1)
					num[b]++;
		int x = 0;
		for(int i = 0; i < 8; i++)
			if(num[i] & 1)
				x |= 1 << i;
		int ans = 0;
		for(int i = 1; i <= n; i++)
			a[i] ^= x, ans ^= a[i];
		if(ans == 0)
			printf("%d\n", x);
		else
			printf("%d\n", -1);
	}
	return 0;
}
