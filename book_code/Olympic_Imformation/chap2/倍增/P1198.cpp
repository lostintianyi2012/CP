/* 
 * Author:lostintianyi
 * Date:2023.1.25
 * Problem:P1198 最大数
 * Tag:ST table
 */
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 2e5 + 10;
long long st[22][N];
int lg[N];
int n = 0;
int L;
int m, mod;

int main(){
    scanf("%d%d", &m, &mod);
    for(int i = 2; i <= m; i++){
        lg[i] = lg[i >> 1] + 1;
    }

    long long last = 0;
    for(int i = 1; i <= m; i ++){
        char op;
        cin >> op;

        if(op == 'A'){
            long long a;
            scanf("%lld", &a);

            st[0][++n] = (a + last) % mod;
            for(int k = 1; n - (1 << k) + 1 > 0; k++){
                st[k][n] = max(st[k-1][n], st[k-1][n - (1 << (k-1))]);
            }
        }
        else{
            int len;
            scanf("%lld", &len);
            int l = n - len + 1;
            int k = lg[len];
            long long ans = max(st[k][n], st[k][l + (1 << k) - 1]);
            last = ans;
            printf("%lld\n", ans);
        }
    }
    return 0;
}