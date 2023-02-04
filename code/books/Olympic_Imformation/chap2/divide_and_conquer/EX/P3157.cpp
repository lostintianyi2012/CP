/*
 * Author:lsty
 * Date:2023.1.31
 * Problem:P3157 动态逆序对
 * Tag:CDQ分治
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>

const int N = 1e5 + 10;
int tr[N];
int n, m;
int idx;
//值到下标的一个映射
int rev[N];
int ans[N];

struct term{
    int id, t, val;
    int ans;
    //第t个被删除的
    //ans是每个元素对逆序对的贡献
}p[N];

int lowbit(int x){
    return x & -x;
}

void add(int x, int k){
    for(int i = x; i <= n; i += lowbit(i)){
        tr[i] += k;
    }
}

int query(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += tr[i];
    }
    return ans;
}

//按时间降序,id升序,(不需要的)值升序
bool cmp1(term a, term b){
    if(a.t == b.t){
        if(a.id == b.id){
            return a.val < b.val;
        }
        return a.id < b.id;
    }
    return a.t < b.t;
}

bool cmp2(term a, term b){
    return a.id < b.id;
}

void cdq1(int l,int r){
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    cdq1(l, mid);
    cdq1(mid + 1, r);

    //id[l, mid] 与 id[mid+1, r] 下标单调递增
    //t[l, mid] >= t[mid+1, r]
    std::sort(p + l, p + mid + 1, cmp2);
    std::sort(p + mid + 1, p + r, cmp2);

    //倒序插入
    int i = mid, j = r;
}

void cdq2(int l, int r){
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    cdq2(l, mid);
    cdq2(mid + 1, r);

    std::sort(p + l, p + mid + 1, cmp2);
    std::sort(p + mid + 1, p + r, cmp2);

}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        idx++
        scanf("%d", &p[idx].val);
        p[idx].id = i;
        rev[p[idx].val] = i;
    }

    for(int i = 1; i <= m; i++){
        int del;
        scanf("%d", &del);
        idx++;
        p[idx].id
    }

    for(int i = n; i > 0; i--){
        add(p[i].val, 1);
        ans[0] += query(p[i].val - 1);
    }
    memset(tr, 0, sizeof tr);

    //排序,不用去重直接CDQ
    std::sort(p + 1, p + 1 + n, cmp1);
    cdq1(1, n);
    std::sort(p + 1, p + 1 + n, cmp1);
    cdq2(1, n)
    std::sort(p + 1, p + 1 + n, cmp1);
    return 0;
}