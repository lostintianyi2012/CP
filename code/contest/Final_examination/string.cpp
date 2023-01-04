#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;
const int N = 510;
string s;
int m;
int ans;

int main(){
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    cin >> s;
    scanf("%d", &m);
    int sz = s.size();

    for(int i = 0; i < sz; i++){
        int l = i, r = i;
        for(r = i; s[r] == s[l]; r ++);
        r--;

        priority_queue<int, vector<int>, greater<int>> heap;

        int l_cnt = 0, r_cnt = 0;

        for(int j = l-1; j >= 0; j--){
            if(s[j] == s[l])
                heap.push(l - j - 1 - l_cnt++);
        }

        for(int j = r+1; j < sz; j++){
            if(s[j] == s[r])
                heap.push(j - r - 1 - r_cnt++);
        }

        int sum = 0, cnt = 0;
        while(!heap.empty() && sum + heap.top() <= m){
            sum += heap.top();
            heap.pop();
            cnt++;
        }
        ans = max(ans, cnt + r - l + 1);
        i = r;
    }
    printf("%d\n", ans);
    return 0;
}
