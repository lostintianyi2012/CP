#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 22;
int n;

struct node{
    int x, y;
}a[N];

bool cmp(node a, node b){
    return a.y * b.x > a.x * b.y;
}

int main(){
    while(scanf("%d", &n) != EOF){
        for(int i = 1; i <= n; i++){
            scanf("%d%d", &a[i].x, &a[i].y);
        }
        sort(a + 1, a + 1 + n, cmp);
        long long ans = 0;

        for(int i = 1; i <= n; i++){
            for(int j = i; j <= n; j++){
                ans += a[j].y * a[i].x;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}