#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;
typedef long long ll;
const int N = 12;
ll A[N];
int idx;
int n, k;
set<ll> S;

int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		cin >> A[i];
	sort(A + 1, A + 1 + n);
	S.insert(0);
	while(k--){
		ll x = *S.begin();
		S.erase(x);
		for(int i = 1; i <= n; i++)
			S.insert(x + A[i]);
	}
	cout << *S.begin() << endl;
	return 0;
}
