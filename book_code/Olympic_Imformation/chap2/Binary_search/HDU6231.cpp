#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
int sum[N];
int n, k;
long long m;

inline bool check(int x){
    long long res = 0;
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1];
        if(a[i] >= x){
            sum[i] ++;
        }
    }

    for(int i = 1, j = 1; i <= n && j <= n; i ++){
        while(sum[j] - sum[i-1] < k && j <= n)    j++;
        res += n - j + 1;
    }
    return res >= m;
}

int main(){
    int T;
    scanf("%d", &T);

    while(T--){
        scanf("%d%d%lld", &n, &k, &m);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b + 1, b + n +1);

        int l = 1, r = n+1, ans;
        while(l < r){
            int mid = (l + r) >> 1;
            if(check(b[mid]))  { ans = mid, l = mid + 1;}
            else    r = mid;
        }

        printf("%d\n", b[ans]);
    }
    return 0;
}