/* 
 * Author:lsty
 * Date:2023.1.27
 * Problem:P3958 奶酪
 * Tag:DSU 卡精度
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;
typedef unsigned long long ull;
const int N = 1e3 + 10;
int fa[N];

struct node{
    long long x, y, z;
}point[N];

ull pf(long long x){
    return x * x;
}

ull dis(const node& a, const node& b){
    return pf(a.x - b.x) + pf(a.y - b.y) + pf(a.z - b.z);
}

int find(int x){
    if(x != fa[x]){
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx == fy){
        return ;
    }
    else{
        fa[fx] = fy;
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n, h;
        long long r;
        scanf("%d%d%lld", &n, &h, &r);
        for(int i = 1; i <= n; i++){
            fa[i] = i;
        }

        vector<int> st;
        vector<int> ed;
        for(int i = 1; i <= n; i ++){
            scanf("%lld%lld%lld", &point[i].x, &point[i].y, &point[i].z);
            if(point[i].z - r <= 0){
                st.push_back(i);
            }
            if(point[i].z + r >= h){
                ed.push_back(i);
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = i + 1; j <= n; j++){
                if(pf(point[i].x - point[j].x) + pf(point[j].y - point[j].y) > 4 * r * r){
                    continue;
                }

                if(dis(point[i], point[j]) <= 4 * r * r){
                    merge(i, j);
                }
            }
        }
        
        bool flag = false;
        for(int x : st){
            for(int y : ed){
                int fx = find(x), fy = find(y);

                if(fx == fy){
                    flag = true;
                    break;
                }
            }
        }

        if(flag){
            puts("Yes");
        }
        else{
            puts("No");
        }
    }
    return 0;
}