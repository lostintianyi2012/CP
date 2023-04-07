---
tags: string, kmp
---

对于一个仅含小写字母的字符串 $a$，$p$ 为 $a$ 的前缀且 $p\ne a$，那么我们称 $p$ 为 $a$ 的 proper 前缀。

规定字符串 $Q$（可以是空串）表示 $a$ 的周期，当且仅当 $Q$ 是 $a$ 的 proper 前缀且 $a$ 是 $QQ$ 的前缀。

例如 `ab` 是 `abab` 的一个周期，因为 `ab` 是 `abab` 的 proper 前缀，且 `abab` 是 `ab+ab` 的前缀。

求给定字符串所有前缀的最大周期长度之和。

考虑一个字符串的border，假设一个border是 $a$ 则字符串可以被表示为 $aba$
挖去最后一个 $a$，再倍长这个字符串有 $abab$，则如果 $a$ 不为空串，$ab$ 即为其一个满足条件的前缀
所以只要找到所有满足条件的最短border即可得到答案，只要border非空就一直跳border就可以得到最小的公共前后缀
可以记下已经跳完的border的答案优化一下
```cpp
#include <iostream>
#include <algorithm>
#include <stdio.h>

typedef long long ll;
const int N = 1e6 + 10;
int n;
char str[N];
int Pi[N];
ll ans;

int main(){
	scanf("%d", &n);
	scanf("%s", str + 1);
	for(int i = 2; i <= n; i++){
		int j = Pi[i - 1];
		while(j && str[j + 1] != str[i])
			j = Pi[j];
		if(str[j + 1] == str[i])
			j++;
		Pi[i] = j;
	}
	
	for(int i = 2, j = 2; i <= n; i++, j = i){
		while(Pi[j])	j = Pi[j];
		if(Pi[i])
			Pi[i] = j;
		ans += i - j;
	}
	printf("%lld\n", ans);
	return 0;
}

```