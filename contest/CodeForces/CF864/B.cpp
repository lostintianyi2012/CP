#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
const int N = 1e3 + 10;
int mat[N][N];
int n, k;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                cin >> mat[i][j];
        if(n == 1){
            cout << "YES\n";
            continue;
        }
        
        int ans = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(mat[i][j] != mat[n - i + 1][n - j + 1])
                    ans++;
       ans >>= 1;
       if(ans <= k && ((n & 1) || ((k & 1) == (ans & 1))))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}