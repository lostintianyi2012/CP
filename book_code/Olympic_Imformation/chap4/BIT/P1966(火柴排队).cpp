/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P1966 火柴排队
 * Tag:BIT
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10;
const int mod = 1e8 - 3;
int a[N], b[N], t[N];
int tr[N];
int n;
long long ans1, ans2;
int num;

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
int main(){
    std::cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        t[i] = a[i];
    }

    std::sort(t + 1, t + 1 + n);
    num = std::unique(t + 1, t + 1 + n) - t - 1;

    for(int i = 1; i <= n; i++)
        a[i] = std::lower_bound(t + 1, t + num + 1, a[i]) - t;
    
    for(int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        t[i] = b[i];
    }

    std::sort(t + 1, t + 1 + n);
    num = std::unique(t + 1, t + 1 + n) - t - 1;

    for(int i = 1; i <= n; i++)
        b[i] = std::lower_bound(t + 1, t + num + 1, b[i]) - t;
    //离散化 a, b

//    for(int i = 1; i <= n; i++)
//        printf("%d ", b[i]);
//    puts("");
    
    for(int i = 1; i <= n; i++)
        t[a[i]] = i;
    for(int i = 1; i <= n; i++)
        b[i] = t[b[i]];

//    for(int i = 1; i <= n; i++)
//        printf("%d ", b[i]);
//    puts("");

    int ans = 0;
    for(int i = n; i > 0; i--){
        add(b[i], 1);
        ans = (ans + query(b[i]-1)) % mod;
    }
    printf("%d\n", ans);
    return 0;
}