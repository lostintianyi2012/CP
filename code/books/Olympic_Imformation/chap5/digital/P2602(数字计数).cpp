/*
 * Copyright© 2023 lsty. All rights reserved.
 * author: lsty
 * Problem:
 * Tag: DP
 * Date: 2023-02-20 
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdio.h>

using namespace std;
typedef long long LL;

const int N = 20;
//m[u][sum]表示最后有pos位, 前面有 sum 个 i 的所有数中 i 的数量
LL m[N][N];
int a[N];
int len;

//当前第 u 位, 要搜索的数字是 digit
//lead表示没有前导0限制, limit 表示有最高位限制
LL dfs(int u, int digit, LL sum, bool lead, bool limit){
	if(u == 0){
		return sum;
	}

	if(!limit && m[u][sum] != -1 && lead)
		return m[u][sum];

	int maxn = limit ? a[u] : 9;

	LL ans = 0;
	for(int i = 0; i <= maxn; i++){
		ans += dfs(u - 1, digit, sum + ((i == digit) && (i || lead)), lead || i, limit && (i == maxn));
	}
	if(!limit && lead)
		m[u][sum] = ans;
	return ans;
}


//统计<=num的数中数字 k 出现了多少次
LL work(LL num, int k){
	memset(m, -1, sizeof (m));
	len = 0;
	while(num){
		a[++len] = num % 10;
		num /= 10;
	}
    //a[i]存 num 的第 i 位
	return dfs(len, k, 0, false, true);
}

int main(){
	LL a, b;
	scanf("%lld %lld", &a, &b);
	for(int i = 0; i < 10; i ++){
		printf("%lld", work(b, i) - work(a - 1, i));
		i == 9 ? puts("") : printf(" ");
	}
	return 0;
}