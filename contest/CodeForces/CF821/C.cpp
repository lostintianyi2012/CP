#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;
const int N = 1e5 + 10;
int a[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        if(n == 1){
            cout << 0 << '\n';
            continue;
        }
        cout << n - 1 << '\n';
        if((a[1] + a[n]) & 1)
            a[n] = a[1];
        else
            a[1] = a[n];
        cout << 1 << ' ' << n << '\n';
        for(int i = 2; i < n; i++)
            if((a[i] + a[1]) & 1)
                cout << 1 << ' ' << i << '\n';
            else
                cout << i << ' ' << n << '\n';
    }
    return 0;
}