假设已经有了 $k$ 个图案，令 $s=\dfrac{k}{n}$
那么通过 $t$ 次拿到一个新的图案的方法就是 $s^{t-1}(1-s)$ 
前面 $t-1$ 次都失败，最后一次成功
则期望为
$$
\sum_{t=1}^{\infty}s^{t-1}(1-s)
$$
把 $(1-s)$ 提出来
$$
(1-s)\sum_{t=1}^{\infty}ts^{t-1}
$$
令 $\sum_{t=1}^{\infty}ts^{t-1}=E$ 
则 $sE=\sum_{t=1}^{\infty}ts^t$
$$
sE=E-\sum_{t=1}^{\infty}s^{t-1}
$$
移项
$$
(1-s)E=\sum_{t=1}^{\infty}s^{t-1}
$$
所以
$$
(1-s)E=\dfrac{1}{1-s}
$$
把 $s$ 变回去
$$
\dfrac{n}{n-k}
$$
根据期望的线性性质，总期望次数即为
$$
\sum_{k=0}^{n-1} \dfrac{n}{n-k}
$$
$$
n\sum_{k=1}^{n} \dfrac{1}{k}
$$
容易发现这是调和级数，预处理