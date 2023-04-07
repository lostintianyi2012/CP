#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
int n;

int take(int k)
{
    int mink = inf, maxk = -inf;
    while (k) {
        mink = min(mink, k % 10);
        maxk = max(maxk, k % 10);
        k /= 10;
    }
    return maxk - mink;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int ansk = 0;
        int ans = 0;
        int a, b;
        cin >> a >> b;
        for (int i = a; i <= min(b, a + 100); i++) {
            int k = take(i);
            if (k >= ansk)
                ansk = k, ans = i;
            // cout << k << endl;
        }
        cout << ans << '\n';
    }
    return 0;
}
