/*
 *Author:lostintianyi
 *Date:2023.1.10
 *Problem:P1419 寻找段落
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
const double eps = 1e-5;
double sum[N], b[N];
int q[N];
int a[N];
int n, s, t;

bool check(double x){
    for(int i = 1; i <= n; i++){
        b[i] = double(a[i]) - x;
    }
    
    sum[0] = 0;
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1] + b[i];
    }
    
    int hh = 1, tt = 0;
    for(int i = s; i <= n; i++){
        while(hh <= tt && sum[q[tt]] > sum[i-s])    tt--;
        q[++tt] = i - s;
        while(hh <= tt && q[hh] < i - t)    hh++;
        if(hh <= tt && sum[i] - sum[q[hh]] >= 0)    return true;
    }
    return false;
}

int main(){
    scanf("%d", &n);
    scanf("%d%d", &s, &t);

    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    double l = -10000, r = 10000;
    while(r - l > eps){
        double mid = (l+r) / 2;
        if(check(mid))  l = mid;
        else    r = mid;
    }

    printf("%.3lf\n", l);
    return 0;
}