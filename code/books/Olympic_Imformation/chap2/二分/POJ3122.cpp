#include <bits/stdc++.h>

using namespace std;
const int N = 1e4 + 10;
const double pi = acos(-1.0), eps = 1e-5;

int n, m;
int r[N];
double area[N];

bool check(double x){
    int res = 0;
    for(int i = 1; i <= n; i++){
        res += (int)(area[i] / x);
    }
    return res >= m;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        m++;

        double max_size = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &r[i]);
            area[i] = pi * r[i] * r[i];
            max_size = max(max_size, area[i]);
        }

        double l = 0, r = max_size;
        while(r - l > eps){
            double mid = (l + r) / 2;
            if(check(mid))  l = mid;
            else    r = mid;
        }

        printf("%.4f\n", l);
    }
    return 0;
}