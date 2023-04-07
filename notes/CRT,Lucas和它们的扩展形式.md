---
aliases: CRT,Lucas和它们的扩展形式
tags: 数论, 组合计数
type: algorithm
---
# CRT、Lucas和ExCRT、ExLucas

## CRT(中国剩余定理)

CRT 用于求解形如
$$
\left \{
\begin{matrix}
x\equiv a_1 \pmod {m_1}\\
x\equiv a_2 \pmod {m_2}\\
x\equiv a_3 \pmod {m_3}\\
\cdots\cdots\\
x\equiv a_k \pmod {m_k}
\end{matrix}
\right.
$$
的**一元线性同余方程组**，其中 $m_1, m_2, \cdots, m_k$ 两两互质

### 过程

令 $M=\prod_{i=1}^{k} m_i$，则

对于每个 $i$ ：

令 $n_i=\dfrac{M}{m_i}$

随后 $n_i$ 在 $\bmod m_i$ 意义下的逆元 $n_i^{-1}$

令 $c_i=m_i m_i^{-1}$，这里不对 $n_i$ 取模

$x$ 在 $\bmod n$ 意义下有唯一解，
$$
x=\sum_{i=1}^{k}a_ic_i \pmod n
$$

```cpp
#include <iostream>
#include <algorithm>
#include <math.h>

typedef long long ll;
const int N = 12;
ll a[N], m[N], Mi[N], M = 1, X = 0;
ll n;

char buf[1 << 20], *p1, *p2;
inline char gc(){
	if(p1 == p2){
		p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
	}
	return p1 == p2 ? EOF : *p1++;
}

ll read(){
	int w = 1;
	ll s = 0;
	char c = gc();
	while(!isdigit(c)){
		if(c == '-')
			w = -1;
		c = gc();
	}
	while(isdigit(c)){
		s = (s << 3) + (s << 1) + (c ^ 48);
		c = gc();
	}
	return s *= w;
}

void exgcd(ll a, ll b, ll &d, ll &x, ll &y){
	if(b == 0){
		d = a;
		x = 1, y = 0;
		return ;
	}
	exgcd(b, a % b, d, y, x);
	y -= a / b * x;
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++){
		m[i] = read();
		a[i] = read();
		M *= m[i];
	}
	for(int i = 1; i <= n; i++){
		Mi[i] = M / m[i];
		ll x = 0, y = 0;
		ll d;
		exgcd(Mi[i], m[i], d, x, y);
		X += a[i] * Mi[i] * (x < 0 ? x + m[i] : x);
	}
	printf("%lld\n", X % M);
	return 0;
}
```

## Lucas定理
