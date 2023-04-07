#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const double ratio = 0.29, beta = 0.6;
int trash[N << 1], top, cnt, root;
struct node{
    int w, size, ch[2];
}tr[N << 1];

void print_node(int u){
    printf("node: %d\n", u);
    printf("weight&size: %d %d\n", tr[u].w, tr[u].size);
    printf("son: %d %d\n", tr[u].ch[0], tr[u].ch[1]);
}

void debug(){}
template<typename T, typename... Ts>
void debug(const T& u, const Ts&... us){
    print_node(u);
    debug(us...);
}

int newnode(){return top ? trash[--top] : ++cnt;}
int newnode(int x){
    int u = newnode();
    tr[u].w = x;
    tr[u].ch[0] = tr[u].ch[1] = 0, tr[u].size = 1;
    return u;
}

inline void recycle(int u){
    trash[top++] = u;
}

inline void pushup(int u){
    tr[u].size = tr[tr[u].ch[0]].size + tr[tr[u].ch[1]].size;
    tr[u].w = tr[tr[u].ch[1]].w;
}

inline int merge(int x, int y){
    int u = newnode();
    tr[u].ch[0] = x, tr[u].ch[1] = y;
    pushup(u);  return u;
}

void rotate(int u, int d){
    //右旋
    //puts("Keep Balance");
    if(d == 1){
        //把右子节点拆开，划一半到左子节点
        tr[u].ch[0] = merge(tr[u].ch[0], tr[tr[u].ch[1]].ch[0]);
        recycle(tr[u].ch[1]);
        tr[u].ch[1] = tr[tr[u].ch[1]].ch[1];
    }
    else{
        tr[u].ch[1] = merge(tr[tr[u].ch[0]].ch[1], tr[u].ch[1]);
        recycle(tr[u].ch[0]);
        tr[u].ch[0] = tr[tr[u].ch[0]].ch[0];
    }
    pushup(u);
}

void maintain(int &u){
    int d = -1;
    //不平衡
    if(tr[tr[u].ch[0]].size < tr[u].size * ratio) d = 1;
    if(tr[tr[u].ch[1]].size < tr[u].size * ratio) d = 0;
    if(d == -1) return ;
    int son = tr[u].ch[d];
    if(tr[tr[son].ch[d]].size < tr[son].size * beta)
        rotate(son, d^1);
    rotate(u, d);
}

void insert(int &u, int x){
    if(!u)  {u = newnode() ; return ;}
    //走到叶子结点之后新建节点和叶子合并
    if(tr[u].size == 1){
        u = (x <= tr[u].w ? merge(newnode(x), u) : merge(u, newnode(x)));
        return ;
    }
    x <= tr[tr[u].ch[0]].w ? insert(tr[u].ch[0], x) : insert(tr[u].ch[1], x);
    pushup(u), maintain(u);
}

void del(int &u, int x){
    if(tr[u].size == 1) {recycle(u), u = 0; return ;}
    int d = x > tr[tr[u].ch[0]].w;
    //要删除的那一边只有一个节点，把另一边接上
    if(tr[tr[u].ch[d]].size == 1){
        recycle(u), recycle(tr[u].ch[d]), u = tr[u].ch[d^1];
        return ;
    }
    del(tr[u].ch[d], x), pushup(u), maintain(u);
}

int find_rnk(int k){
    int u = root, cnt = 0;
    while(1){
        if(tr[u].size == 1) return cnt+1;
        if(k <= tr[tr[u].ch[0]].w)    u = tr[u].ch[0];
        else    cnt += tr[tr[u].ch[0]].size, u = tr[u].ch[1];
    }
}

int find_kth(int k){
    int u = root;
    while(1){
        if(tr[u].size == 1) return k == 1 ? tr[u].w : -1;
        if(k <= tr[tr[u].ch[0]].size)   u = tr[u].ch[0];
        else    k -= tr[tr[u].ch[0]].size, u = tr[u].ch[1];
    }
}

int precursor(int k){
    //cout << find_rnk(k) << endl;
    return find_kth(find_rnk(k) - 1);
}
int successor(int k){
    //cout << find_rnk(k + 1) << endl;
    return find_kth(find_rnk(k + 1));
}

int main(){
    int q;
    scanf("%d", &q);
    root = newnode(1e9);
    insert(root, -1e9);
    //debug(1, 2, 3);
    int op, x;
    while(q--){
        scanf("%d%d", &op, &x);
        switch (op)
        {
        case 1:
            insert(root, x);
            //debug(1, 2, 3, 4, 5);
            break;
        case 2:
            del(root, x);
            break;
        case 3:
            printf("%d\n", find_rnk(x) - 1);
            break;
        case 4:
            printf("%d\n", find_kth(x + 1));
            break;
        case 5:
            printf("%d\n", precursor(x));
            break;
        case 6:
            printf("%d\n", successor(x));
            break;
        }
    }
    return 0;
}
