#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
__int128 animal;
__int128 type;
int n, m, c, k;

void write(__int128 x) {
  if (x < 0) {
    x = -x;
    putchar('-');
  }
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}

int main(){
    freopen("zoo.in", "r", stdin);
    freopen("zoo.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &c, &k);
    for(int i = 1; i <= n; i++){
        ull t;
        scanf("%llu", &t);
        //已经选过的饲料可以选
        animal |= t;
    }
    for(int i = 1; i <= m; i++){
        int p, q;
        scanf("%d%d", &p, &q);
        __int128 t = ((__int128)1 << p);
        type |= t;
    }
    __int128 full = 0;
    for(int i = 0; i < k; i++){
        full |= ((__int128)1 << i);
    }
    //不存在饲料的二进制位可以选
    __int128 not_take = full ^ type;
    __int128 able = not_take | animal;
    //总共有多少个可以选
    __int128 num = 1;
    while(able){
        if(able & 1)
            num <<= 1;
        able >>= 1;
    }
    //减去已经选过的动物
    write(num - n);
    printf("\n");
    return 0;
}