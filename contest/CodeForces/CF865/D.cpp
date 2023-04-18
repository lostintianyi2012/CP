#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int N = 2e3 + 10;
int n;
int rnk[N];
int p[N], q[N];

void query1(int x){
	cout << "+ " << x << endl;
	int tmp;
	cin >> tmp;
}

void query2(int x, int y){
	cout << "? " << x << ' ' << y << endl;
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		query1(n + 1), query1(n + 2);
		int l = 1, r = n;
		for(int i = 1; i <= n; i++)
			if(i & 1)
				rnk[i] = l++;
			else
				rnk[i] = r--;

		int top = 1, dis = 0;
		for(int i = 2; i <= n; i++){
			query2(1, i);
			int x;
			cin >> x;
			if(x > dis)
				top = i, dis = x;
		}

		p[top] = rnk[1];
		q[top] = rnk[n];
		for(int i = 1; i <= n; i++){
			if(i != top){
				query2(top, i);
				int x;
				cin >> x;
				p[i] = rnk[x + 1], q[i] = rnk[n - x];
			}
		}
		cout << "!";
		for(int i = 1; i <= n; i++)
			cout << " " << p[i];
		for(int i = 1; i <= n; i++)
			cout << " " << q[i];
		cout << endl;
	}
	return 0;
}
