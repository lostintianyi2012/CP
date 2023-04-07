/*
 *Author:lostintianyi 
 *Date:2023/1/10
 *Problem:P1102 A-B数对
 */
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;
const int N = 2e5 + 10;
int a[N];
int n, c;

int main(){
    scanf("%d%d", &n, &c);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + 1 + n);
    
    ll ans = 0;
    for(int i = 1,j = 1, k = 1; i <= n; i++){
        while(j <= n && a[i] - a[j] > c)    j++;
        while(k <= n && a[i] - a[k] >= c)   k++;
//        cout << "i:" << i << endl;
//        cout << "j:" << j << endl;
//        cout << "k:" << k << endl;
        ans += (k-1) - j + 1;
    }

    printf("%lld\n", ans);
    return 0;
}