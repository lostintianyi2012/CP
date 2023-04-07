/*
 * Author:lsty
 * Date:2023.1.28
 * This is a template of Aho Corasick automanton
 * Tag:AC自动机
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1e6 + 10;
int n;

struct Aho_Corasic{
    int tr[N][26];
    int cnt[N];
    int fail[N];
    int idx;

    void Insert(char *s){
        int u = 0;
        for(int i = 1; s[i]; i ++){
            int c = s[i] - 'a';
            
            if(!tr[u][c])   tr[u][c] = ++idx;
            u = tr[u][c];
        }
        cnt[u] ++;
    }

    void AC_init(){
        queue<int> q;
        for(int i = 0; i < 26; i ++)
            if(tr[0][i])
                q.push(tr[0][i]);
        
        while(q.size()){
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i++){
                if(tr[u][i])
                    fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
                else
                    tr[u][i] = tr[fail[u]][i];
            }
        }
    }

    int query(char *t){
        int ans = 0, u = 0;
        for(int i = 1; t[i]; i++){
            u = tr[u][t[i] - 'a'];
            
            for(int j = u; j && cnt[j] != -1; j = fail[j]){
                ans += cnt[j];
                cnt[j] = -1;
            }
        }
        return ans;
    }
}AC;

char s[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%s", s + 1), AC.Insert(s);

    AC.AC_init();
    scanf("%s", s + 1);
    printf("%d\n", AC.query(s));
    return 0;
}
