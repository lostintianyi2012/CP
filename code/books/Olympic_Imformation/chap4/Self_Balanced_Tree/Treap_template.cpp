/*
 * Author:lsty
 * Date:2023.1.27
 * This is a template
 * Tag:Treap
 */
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10 + 1e5 + 10;
int idx = 0;

mt19937 rnd(time(0));

inline int read(){
    int w = 1, s = 0;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-')
            w = -1;
        c = getchar();
    }
    while(isdigit(c)){
        s = (s << 3) + (s << 1) + (c ^ 48);
        c = getchar();
    }
    return w * s;
}

struct node{
    int ls, rs;
    int key, pri;
    int size;
}tr[N];

void Create(int x){
    idx++;
    tr[idx].size = 1;
    tr[idx].ls = tr[idx].rs = 0;
    tr[idx].key = x;
    tr[idx].pri = rnd();
}

void upd(int u){
    tr[u].size = tr[tr[u].ls].size + tr[tr[u].rs].size + 1;
}

void rotate(int &o, int d){
    int k;
    if(d == 1){
        k = tr[o].rs;
        tr[o].rs = tr[k].ls;
        tr[k].ls = o;
    }
    else{
        k = tr[o].ls;
        tr[o].ls = tr[k].rs;
        tr[k].rs = o;
    }
    tr[k].size = tr[o].size;
    upd(o);
    o = k;
}

void Insert(int &u, int x){
    if(u == 0){
        Create(x);
        u = idx;
        return ;
    }
    tr[u].size++;

    //小于等于的放到左子树
    if(x <= tr[u].key)   Insert(tr[u].ls, x);
    else                 Insert(tr[u].rs, x);

    if(tr[u].ls != 0 && tr[u].pri > tr[tr[u].ls].pri)   rotate(u, 0);
    if(tr[u].rs != 0 && tr[u].pri > tr[tr[u].rs].pri)   rotate(u, 1);
    upd(u);
}

void del(int &u, int x){
    tr[u].size--;
    if(tr[u].key == x){
        if(tr[u].ls == 0 && tr[u].rs == 0)  {u = 0; return ;}
        if(tr[u].ls == 0 || tr[u].rs == 0)  {u = tr[u].ls + tr[u].rs; return ;}

        if(tr[tr[u].ls].pri < tr[tr[u].rs].pri){
            rotate(u, 0); del(tr[u].rs, x); return ;
        }
        else{
            rotate(u, 1); del(tr[u].ls, x); return ;
        }
    }
    if(x <= tr[u].key)  del(tr[u].ls, x);
    else                del(tr[u].rs, x);
    upd(u);
}

int rnk(int u, int k){
    if(u == 0)  return 0;
    if(k > tr[u].key)   return tr[tr[u].ls].size + 1 + rnk(tr[u].rs, k);
    return rnk(tr[u].ls, k);
}

int kth(int u, int k){
    if(k == tr[tr[u].ls].size + 1)  return tr[u].key;
    if(k > tr[tr[u].ls].size + 1)   return kth(tr[u].rs, k - tr[tr[u].ls].size - 1);
    return kth(tr[u].ls, k);
}

int Precursor(int u, int k){
    if(u == 0)  return 0;
    //小于等于的在左子树中找
    if(k <= tr[u].key)  return Precursor(tr[u].ls, k);
    //右边没有找到
    int tmp = Precursor(tr[u].rs, k);
    if(tmp == 0)    return tr[u].key;
    return tmp;
}

int Successor(int u, int k){
    if(u == 0)  return 0;
    if(k >= tr[u].key)   return Successor(tr[u].rs, k);
    int tmp = Successor(tr[u].ls, k);
    if(tmp == 0)    return tr[u].key;
    return tmp;
}

int main(){
    srand(time(NULL));
    int root = 0;
    int m, n;
    m = read(), n = read();
    int last = 0, ans = 0;
    for(int i = 1; i <= m; i++){
        int t;
        t = read();
        Insert(root, t);
    }

    while(n--){
        int opt, x;
        opt = read(), x = read();

        x ^= last;

        if(opt == 1)
            Insert(root, x);
        else if(opt == 2)
            del(root, x);
        else if(opt == 3){
            int t = rnk(root, x) + 1;
            last = t;
            ans ^= t;
        }
        else if(opt == 4){
            int t = kth(root, x);
            last = t;
            ans ^= t;
        }
        else if(opt == 5){
            int t = Precursor(root, x);
            last = t;
            ans ^= t;
        }
        else{
            int t = Successor(root, x);
            last = t;
            ans ^= t;
        }
    }

    printf("%d\n", ans);
    return 0;
}