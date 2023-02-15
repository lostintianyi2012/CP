# CDQ分治

## 基础内容
$\rm {CDQ}$ 分治可以解决的最基本的问题是三维偏序，即:
>给定 $n$ 个三元组 $(x,y,z)$, 求有多少对三元组 $(x_i,y_i,z_i),(x_j,y_j,z_j)$ 
>
>满足 $x_i\le x_j \land y_i \le y_j \land z_i \le z_j \land i \neq j$

首先去除第一维的影响，以第一维为关键字先对数组进行排序
```cpp
bool cmp1(node a, node b){
    if(a.x == b.x){
        if(a.y == b.y){
            return a.z < b.z;
        }
        else    return a.y < b.y;
    }
    else{
        return a.x < b.x;
    }
}
```
那么对于任何 $j > i$， 都有 $x_j \ge x_i$ ，问题就转化为求有多少对二元组 $(y_i, z_i)$ 与 $(y_j, z_j)$， 满足 $i < j \land y_i \le y_j \land z_i \le z_j$

也就是给定一个二元组的序列，求二维偏序。然而由于第一维的影响，这里不能对整个序列按 $y$ 为关键字，再排序一次。

**接下来是$\rm {CDQ}$ 分治在这一题里的核心内容**

序列第一维单调递增显然带来了这样的一个性质 $\forall i \in [l, k], j \in [k+1,r],有 a_i \le a_j$

这个性质虽然很显然，但是给我们带来的一个启示是：虽然不能对整个序列排序，但是可以对相邻的两个区间排序，然后统计区间内的答案，自然而然想到用类似归并排序的方式求解

<a id="main"></a>
每次把一个区间分成两半，分别递归处理两个区间，先分别对两个区间排序，然后类似归并的方式，令 $i$ 指向 $[l,mid]$， $j$ 指向 $[mid+1, r]$ ，那么，在遇到 $i \rightarrow y \le j \rightarrow y$，这个时候就只有最后一维需要考虑了，用树状数组维护即可

**细节:** 可能有三元组 $a$ 完全与三元组 $b$ 相同的情况，此时三元组 $a$ 与 $b$ 相互贡献，然后按照上面的划分方式只有前面的才能贡献后面的，所以要先合并相同的三元组

分治部分代码:
```cpp
bool cmp2(node& a, node& b){
    if(a.y == b.y){
        return a.z < b.z;
    }
    return a.y < b.y;
}

void cdq(int l, int r){
    if(l == r)  return ;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    sort(s2 + l, s2 + mid + 1, cmp2);
    sort(s2 + mid + 1, s2 + r + 1, cmp2);
    //算前一半对后一半的贡献

    int i = l, j = mid + 1;
    while(j <= r){
        while(i <= mid && s2[i].y <= s2[j].y){
            add(s2[i].z, s2[i].cnt);
            i++;
        }
        s2[j].ans += query(s2[j].z);
        j++;
    }

    for(int k = l; k < i; k++){
        add(s2[k].z, -s2[k].cnt);
    }
}
```

完整的代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
const int K = 2e5 + 10;
int n, k, idx;
int ans[N];
int tr[K];

int lowbit(int x){
    return x & -x;
}

void add(int x, int d){
    for(int i = x; i <= k; i += lowbit(i)){
        tr[i] += d;
    }
}

int query(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += tr[i];
    }
    return ans;
}

struct node{
    int x, y, z;
    int ans, cnt;
}s1[N], s2[N];

bool cmp1(node& a, node& b){
    if(a.x == b.x){
        if(a.y == b.y){
            return a.z < b.z;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool cmp2(node& a, node& b){
    if(a.y == b.y){
        return a.z < b.z;
    }
    return a.y < b.y;
}

bool Same(node& a, node &b){
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

void cdq(int l, int r){
    if(l == r)  return ;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

    sort(s2 + l, s2 + mid + 1, cmp2);
    sort(s2 + mid + 1, s2 + r + 1, cmp2);

    //算前一半对后一半的贡献
    int i = l, j = mid + 1;
    while(j <= r){
        while(i <= mid && s2[i].y <= s2[j].y){
            add(s2[i].z, s2[i].cnt);
            i++;
        }
        s2[j].ans += query(s2[j].z);
        j++;
    }

    for(int k = l; k < i; k++){
        add(s2[k].z, -s2[k].cnt);
    }
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d%d%d", &s1[i].x, &s1[i].y, &s1[i].z);
    }
    sort(s1 + 1, s1 + 1 + n, cmp1);

    for(int i = 1; i <= n; i++){
        int j = i;
        while(Same(s1[i], s1[j]))
            j ++;
        
        idx ++, j --;
        s2[idx].x = s1[i].x;
        s2[idx].y = s1[i].y;
        s2[idx].z = s1[i].z;
        s2[idx].cnt = j - i + 1;
        i = j;
    }
    cdq(1, idx);
    for(int i = 1; i <= idx; i++){
        ans[s2[i].ans + s2[i].cnt - 1] += s2[i].cnt;
    }
    for(int i = 0; i < n; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}
```

实际上，可以发现[刚刚](#main)的分治主体过程本质上是:

1. 找到序列的中点 $mid$ 
2. 把点对分成三类: 
   1. $\forall i, j\in [l, mid],s_i\preceq s_j$
   2. $\forall i\in [l, mid], j\in [mid+1, r],s_i\preceq s_j$
   3. $\forall i, j\in [mid+1, r],s_i\preceq s_j$
3. 对三类点对分别统计数量

由上面的例子可以发现，第一类和第三类点对实际上可以靠向下递归来统计，所以实际上只需要设法求出第二类点对

所以，$\rm {CDQ}$ 分治主要的难点就在于设计统计第二类点对的方法，以及观察并构造出偏序关系的能力