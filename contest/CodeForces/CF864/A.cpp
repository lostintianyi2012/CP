#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m;
        int x1, y1, x2, y2;
        cin >> n >> m >> x1 >> y1 >> x2 >> y2;
        int ans1 = 4, ans2 = 4;
        if(x1 == 1 || x1 == n){
            ans1--;
        }
        if(y1 == 1 || y1 == m){
            ans1--;
        }
        if(x2 == 1 || x2 == n){
            ans2--;
        }
        if(y2 == 1 || y2 == m){
            ans2--;
        }
        cout << min(ans1, ans2) << '\n';
    }
    return 0;
}