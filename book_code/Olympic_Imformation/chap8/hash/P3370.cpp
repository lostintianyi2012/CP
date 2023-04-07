#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <set>
#include <string.h>

typedef long long ll;
using namespace std;
const ll p[3] = {469762049, 998244353, 1004535809};
const ll b = 131;
const int N = 1510;
set<ll> result[3];
char s[N];
int n;
int ans = 0;

void Hash(){
    int len = strlen(s + 1);
    ll base[3] = {0, 0, 0};
    for(int i = 1; i <= len; i++){
        for(int j = 0; j < 3; j++){
            base[j] = ((base[j] * b) + s[i]) % p[j];
        }
    }
    if(!result[0].count(base[0]) || !result[1].count(base[1]) || !result[2].count(base[2]))
        ans++;
    for(int i = 0; i < 3; i++)
        result[i].insert(base[i]);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s", s + 1);
        Hash();
    }
    printf("%d\n", ans);
    return 0;
}