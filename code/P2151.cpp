#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 151, mod = 45989;
int n, m, s, t, x[N], y[N], cnt;
ll T;
struct matrix {
    int c[N][N];
    matrix() { memset(c, 0, sizeof(c)); }

    matrix operator*(const matrix& A)
    {
        matrix re;
        for (int i = 1; i <= cnt; i++)
            for (int j = 1; j <= cnt; j++)
                for (int k = 1; k <= cnt; k++)
                    re.c[i][j] = (re.c[i][j] + c[i][k] * A.c[k][j] % mod) % mod;
        return re;
    }
} A;

matrix pow(matrix x, ll y)
{
    matrix re;
    for (int i = 1; i <= cnt; i++)
        re.c[i][i] = 1;
    while (y) {
        if (y & 1)
            re = re * x;
        y >>= 1;
        x = x * x;
    }
    return re;
}
int main()
{
    scanf("%d%d%lld%d%d", &n, &m, &T, &s, &t);

    s++, t++;
    x[++cnt] = 0;
    y[cnt] = s;

    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        u++, v++;
        x[++cnt] = u, y[cnt] = v;
        x[++cnt] = v, y[cnt] = u;
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (i != j && i != (j ^ 1)) {
                if (y[i] == x[j])
                    A.c[i][j] = 1;
            }
        }
    }

    matrix Ans = pow(A, T);
    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (y[i] == t) {
            ans = (ans + Ans.c[1][i]) % mod;
        }
    }

    cout << ans << endl;
    return 0;
}