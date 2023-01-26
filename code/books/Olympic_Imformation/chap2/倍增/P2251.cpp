/*
 * Author:lostintianyi
 * Date:2023.1.25
 * Problem:质量检测
 * Tag:Monotone queue
 */
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 1000010;
int a[N];
deque<int> q;
int n, m;

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    for(int i = 1; i <= n; i++){
        while(!q.empty() && a[q.back()] > a[i]) q.pop_back();
        q.push_back(i);
        if(i >= m){
            while(!q.empty() && q.front() <= i-m)   q.pop_front();
            printf("%d\n", a[q.front()]);
        }
    }

    return 0;
}