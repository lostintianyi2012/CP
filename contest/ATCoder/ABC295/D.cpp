#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
const int N = 5e5 + 10;
char s[N];
int st[2005];

int main(){
    scanf("%s", s + 1);
    st[0] = 1;
    int tmp = 0;
    long long ans = 0;
    for(int i = 1; s[i]; i++){
        tmp ^= (1 << (s[i] - '0'));
        ans += st[tmp];
        st[tmp]++;
    }
    printf("%lld\n", ans);
    return 0;
}