#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 2e5 + 10;
int b[N];
int a[N];
int n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i < n; i++)
            cin >> b[i];
        a[1] = b[1];
        for(int i = 2; i < n; i++)
            a[i] = min(b[i], b[i-1]);
        a[n] = b[n-1];
        for(int i = 1; i <= n; i++)
            cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}