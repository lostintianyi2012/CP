/*
 * Author:lsty
 * Date:2023.1.28
 * Problem:P2414 阿狸的打字机
 * Tag:AC自动机
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 1e5 + 10;
char s[N];
char stk[N], tt;

struct Aho_Corasick{
    int tr[N][26];
    int fail[N];
    int cnt[N];
    int idx;

    void Insert(int top){
        int u = 0;
        for(int i = 1; i <= top; i++){
            int c = stk[i] - 'a';
            if(!tr[u][c])   tr[u][c] = ++idx;
            u = tr[u][c];
        }
        cnt[u] ++;
    }

    void build(){
        std::queue<int> q;
        for(int i = 0; i < 26; i++){
            if(!tr[0][i])
                q.push(tr[0][i]);
        }

        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i++){
                if(tr[u][i]){
                    fail[tr[u][i]] = tr[fail[u]][i];
                    q.push(tr[u][i]);
                }
                else
                    tr[u][i] = tr[fail[u]][i];
            }
        }
    }

    int query(int u){
        
    }
}AC;

int main(){
    scanf("%s", s + 1);
    for(int i = 1; s[i]; i++){
        if(s[i] == 'B')
            tt--;
        else if(s[i] == 'P')
            AC.Insert(tt);
        else
            stk[++tt] = s[i];
    }

    return 0;
}