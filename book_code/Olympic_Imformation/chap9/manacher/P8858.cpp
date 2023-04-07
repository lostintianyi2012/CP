#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pll;
const int N = 5e5 + 10;
int n;
pll point[N];
int tr[N];

int lowbit(int x){
	return x & (-x);
}

void add(int x, int k){
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += k;
}

int query(int x){
	int ans = 0;
	for(int i = x; i; i -= lowbit(i))
		ans += tr[i];
	return ans;
}

bool cmp(pll a, pll b){
	return a.second == b.second ? a.first < b.first : a.second < b.second;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d%d", &point[i].first, &point[i].second);

		std::sort(point + 1, point + 1 + n, cmp);

		//是2的情况
		if(point[n >> 1].second != point[(n >> 1) + 1].second){
			printf("2\n");
			goto end;
		}

		std::sort(point + 1, point + 1 + n);

		if(point[n >> 1].first != point[(n >> 1) + 1].first){
			printf("2\n");
			goto end;
		}

		//是3的情况
		for(int i = 1; i <= n;){
			int col = point[i].first;

			while(i <= n && point[i].first == col){
				add(point[i].second, 1);
				i++;
			}

			int l = 1, r = n + 1;
			while(l < r){
				int mid = l + r >> 1;
				int num = i - query(mid) - 1;
				if(num == (n >> 1)){
					printf("3\n");
					goto end;
				}
				if(num >= (n >> 1))	l = mid + 1;
				else r = mid;
			}
		}

		memset(tr, 0, sizeof tr);
		//加一列，二分
		for(int i = n; i >= 1;){
			int col = point[i].first;

			while(i >= 1 && point[i].first == col){
				add(point[i].second, 1);
				i--;
			}

			int l = 1, r = n;
			while(l < r){
				int mid = l + r >> 1;
				int num = query(mid);

				if(num == (n >> 1)){
					printf("3\n");
					goto end;
				}

				if(num < (n >> 1))	l = mid + 1;
				else r = mid;
			}
		}
		//都不是则为4
		printf("4\n");
		end:
		memset(tr, 0, sizeof tr);
	}
	return 0;
}
