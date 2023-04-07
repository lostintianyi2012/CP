#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 255;
int g[N][N], st[N];
int f[N];
int flag = 0;
int n;

struct edge{
    int s, v, w;
    bool operator<(const edge &x){
        return this->w < x.w;
    }
};

vector<edge> q;

inline int find(int x){
    return f[x] == x ? f[x] : f[x] = find(f[x]);
}

void solve3(){
    sort(q.begin(), q.end());
    for (int i = 1; i <= n; i++){
        f[i] = i;
    }

    long long ans = 0;
    for (auto x : q){
        int f1 = find(x.s), f2 = find(x.v);
        if (f1 == f2)
            continue;
        ans += x.w;
        f[f1] = f[f2];
    }

    printf("%d %lld\n", n - 1, ans);
}

int main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &st[i]);
        // 情况1
        if (st[i] == 1)
            flag = 1;
        // 情况2
        if (flag == 0 && st[i] == 2)
            flag = 2;
    }

    // 两个都不是,那么情况3
    if (!flag){
        flag = 3;
    }

    if (flag == 3){
        int w;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                scanf("%d", &w);
                if (j > i){
                    edge a;
                    a.s = i, a.v = j, a.w = w;
                    q.push_back(a);
                }
            }
        }
        solve3();
    }

    else{
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                scanf("%d", &g[i][j]);
            }
        }

        if (flag == 2){
            long long ans = 0x7f7f7f7f;
            //暴力枚举菊花图
            for (int i = 1; i <= n; i++){
                long long tmp = 0;
                for (int j = 1; j <= n; j++){
                    tmp += g[i][j];
                }
                ans = min(tmp, ans);
            }
            printf("%d %lld\n", n - 1, ans);
        }

        if (flag == 1){
            long long ans = 0;
            int s = 0;
            for (int i = 1; i <= n; i++){
                if (st[i] == 1){
                    for (int j = i + 1; j <= n; j++){
                        s++;
                        ans += g[i][j];
                    }
                }
            }
            printf("%d %lld\n", s, ans);
        }
    }
    return 0;
}