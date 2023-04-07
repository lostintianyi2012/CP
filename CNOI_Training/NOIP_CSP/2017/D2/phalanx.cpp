/*
 * Author:lsty
 * Date:2023.2.6
 * Problem:NOIP 2017 D2T3 列队
 * Tag:动态开点线段树
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>

const int N = 3e5 + 10, NlogN = 12000005;

int root[N];

struct node{
    int ls, rs, sum;
	//sum:当前区间空位的个数
}tr[NlogN];

int n, m, q, x, y, idx, pos, max;
std::vector<long long> v[N];

//找到这一行的第 num 个数
int query(int u, int l, int r, int num){
    if(l == r)
        return l;
    int mid = (l + r) >> 1;
	//这个区间的总个数 - 左侧空缺的个数
    int tmp = mid - l + 1 - tr[tr[u].ls].sum;
    if(num <= tmp)
        return query(tr[u].ls, l, mid, num);
    return query(tr[u].rs, mid + 1, r, num - tmp);
}

//删除原来序列的第 k 个
void update(int &u, int l, int r, int k){
	if(!u)	u = ++idx;
	tr[u].sum++;
	if(l == r)
		return ;
	int mid = (l + r) >> 1;
	if(k <= mid)	update(tr[u].ls, l, mid, k);
	else			update(tr[u].rs, mid+1, r, k);
}

long long modify_last(int x, long long y){
	//找到最后一行的x的位置
	pos = query(root[n+1], 1, max, x);
	update(root[n+1], 1, max, pos);
	long long ans;
	if(pos <= n)
		//最后一列的第pos个, 标号就是 pos*m
		ans = (long long)pos * (long long)m;
	else
		ans = v[n+1][pos - n - 1];
	v[n+1].push_back(y ? y : ans);
	return ans;
}

long long modify_row(int x, int y){
	pos = query(root[x], 1, max, y);
	update(root[x], 1, max, pos);
	long long ans;
	if(pos < m)
		//得到 ans 的序号
		ans = (long long)(x-1)*(long long)m + pos;
	else
		ans = v[x][pos - m];
	//往最后一行插入 ans
	modify_last(x, ans);
	v[x].push_back(ans);
	return ans;
}

int main(){
    scanf("%d%d%d", &n, &m, &q);
    max = std::max(n, m) + q;
	for(int i = 1; i <= q; i++){
		scanf("%d%d", &x, &y);
		printf("%lld\n", y == m ? modify_last(x, 0) : modify_row(x, y));
	}
    return 0;
}