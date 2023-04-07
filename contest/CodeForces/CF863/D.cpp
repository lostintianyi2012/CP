#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 55;
ll fib[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    fib[0] = fib[1] = 1;
    for(int i = 2; i < N; i++)
        fib[i] = fib[i-1] + fib[i-2];

    int T;
    cin >> T;
    while(T--){
        int n, x, y;
        cin >> n >> x >> y;
        bool flag = true;
        ll l = 1, r = fib[n + 1];
        ll u = 1, d = fib[n];

        for(int i = n; i >= 2; i--){
            if(r - l + 1 > d - u + 1){
                //贪心放正方形
                if(y > l + fib[i] - 1)
                    l += fib[i];
                else if(y < r - fib[i] + 1)
                    r -= fib[i];
                else{
                    flag = false;
                    break;
                }
            }
            else{
                if(x > u + fib[i] - 1)
                    u += fib[i];
                else if(x < d - fib[i] + 1)
                    d -= fib[i];
                else{
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? "YES" : "NO");
        cout << '\n';
    }
    return 0;
}