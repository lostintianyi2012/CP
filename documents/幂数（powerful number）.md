# 幂数（powerful number）

定义 powerful number 的为如下集合的中的元素：

$$
{a^2b^3|a,b \in \mathbb{N^+}}
$$

对于积性函数 $f(n)$，设其在 $p^e$ 时的函数为 $f_\tau$，在 $p$ 时的函数为 $g$，且 $g(1)=1$，则 $F(n)=\sum_{i=1}^{n}f(i)$ 可以用幂数求解

当然，在 $p^e$ 处的 $g$ 是需要自己搞的，一般而言直接和 $p$ 处一致即可

然后需要搞出一个函数 $h$，满足 $h=\frac{f}{g}$，即 $h \times g = f$

考虑在质数时的情况，有 $g(n)=f_\tau(n)=\sum_{i=0}^{1}g(n^i)h(n^{1-i})=g(1)h(n)+g(n)h(1)=h(n)+g(n)$，即 $h(n)=0$

考虑 $n$ 是质数且 $e \ge 2$ 时，$h(n^e)$ 时的值，由于 $f_\tau(n^e)=\sum_{i=0}^{e}g(n^i)h(n^{e-i})$，则有 $h(n^e)=f_\tau(n^e)-\sum_{i=1}^{e}g(n^i)h(n^{e-i})$

展开可得：

$$
\begin{aligned}
h(n^e)
=&f_\tau(n^e)-\sum_{i=1}^{e}g(n^i)h(n^{e-i})  \\
=&f_\tau(n^e)-\sum_{i=0}^{e-1}h(n^i)g(n^{e-i})  \\
\end{aligned}
$$

$$
\begin{aligned}
& h(n)=f_\tau(n)-h(1)g(n)=0 \\
& h(n^2)=f_\tau(n^2)-h(1)g(n^2)-h(n)g(n)=f_\tau(n^2)-g(n^2) \\
& h(n^3)=f_\tau(n^3)-h(1)g(n^3)-h(n)g(n^2)-h(n^2)g(n)=f_\tau(n^3)-g(n^3)-(f_\tau(n^2)-g(n^2))g(n) \\
\end{aligned}
$$

然而似乎没啥规律，具体问题具体分析吧

现在要计算 $f$ 的前缀和，有：

$$
\begin{aligned}
F(n)
=&\sum_{i=1}^{n}f(i) \\
=&\sum_{i=1}^{n}\sum_{j|i} g(j)h\left(\frac{i}{j} \right) \\
=&\sum_{j=1}^{n} h(j) \sum_{i=1}^{\left\lfloor \frac{n}{j} \right\rfloor} g(i) \\
=&\sum_{i=1}^{n}h(i)G\left( \left\lfloor \frac{n}{i} \right\rfloor \right)
\end{aligned}
$$

那么只需要枚举非 $0$ 的 $h$，然后计算 $G$ 即可，因此要求 $G$ 可以快速求和

考虑分析时间复杂度，首先计算的 powerful number 的个数（也就是 $h$ 非 $0$ 的个数）一共有 $\sqrt{n}$ 个，因此暴力枚举的复杂度是 $O(\sqrt{n} \cdot (\log n + T(f_\tau)))$

之后还要计算一共 $\sqrt{n}$ 个 $G$，这一部分的时间复杂度为 $O(\sqrt{n} \cdot T(G))$

实际上还可以更近一步，考虑枚举 powerful number 的时候计算 $h$，那么只需要枚举 $a,b$，即 $n=a^2b^3$

为了去重可以这么枚举：把质因子尽可能多的推到 $a^2$ 中去，也就是 $b$ 中无完全平方数，也就是 $|\mu(b)|=1$

也就是可以这么枚举：

```cpp
for (int a = 1; a * a <= n; a++) {
    for (int b = 1; a * a * b * b * b <= n; b++) {
        if (mu[b]) {
            powerful_number = a * a * b * b * b;
        }
    }
}
```
由于之后还要面对把某个幂数质因数分解，相当于对 $a,b$ 分别质因数分解，它们都是不超过 $\sqrt{n}$ 的，因此可以预处理每个不超过 $\sqrt{n}$ 的正整数的最小质因子是谁

对于计算 $h(n)$，只需要把 $n$ 质因数分解，设 $n=\prod p_i^{e_i}$，则 $h(n)=\prod h\left(p_i^{k_i}\right)$

于是总的时间复杂度为 $O(\sqrt{n} \cdot (\log n + T(f_\tau)+T(G)))$

那么对 $n$ 质因数分解，即对 $a,b$ 分别质因数分解，那么这一部分的总复杂度就化为了 $O(\log \log n)$

于是最终的总时间复杂度为 $O(\sqrt{n} \cdot (\log \log n + T(f_\tau)+T(G)))$

第一个例题：

对于积性函数 $f(n)$，有 $f_\tau(p^e)=p^k$，给定 $n,k$，求 $F(n)=\sum_{i=1}^{n}f(i)$

数据范围：$1 \le n \le 10^{14},1 \le k \le 5000$

时间限制：$2s$

那么有 $g(n)=f_\tau(n)=n^k$，且：

$$
\begin{aligned}
h(n^e)
=&f(n^e)-\sum_{i=0}^{e-1}h(n^i)g(n^{e-i}) \\
=&n^k-\sum_{i=0}^{e-1}h(n^i)n^{(e-i)k} \\
\end{aligned}
$$

找找规律：

$$
\begin{aligned}
& h(n)=f_\tau(n)-h(1)g(n)=0 \\
& h(n^2)=f_\tau(n^2)-g(n^2)=n^k-n^{2k} \\
& h(n^3)=f_\tau(n^3)-g(n^3)-(f_\tau(n^2)-g(n^2))g(n)=n^k-n^{3k}-(n^k-n^{2k})n^{k}=n^k-n^{2k} \\
\end{aligned}
$$

猜想 $h(n^e)=(n^k-n^{2k}) \cdot [e \ge 2]$

若 $h(n^{e-1})$ 成立，考虑 $h(n^{e})$，有：

$$
\begin{aligned}
h(n^e)
=&n^k-h(1)n^{ek}-h(n)n^{(e-1)k}-\sum_{i=2}^{e-1}(n^k-n^{2k})n^{(e-i)k} \\
=&n^k-n^{ek}-(n^k-n^{2k})\sum_{i=1}^{e-2}(n^k)^{i} \\
=&n^k-n^{ek}-n^k(1-n^{k}) \frac{n^{k(e-1)}-n^k}{1-n^k} \\
=&n^k-n^{ek}-n^{ek}+n^{2k} \\
=&n^k-n^{2k}
\end{aligned}
$$

然而这个还是很难跑 $(10^{14},5000)$ 的数据

考虑到 $G$ 的计算，实际上是自然数幂和，在这里不考虑拉格朗日插值和贝尔数，考虑用第二类斯特林数来进行自然数幂和的计算

实际上斯特林数的第二维求和是贝尔数

考虑到 $n^m=\sum_{k=0}^{m}S_{m,k}{n \choose k}k!$，同时不难得到 $\sum_{i=1}^{n}{i \choose j}={n+1 \choose j+1}$，于是有：

$$
\begin{aligned}
\sum_{i=1}^{n}i^k
=&\sum_{i=1}^{n} \sum_{j=0}^{k} S_{k,j} {i \choose j} j! \\
=&\sum_{j=0}^{k}S_{k,j} j!\sum_{i=1}^{n} {i \choose j} \\
=&\sum_{j=0}^{k}S_{k,j}j! {n+1 \choose j+1} \\
=&\sum_{j=0}^{k}S_{k,j}j! \frac{(n+1)^{\underline {j+1}}}{(j+1)!} \\
=&\sum_{j=0}^{k}S_{k,j} \frac{(n+1)^{\underline {j+1}}}{j+1} \\
\end{aligned}
$$

题外话：如何求模 $2^{32}$ 意义下的自然数幂和

由于没有逆元，但是 $(n+1)^{\underline {j+1}}$ 中一定存在一个 $j+1$ 的倍数（原因：一共有 $j+1$ 个数，模 $j+1$ 意义下一定存在一个余数为 $0$ 的

因此找出那个数即可（可能要暴力找？）

然而这个常数还是挺大的，发现每次调用的自然数幂和太多了

从直觉上来看，幂数都是比较大的，也就是说 $G\left(\left\lfloor \frac{n}{i} \right\rfloor\right)$ 中的参数很小（实际上由于 $\left\lfloor \frac{n}{i} \right\rfloor$ 只有 $\sqrt {n}$ 个取值，可以根据是否大于 $\sqrt{n}$ 用两个数组进行记录）

实践中，$\left\lfloor \frac{n}{i} \right\rfloor \le \sqrt{n}$ 的远远大于剩下的一些，因此可以直接线性筛一下 $\sqrt{n}$ 的自然数幂和

第二个例题：

对于积性函数 $f(n)$，有 $f_\tau(p^e)=p \oplus e$，给定 $n$，求 $F(n)=\sum_{i=1}^{n}f(i)$

数据范围：$1 \le n \le 10^{10}$

时间限制：$2s$

因为奇素数二进制末尾为 $1$，所以在 $p$ 处有 $f(p)=p \oplus 1=(p-1) \cdot [p \ne 2] + 3 \cdot [p=2]$

则质数处大约就是 $g(p)=\phi(p)$，特别的，$g(2)=3$