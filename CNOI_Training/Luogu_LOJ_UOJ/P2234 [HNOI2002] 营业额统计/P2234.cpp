#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <random>
#include <cmath>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 4e4 + 10;
const int inf = 0x3f3f3f3f;

mt19937 rnd(time(0));

template<int size>
class treap{
	queue<int> q;
	int idx = 0;
	struct node{
		int ls, rs;
		int rank, key;
	}tr[size];
	
	int newnode(int x){
		int u;
		if(!q.empty()){
			u = q.front();
			q.pop();
		}
		else
			u = ++idx;
		tr[u].ls = tr[u].rs = 0;
		tr[u].key = x, tr[u].rank = rnd();
		return u;
	}
	
	void rotate(int &u, int type){
		int k;
		if(type == 0){
			k = tr[u].ls;
			tr[u].ls = tr[k].rs;
			tr[k].rs = u;
		}
		else{
			k = tr[u].rs;
			tr[u].rs = tr[k].ls;
			tr[k].ls = u;
		}
		u = k;
	}
	public:
	int root = 0;
	void Insert(int &u, int x){
		if(u == 0){
			u = newnode(x);
			return ;
		}
		if(x <= tr[u].key)
			Insert(tr[u].ls, x);
		else
			Insert(tr[u].rs, x);
		if(tr[u].ls && tr[u].rank > tr[tr[u].ls].rank)
			rotate(u, 0);
		if(tr[u].rs && tr[u].rank > tr[tr[u].rs].rank)
			rotate(u, 1);
	}

	int Precursor(int u, int k){
		if(u == 0)	return -inf;
		if(tr[u].key == k)	return tr[u].key;
		if(k < tr[u].key)	return Precursor(tr[u].ls, k);
		int tmp = Precursor(tr[u].rs, k);
		if(tmp == -inf)	return tr[u].key;
		return tmp;
	}
	int Successor(int u, int k){
		if(u == 0)	return -inf;
		if(tr[u].key == k)	return tr[u].key;
		if(k > tr[u].key)	return Successor(tr[u].rs, k);
		int tmp = Successor(tr[u].ls, k);
		if(tmp == -inf)	return tr[u].key;
		return tmp;
	}
};

treap<N> bst;
int n, a[N];
ll ans;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	ans += a[1];
	bst.Insert(bst.root, a[1]);
	for(int i = 2; i <= n; i++){
		int pre = bst.Precursor(bst.root, a[i]);
		int suf = bst.Successor(bst.root, a[i]);
		int dp = inf, ds = inf;
		if(pre != -inf)
			dp = abs(a[i] - pre);
		if(suf != -inf)
			ds = abs(a[i] - suf);
		int d = min(dp, ds);
		ans += d;
		bst.Insert(bst.root, a[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
