---
tags: string, DP, kmp
---
你打算在纸上印一串字母。
为了完成这项工作，你决定刻一个印章。印章每使用一次，就会将印章上的**所有**字母印到纸上。
同一个位置的相同字符可以印多次。例如：用 `aba` 这个印章可以完成印制 `ababa` 的工作（中间的 `a` 被印了两次）。但是，因为印上去的东西不能被抹掉，在同一位置上印不同字符是不允许的。例如：用 `aba` 这个印章不可以完成印制 `abcba` 的工作。
因为刻印章是一个不太容易的工作，你希望印章的字符串长度尽可能小。
字符串长度不超过 $5\times 10^5$

考虑DP, 设 $f_i$ 表示前 $i$ 个位置的答案
那么，$f_i$ 有两种取值的情况
1. $f_i=i$ 印章上刻满所有字符显然可行
2. $f_i=f_{\pi (i)}$ 先组成最长border，再用最长border组成整个字符串
所有border一定包含在最长border中，考虑了最长border就考虑了所有border的情况
注意第二种情况并不一定成立，考虑它什么时候成立
由于 $i$ 的最长border长度为 $\pi (i)$，那么至多往先组成的字符串后加 $\pi (i)$ 个字符，则前面字符串的长度必须 $\ge i-\pi(i)$，等价于其末尾位置 $j$ 满足 $j\ge i - \pi (i)$，前面的字符串的答案又必须为 $f_{\pi (i)}$，所以我们对于每个出现的 $f_i$ 以此为答案的最长字符串的长度，每次查询 $i-\pi(i)$ 是否小于等于 $f_{\pi(i)}$ 对应的最长字符串的长度
```cpp
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

const int N = 5e5 + 10;
char s[N];
int Pi[N];
int n;
int f[N], bucket[N];

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 2; i <= n; i++){
		int j = Pi[i-1];
		while(j && s[j + 1] != s[i])
			j = Pi[j];
		if(s[j + 1] == s[i])
			j++;
		Pi[i] = j;
	}
	f[1] = 1, bucket[1] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = i;
		if(i - Pi[i] <= bucket[f[Pi[i]]])
			f[i] = f[Pi[i]];
		bucket[f[i]] = i;
	}
	printf("%d\n", f[n]);
	return 0;
}

```
