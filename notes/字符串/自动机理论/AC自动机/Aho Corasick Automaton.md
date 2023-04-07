AC自动机实际上就是在 Trie 树上对每个节点多维护一个 Fail 指针，Fail指针指向所有字符串中是==当前字符串的最长后缀的字符串==的末尾节点
还是用OI-wiki中的图
![Fail](https://oi-wiki.org/string/images/ac-automaton4.png)
KMP可以用来解决单模匹配问题（给字符串 $S$ 和 $T$，求 $T$ 中 $S$ 的出现）
AC自动机可以解决多模匹配问题，给你一堆字符串 $S_1,S_2,S_3,\cdots S_n$，求他们各自在模板串 $T$ 中的出现情况
对 $T$ 逐位匹配，每次失配时跳转到一个最长后缀继续匹配，类似于KMP每次跳border

### AC自动机的构建
容易发现 Fail 指针总是指向深度更低的节点，可以使用 BFS 构建 AC自动机
由于 Fail 指针总是指向==当前字符串的最长后缀的字符串==的末尾节点，如果要构建当前节点的Fail指针，则先考虑其父节点的Fail指针，指向了父节点的最长后缀，那么父节点的Fail指向的节点如果有一个和当前字符相同的边连向的子节点，当前节点的Fail指向其就好了
考虑上图的节点 $9$，$8$ 指向了 $1$，同时有一个边 $\rm e$ 连向的儿子 $2$，那么 $9$ 的Fail就是节点 $2$
如果这个儿子不存在，那么就一直跳父亲Fail直到跳到该儿子存在的节点，或者跳到根节点
实际上情况二有一个优化：如果子节点不存在，那么虚拟一个父节点的Fail指针指向的节点的儿子，让当前节点的Fail指向它，容易发现这个子节点指向的节点实际上就是上面说的过程二中最终找到的节点
有一份板子代码
```cpp
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
		//BFS建图
        queue<int> q;
        for(int i = 0; i < 26; i ++)
            if(tr[0][i])
                q.push(tr[0][i]);
        
        while(q.size()){
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i++){
				//如果子节点存在, 那么其fail指针相当于父节点fail指向的节点的相同节点
                if(tr[u][i])
                    fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
				//如果子节点不存在, 那么其子节点认为是父亲的fail指向的节点的相同节点
                else
                    tr[u][i] = tr[fail[u]][i];
            }
        }
    }

    int query(char *t){
        int ans = 0, u = 0;
        for(int i = 1; t[i]; i++){
            u = tr[u][t[i] - 'a'];
            
			//找到所有是模式串前 i 个节点后缀的字符串
			//查询就跳后缀
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
```