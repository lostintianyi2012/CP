#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <cctype>
#include <random>

using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const int inf = 0x3f3f3f3f;
int n;
ll minv, add;

mt19937 rnd(time(0));
template <int maxn>
class treap {
	int idx;
	struct node {
		int ls, rs;
		int size, rank, key;
	} tr[maxn];

	int newnode(int x)
	{
		int u;
		u = ++idx;
		tr[u].ls = tr[u].rs = 0;
		tr[u].size = 1;
		tr[u].rank = rnd(), tr[u].key = x;
		return u;
	}

	void upd(int u)
	{
		if (u)
			tr[u].size = tr[tr[u].ls].size + tr[tr[u].rs].size + 1;
	}

	void rotate(int& u, int type)
	{
		int k;
		if (type == 0) {
			k = tr[u].ls;
			tr[u].ls = tr[k].rs;
			tr[k].rs = u;
		} else {
			k = tr[u].rs;
			tr[u].rs = tr[k].ls;
			tr[k].ls = u;
		}
		tr[k].size = tr[u].size;
		upd(u);
		u = k;
	}

public:
	int root, ans;
	void Insert(int& u, int x)
	{
		if (!u) {
			u = newnode(x);
			return;
		}
		tr[u].size++;
		if (x <= tr[u].key)
			Insert(tr[u].ls, x);
		else
			Insert(tr[u].rs, x);
		if (tr[u].ls && tr[u].rank > tr[tr[u].ls].rank)
			rotate(u, 0);
		if (tr[u].rs && tr[u].rank > tr[tr[u].rs].rank)
			rotate(u, 1);
		upd(u);
	}

	void del(int& u, int k)
	{
		//旋转到叶子再删除
		tr[u].size--;
		if (tr[u].key == k) {
			if (!tr[u].ls || !tr[u].rs){
				ans++;
				u = tr[u].ls | tr[u].rs;
				return;
			}
			
			if (tr[tr[u].ls].rank <= tr[tr[u].rs].rank) {
				rotate(u, 0), del(tr[u].rs, k);
				return;
			} else {
				rotate(u, 1), del(tr[u].ls, k);
				return;
			}
		}

		if (k < tr[u].key)
			del(tr[u].ls, k);
		else
			del(tr[u].rs, k);
		upd(u);
	}

	int kth(int u, int k)
	{
		int left = tr[tr[u].ls].size + 1;
		if (k == left)
			return tr[u].key;
		if (k < left)
			return kth(tr[u].ls, k);
		else
			return kth(tr[u].rs, k - left);
	}

	void deltree(int& u)
	{
		if (!u)
			return;
		if (tr[u].ls)
			deltree(tr[u].ls);
		if (tr[u].rs)
			deltree(tr[u].rs);
		upd(u);
		u = 0, ans++;
	}

	void del_lower(int& u, int k)
	{
		if (!u)
			return;
		if (tr[u].key < k) {
			deltree(tr[u].ls);
			del_lower(tr[u].rs, k);
			del(u, tr[u].key);
		} else {
			del_lower(tr[u].ls, k);
		}
		upd(u);
	}

	int size()
	{
		return tr[root].size;
	}
};
treap<N> sbt;

int main()
{
	freopen("test.in", "r", stdin);
	scanf("%d", &n);
	scanf("%lld", &minv);
	for (int i = 1; i <= n; i++) {
		char op[2];
		int k;
		scanf("%s", op);
		scanf("%d", &k);
		if (op[0] == 'I') {
			if (k >= minv)
				sbt.Insert(sbt.root, k - add);
		} else if (op[0] == 'A') {
			add += k;
		} else if (op[0] == 'S') {
			add -= k;
			sbt.del_lower(sbt.root, minv - add);
		} else {
			if (sbt.size() >= k)
				printf("%lld\n", sbt.kth(sbt.root, sbt.size() - k + 1) + add);
			else
				puts("-1");
		}
	}
	printf("%d\n", sbt.ans);
	return 0;
}
