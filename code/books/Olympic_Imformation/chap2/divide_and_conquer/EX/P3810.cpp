/*
 * Author:lsty
 * Date:2023.1.31
 * Problem:P3810 三维偏序
 * Tag:CDQ分治
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
const int K = 2e5 + 10;
int n, k, idx;
int ans[N];
int tr[K];

int lowbit(int x){
    return x & -x;
}

void add(int x, int d){
    for(int i = x; i <= k; i += lowbit(i)){
        tr[i] += d;
    }
}

int query(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += tr[i];
    }
    return ans;
}

struct node{
    int x, y, z;
    int ans, cnt;
}s1[N], s2[N];

bool cmp1(node& a, node& b){
    if(a.x == b.x){
        if(a.y == b.y){
            return a.z < b.z;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool cmp2(node& a, node& b){
    if(a.y == b.y){
        return a.z < b.z;
    }
    return a.y < b.y;
}

bool Same(node& a, node &b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void cdq(int l, int r){
    if(l == r)  return ;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

    sort(s2 + l, s2 + mid + 1, cmp2);
    sort(s2 + mid + 1, s2 + r + 1, cmp2);

    //算前一半对后一半的贡献
    int i = l, j = mid + 1;
    while(j <= r){
        //正常查逆序对
        while(i <= mid && s2[i].y <= s2[j].y){
            add(s2[i].z, s2[i].cnt);
            i++;
        }
        //查有多少个小于等于s2[j].z的z
        s2[j].ans += query(s2[j].z);
        j++;
    }

    for(int k = l; k < i; k++){
        add(s2[k].z, -s2[k].cnt);
    }
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d%d%d", &s1[i].x, &s1[i].y, &s1[i].z);
    }
    sort(s1 + 1, s1 + 1 + n, cmp1);

    for(int i = 1; i <= n; i++){
        int j = i;
        while(Same(s1[i], s1[j]))
            j ++;
        
        idx ++, j --;
        s2[idx].x = s1[i].x;
        s2[idx].y = s1[i].y;
        s2[idx].z = s1[i].z;
        s2[idx].cnt = j - i + 1;
        i = j;
    }
    cdq(1, idx);
    for(int i = 1; i <= idx; i++){
        // -1 : 减去自己贡献的逆序对
        ans[s2[i].ans + s2[i].cnt - 1] += s2[i].cnt;
    }
    for(int i = 0; i < n; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}