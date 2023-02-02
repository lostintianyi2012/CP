/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:HDU1542 Atlantis
 * Tag:扫描线
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 2e4 + 10;
double real_x[N];
int tag[N];
double len[N];

struct LINE{        //记录边
    double y;
    double l_x, r_x;
    int inout;
    LINE(){}
    LINE(double y, double x1, double x2, int IO) : 
        y(y), l_x(x1), r_x(x2), inout(IO){}
    
}line[N];

void pushup(int u,int tr_l, int tr_r){
    if(tag[u]){
        len[u] = real_x[tr_r] - real_x[tr_l];
    }
    else if(tr_l + 1 == tr_r)
        len[u] = 0;
    else
        len[u] = len[u << 1] + len[u << 1 | 1];
}

bool cmp(const LINE& a, const LINE& b){
    //正确写法
    //return a.y == b.y ? a.inout > b.inout : a.y < b.y
    return a.y < b.y;
}

void modify(int u, int l, int r, int inout, int tr_l, int tr_r){
    if(l <= tr_l && tr_r <= r){
        tag[u] += inout;
        pushup(u, tr_l, tr_r);
        return ;
    }
    else{
        if(tr_l + 1 == tr_r)
            return ;

        int mid = (tr_l + tr_r) >> 1;
        // [1,4] -> [1, 2] + [2, 4]
        if(l <= mid)    modify(u << 1, l, r, inout, tr_l, mid);
        if(r > mid)     modify(u << 1 | 1, l, r, inout, mid, tr_r);
        pushup(u, tr_l, tr_r);
    }
}

int main(){
    int n, T = 0;
    while(scanf("%d", &n) && n){
        int idx = 0;

        while(n--){
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);

            line[++idx] = LINE(y1, x1, x2,  1);
            real_x[idx] = x1;
            line[++idx] = LINE(y2, x1, x2, -1);
            real_x[idx] = x2;
        }

        sort(real_x + 1, real_x + idx + 1);
        sort(line + 1, line + idx + 1, cmp);
        int tot = unique(real_x + 1, real_x + idx + 1) - (real_x + 1);

        memset(tag, 0, sizeof tag);
        memset(len, 0, sizeof len);
        double ans = 0;
        for(int i = 1; i <= idx; i++){
            int L, R;
            ans += len[1] * (line[i].y - line[i-1].y);
            L = lower_bound(real_x + 1, real_x + 1 + tot, line[i].l_x) - real_x;
            R = lower_bound(real_x + 1, real_x + 1 + tot, line[i].r_x) - real_x;

            modify(1, L, R, line[i].inout, 1, tot);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", ++T, ans);
    }

    return 0;
}