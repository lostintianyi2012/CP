#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
int n, x1, x2, y1, y2;
int c1, c2;
int to_cen(int x){
    if(x <= c1)
        return c1 - x;
    else
        return x - c2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n >> x1 >> y1 >> x2 >> y2;
        c1 = n >> 1, c2 = (n >> 1) + 1;
        int dis1, dis2;
        dis1 = to_cen(x1);
        dis2 = to_cen(y1);
        int len1 = max(dis1, dis2);
        dis1 = to_cen(x2);
        dis2 = to_cen(y2);
        int len2 = max(dis1, dis2);
        if(len2 < len1)
            swap(len1, len2);
        cout << len2 - len1 << '\n';
    }
    return 0;
}