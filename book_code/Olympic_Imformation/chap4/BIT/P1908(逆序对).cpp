
/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P1908 逆序对
 * Tag:BIT
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef pair<int, int> PII;
const int N = 5e5 + 10;
int t[N];
int rnk[N];
PII a[N];
int n;

int lowbit (int x){
    return x & -x;
}

void add(int k, int x){
    for(int i = k; i <= n; i += lowbit(i))
        t[i] += x;
}

int query(int k){
    int ans = 0;
    for(int i = k; i > 0; i -= lowbit(i)){
        ans += t[i];
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);

    for(int i = 1; i <= n; i++){
        rnk[a[i].second] = i;
    }
    long long ans = 0;
    for(int i = n; i > 0; i--){
        add(rnk[i], 1);
        ans += query(rnk[i]-1);
    }
    printf("%lld\n", ans);
    return 0;
}