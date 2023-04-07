#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 110;
int n, m;

inline bool cmp(long long a, long long b){
	return a > b;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		priority_queue<int, vector<int>, greater<int>> q;

		for(int i = 1; i <= n; i++){
			int tmp;
			scanf("%d", &tmp);
			q.push(tmp);
		}

		for(int i = 1; i <= m; i++){
			int tmp;
			scanf("%d", &tmp);
			q.pop();
			q.push(tmp);
		}


		long long sum = 0;
		while(!q.empty()){	
			sum += q.top();
			q.pop();
		}

		printf("%lld\n", sum);
	}
	return 0;
}

