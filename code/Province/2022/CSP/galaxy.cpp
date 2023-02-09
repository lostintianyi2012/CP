/*
 * Author:lsty
 * Date:2023.2.7
 * Problem:2022 CSP-S 星战
 * Tag:图哈希
 */
#include <iostream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <random>

using namespace std;

const int N = 5e5 + 10;
std::mt19937 rnd(time(0));
int hash_weight[N];
long long val[N];
long long all;
long long first[N];
long long dynamic;
int n, m, q;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        hash_weight[i] = rnd();
    }

    for(int i = 1; i <= n; i++)
        all += hash_weight[i];

    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        val[v] += hash_weight[u];
        first[v] = val[v];
        dynamic += hash_weight[u];
    }

    scanf("%d", &q);
    while(q--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int u, v;
            scanf("%d%d", &u, &v);
            val[v] -= hash_weight[u];
            dynamic -= hash_weight[u];
        }
        if(op == 2){
            int u;
            scanf("%d", &u);
            dynamic -= val[u];
            val[u] = 0;
        }
        if(op == 3){
            int u, v;
            scanf("%d%d", &u, &v);
            val[v] += hash_weight[u];
            dynamic += hash_weight[u];
        }
        if(op == 4){
            int u;
            scanf("%d", &u);
            dynamic += first[u] - val[u];
            val[u] = first[u];
        }
        if(dynamic == all)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}