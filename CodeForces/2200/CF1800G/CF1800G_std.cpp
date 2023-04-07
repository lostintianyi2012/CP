#include <bits/stdc++.h>

#define int long long
#define pb emplace_back
#define mp make_pair
#define x first
#define y second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

typedef long double ld;
typedef long long ll;

using namespace std;

mt19937 rnd(time(nullptr));

const int inf = 2e18;
const ll M = 1e9;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

int last;
map<vector<int>, int> eq;
map<int, bool> symmetrical;

int dfs(int v, int p, vector<vector<int>> &sl){
    vector<int> children;
    for(int u: sl[v]){
        if(u == p) continue;
        children.emplace_back(dfs(u, v, sl));
    }
    sort(all(children));
    if(!eq.count(children)){
        map<int, int> cnt;
        for(int e: children){
            cnt[e]++;
        }
        int odd = 0, bad = 0;
        for(auto e: cnt){
            if(e.y & 1){
                odd++;
                bad += !symmetrical[e.x];
            }
        }
        eq[children] = last;
        symmetrical[last] = odd < 2 && bad == 0;
        last++;
    }
    return eq[children];
}

void solve(int tc){
    int n;
    cin >> n;
    eq.clear();
    symmetrical.clear();
    eq[vector<int>(0)] = 0;
    symmetrical[0] = true;
    last = 1;
    vector<vector<int>> sl(n);
    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;
        sl[--u].emplace_back(--v);
        sl[v].emplace_back(u);
    }
    cout << (symmetrical[dfs(0, 0, sl)]? "YES" : "NO");
}

bool multi = true;

signed main() {
    int t = 1;
    if (multi)cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
        cout << "\n";
    }
    return 0;
}

