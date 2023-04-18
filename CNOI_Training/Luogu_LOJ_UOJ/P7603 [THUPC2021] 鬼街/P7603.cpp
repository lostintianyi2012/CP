#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
using namespace std;

using ll = long long;

constexpr int N = 1e5 + 5;

struct node {
	int x;
	ll v;
	node() {}
	node(int _a, ll _b) : x(_a), v(_b) {}
	bool operator<(const node A) const {
		return v < A.v;
	}
	bool operator>(const node A) const {
		return v > A.v;
	}
};

template<typename T>
class ParingHeap{
	struct Node{
		T val;
		Node *sibling, *child;

		Node(){}
		Node(T _val, Node *_sibling, Node *_child){
			val = _val, sibling = _sibling, child = _child;
		}
	};
	int _size = 0;

	public:
	Node* root = nullptr;
	Node* meld(Node* x, Node* y){
		if(x == nullptr)
			return y;
		if(y == nullptr)
			return x;
		if(x->val > y->val)
			swap(x, y);
		y->sibling = x->child;
		x->child = y;
		return x;
	}

	void push(T x){
		Node* y = new Node{x, nullptr, nullptr};
		root = meld(root, y);
		_size++;
	}

	void heap_merge(ParingHeap& b){
		_size += b._size;
		root = meld(root, b.root);
	}

	Node* merge(Node* x){
		if(x == nullptr || x->sibling == nullptr)
			return x;
		Node* y = x->sibling;
		Node* nxt = y->sibling;
		x->sibling = y->sibling = nullptr;
		return meld(meld(x,y), merge(nxt));
	}

	void pop(){
		Node* x = root;
		if(x == nullptr)
			return ;
		root = merge(root->child);
		delete(x);
		_size--;
	}

	T top(){
		return root->val;
	}

	bool empty(){
		return root == nullptr;
	}

	int size(){
		return _size;
	}
};

__gnu_pbds::priority_queue<node, greater<node>, pairing_heap_tag> q[N];

int n, m;
int mnp[N];
ll val[N];
bool vis[N], rung[N];
vector<int> pri, ans;
vector<ll> mx;
vector<vector<pair<int, ll>>> h;

void init(int x) {
	for (int i = 1; i <= x; ++i)
		mnp[i] = i;
	for (int i = 2; i <= x; ++i) {
		if (!vis[i])
			pri.emplace_back(i);
		for (int j : pri) {
			if (i * j > x)
				break;
			vis[i * j] = 1;
			mnp[i * j] = min(mnp[i * j], j);
			if (!vis[i]) mnp[i * j] = min(mnp[i * j], i);
			if (i % j == 0)
				break;
		}
	}
}

void Ring(int x) {
	for (auto &i : h[x])
		mx[x] -= val[i.first] - i.second, i.second = val[i.first];
	if (mx[x] <= 0) {
		rung[x] = 1;
		ans.emplace_back(x + 1);
		return;
	}
	ll tmp = ceil((double)mx[x] / h[x].size());
	for (auto i : h[x]) {
		q[i.first].push(node(x, (ll)tmp + val[i.first]));
	}
}

void add(int x, ll k) {
	val[x] += k;
	while (!q[x].empty()) {
		auto u = q[x].top();
		if (u.v <= val[x]) {
			q[x].pop();
			if (!rung[u.x])
				Ring(u.x);
		}
		else break;
	}
}

signed main() {
	cin >> n >> m;
	ll lst = 0;
	init(1e5);
	for (int i = 1; i <= m; ++i) {
		int op, x;
		ll y;
		cin >> op >> x >> y;
		y ^= lst;
		if (op == 0) {
			int pre = 0;
			while (x > 1) {
				if (mnp[x] != pre)
					add(mnp[x], y);
				pre = mnp[x];
				x /= mnp[x];
			}
			lst = ans.size();
			cout << ans.size() << " ";
			if (ans.size())
				sort(ans.begin(), ans.end());
			for (int a : ans)
				cout << a << " ";
			cout << '\n';
			ans.clear();
		}
		else {
			vector<pair<int, ll>> H;
			int pre = 0;
			while (x > 1) {
				if(mnp[x] != pre)
					H.emplace_back(mnp[x], val[mnp[x]]);
				pre = mnp[x];
				x /= mnp[x];
			}
			mx.emplace_back(y), h.emplace_back(H);
			Ring(h.size() - 1);
		}
	}
}

