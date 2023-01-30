/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P3948 数据结构
 * Tag:prefix sum
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 8010;
long long d[N];
long long s[N];
int ans[N];
int n, opt, mod, minn, maxn;

void add(int x, int y, int k){
    d[x] += k, d[y + 1] -= k;
}

void recover(){
    for(int i = 1; i <= n; i++){
        s[i] = s[i-1] + d[i];
        long long val = s[i] * i % mod;

        if(val >= minn && val <= maxn)
            ans[i] = ans[i-1] + 1;
        else
            ans[i] = ans[i-1];
    }
}

int query(int x, int y){
    return ans[y] - ans[x-1];
}

int main(){
    scanf("%d%d%d%d%d", &n, &opt, &mod, &minn, &maxn);
    bool last_is_query = false;
    for(int i = 1; i <= opt; i++){
        char op;
        int x, y;
        getchar();
        scanf(" %c %d %d", &op, &x, &y);
        if(op == 'A'){
            int k;
            scanf("%d", &k);
            add(x, y, k);
            last_is_query = false;
        }
        else{
            if(last_is_query){
                printf("%d\n", query(x, y));
            }
            else{
                recover();
                printf("%d\n", query(x, y));
                last_is_query = true;
            }
        }
    }

    int final;
    scanf("%d", &final);
    recover();
    for(int i = 1; i <= final; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x, y));
    }
    return 0;
}