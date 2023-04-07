#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f;
vector<int> L, R;
ll ansv, ans;
ll l, r;

int val(ll x){
	int maxa = -inf;
	int mina = inf;
	while(x){
		int t = x % 10;
		maxa = max(maxa, t), mina = min(mina, t);
		x /= 10;
	}
	return maxa - mina;
}

void take(vector<int> &dig, ll x){
	dig.clear();
	ll t = x;
	while(x){
		dig.push_back(x % 10);
		x /= 10;
	}
	reverse(dig.begin(), dig.end());
	int tans = val(t);
	if(tans > ansv){
		ansv = tans;
		ans = t;
	}
}

void work(vector<int> &v){
	ll x = 0;
	for(int pos = 0; pos < v.size(); pos++){
		for(int k = 0; k <= 9; k ++){
			ll res = x;
			for(int i = pos; i < v.size(); i++)
				res = res * 10 + k;
			if(res < l || res > r)
				continue;
			int t = val(res);
			if(ansv > t){
				ansv = t;
				ans = res;
			}
		}
		x = x * 10 + v[pos];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;

	while(T--){
		cin >> l >> r;
		ansv = inf;
		take(L, l), take(R, r);
		if(L.size() != R.size()){
			for(int i = 0; i < L.size(); i++)
				cout << 9;
			cout << '\n';
			continue;
		}
		work(L), work(R);
		cout << ans << '\n';
	}
	return 0;
}
