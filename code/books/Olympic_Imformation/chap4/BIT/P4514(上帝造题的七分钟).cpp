/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P4514 上帝造题的七分钟
 * Tag:BIT
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 2100;
int t1[N][N], t2[N][N], t3[N][N], t4[N][N];
int n, m;

inline int lowbit(int x){
    return x & -x;
}

void add(int x, int y, int d){
    for(int i = x; i <= n; i += lowbit(i)){
        for(int j = y; j <= n; j += lowbit(j)){
            t1[i][j] +=         d;
            t2[i][j] +=     x * d;
            t3[i][j] +=     y * d;
            t4[i][j] += x * y * d;
        }
    }
}

int query(int x, int y){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        for(int j = y; j > 0; j -= lowbit(j)){
            ans += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] - (x + 1) * t3[i][j] + t4[i][j];
        }
    }
    return ans;
}

int main(){
    char op[2];
    scanf("%s", op);
    scanf("%d%d", &n, &m);
    while(scanf("%s", op) != EOF){
        int a, b, c, d, delta;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if(op[0] == 'L'){
            scanf("%d", &delta);
            add(a   , b  ,   delta), add(c+1 , d+1,  delta);
            add(a   , d+1,  -delta), add(c+1 , b  , -delta);
        }
        else{
            printf("%d\n", query(c, d) - query(c, b-1) - query(a-1, d) + query(a-1, b-1));
        }
    }
    return 0;
}