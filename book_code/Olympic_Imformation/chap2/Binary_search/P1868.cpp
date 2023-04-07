/*
 * author:lostintianyi
 * date:2023.1.12
 * problem:P1868 饥饿的奶牛
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 150010;
int f[N];
int n;

struct node{
    int head, tail, val;
}seg[N];

inline int find(int l, int r, int key){
    int ans = 0;
    while(l < r){
        int mid = (l + r) >> 1;
        if(seg[mid].tail < key)   {ans = mid, l = mid + 1;}
        else    r = mid;
    }
    return ans;
}

inline bool cmp(node a, node b){
    return a.tail < b.tail;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d%d", &seg[i].head, &seg[i].tail);
        seg[i].val = seg[i].tail - seg[i].head + 1;
    }
    sort(seg + 1, seg + 1 + n, cmp);

    for(int i = 1; i <= n; i++){
        int j = find(1, i-1, seg[i].head);
        f[i] = max(f[i-1], f[j] + seg[i].val);
    }

    printf("%d\n", f[n]);
    return 0;
}