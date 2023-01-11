#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> PII;

const int N = 10010, M = 50010 << 1;
int h[N], ne[M], e[M], w[M], idx;
int f[N];
int d[N];
bool st[N];
int n, m, b;
int l, r;

inline void add(int a, int b, int c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool dijkstra(int k){
    memset(st, 0, sizeof st);
    memset(d, 0x3f, sizeof d);

    d[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>>  heap;
    heap.push({0, 1});
    
    while(!heap.empty()){
        PII u = heap.top();
        heap.pop();

        int ver = u.second, dis = u.first;
        if(st[ver])
            continue;
        st[ver] = true;

        for(int i = h[ver]; ~i; i = ne[i]){
            int j = e[i];

            if(k < f[j])
                continue;
            
            if(d[j] > d[ver] + w[i]){
                d[j] = d[ver] + w[i];
                heap.push({d[j], j});
            }
        }
    }
    return d[n] <= b;
}

int main(){
    memset(h, -1, sizeof h);

    scanf("%d%d%d", &n, &m, &b);

    for(int i = 1; i <= n; i++){
        scanf("%d", &f[i]);
        r = max(r, f[i]);
    }

    for(int i = 1; i <= m; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    if(!dijkstra(0x7f7f7f7f)){
        puts("AFK");
        //cout << d[n] << endl;
        return 0;
    }

    l = max(f[1], f[n]);
    while(l < r){
        int mid = (l + r) >> 1;
        if(dijkstra(mid))  r = mid;
        else            l = mid + 1;
        //cout << mid << endl;
    }

    printf("%d\n", l);
    return 0;
}