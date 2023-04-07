#include <iostream>
#include <algorithm>
#include <string.h>
#include <bitset>
#include <vector>

typedef long long ll;
const int N = 19;
const ll mod = 1e6 + 33;
ll n, subtask, k, a[N], b[N], c[N], f[1 << N][N][2];
int nxt[N];
std::vector<ll> mat[N][3];
int m;
ll inv[N];
ll A[3][4];

//向量数乘 / 加法
std::vector<ll> operator*(ll x, std::vector<ll> y){
	for(int i = 0; i < 3; i++)
		y[i] = 1ll * x * y[i] % mod;
	return y;
}
std::vector<ll> operator+(std::vector<ll> x, std::vector<ll> y){
	for(int i = 0; i < 3; i++)
		x[i] = (x[i] + y[i]) % mod;
	return x;
}

ll f_pow(ll a, ll k = mod - 2){
	ll base = 1;
	for(; k; k >>= 1, a = (a * a) % mod){
		if(k & 1)
			base = (base * a) % mod;
	}
	return base;
}

ll bit(int k){
	return 1 << k;
}

int pop_count(int k){
	int ans = 0;
	for(; k; k >>= 1){
		ans += (k & 1);
	}
	return ans;
}

ll sub(ll a, ll b){
	a -= b;
	return a < 0 ? a + mod : a;
}

//重置这个点
void cln(int x){
	mat[x][0].clear();
	mat[x][0].resize(3);
	mat[x][1].clear();
	mat[x][1].resize(3);
}

void solve(int SET){
	int x, y, id;
	for(int i = 0; i < n; i++){
		if(SET >> i & 1)
			continue;
		id = i;
	}
	cln(id);
	//令第一项的 f_{S, i, 0} 为 x
	//第一项的 f_{S, i, 1} 为 y
	mat[id][0][1] = 1;
	mat[id][1][2] = 1;
	for(int i = (id + n - 1) % n, j = id; ; i = (i + n - 1) % n){
		if(SET >> i & 1)
			continue;
		cln(i);
		//常数项
		mat[i][0][0] = ((a[i] * f[SET | bit(i)][j][0]) + 1) % mod;
		//计算这一项用x, y表示的系数
		mat[i][0] = (b[i] * mat[j][0]) + (c[i] * mat[j][1]) + mat[i][0];
		mat[i][1][0] = ((a[i] + b[i]) % mod * f[SET | bit(i)][j][0] + 1) % mod;
		mat[i][1] = (c[i] * mat[j][1]) + mat[i][1];

		j = i;
		if(i == id)
			break;
	}

	//最后列出来 x = a_1x + a_2y + c_2 / y = b_1x + b_2y + c_2
	A[1][1] = sub(mat[id][0][1], 1);
	A[1][2] = mat[id][0][2];
	A[1][3] = sub(0, mat[id][0][0]);

	A[2][1] = mat[id][1][1];
	A[2][2] = sub(mat[id][1][2], 1);
	A[2][3] = sub(0, mat[id][1][0]);

	if(!A[1][1])
		std::swap(A[1], A[2]);
	/*============第二行减去第一行=============*/
	//第一行乘的数
	ll mul = A[2][1] * f_pow(A[1][1]) % mod;
	A[2][1] = sub(A[2][1], mul * A[1][1] % mod);
	A[2][2] = sub(A[2][2], mul * A[1][2] % mod);
	A[2][3] = sub(A[2][3], mul * A[1][3] % mod);

	//消掉第一行第二个
	mul = A[1][2] * f_pow(A[2][2]) % mod;
	A[1][1] = sub(A[1][1], mul * A[2][1] % mod);
	A[1][2] = sub(A[1][2], mul * A[2][2] % mod);
	A[1][3] = sub(A[1][3], mul * A[2][3] % mod);

	x = A[1][3] * f_pow(A[1][1]) % mod;
	y = A[2][3] * f_pow(A[2][2]) % mod;

	for(int i = 0; i < n; i++){
		if(SET >> i & 1)
			continue;
		//加上对应的系数
		f[SET][i][0] = ((x * mat[i][0][1] % mod + y * mat[i][0][2] % mod) % mod + mat[i][0][0]) % mod;
		f[SET][i][1] = ((x * mat[i][1][1] % mod + y * mat[i][1][2] % mod) % mod + mat[i][1][0]) % mod;
	}
}

int main(){
	scanf("%lld%lld", &n, &subtask);

	int cnt_1 = 0, cnt_2 = 0, cnt_3 = 0;
	for(int i = 0; i < n; i++){
		scanf("%lld%lld", &a[i], &b[i]);
		a[i] = 1ll * a[i] * f_pow(1000) % mod;
		b[i] = 1ll * b[i] * f_pow(1000) % mod;
		c[i] = sub(1, (a[i] + b[i]) % mod);
		if(a[i] == b[i] && a[i] == 0)
			cnt_1++;
		if(a[i] == c[i] && c[i] == 0)
			cnt_2++;
		if(c[i] == 0)
			cnt_3++;
	}
	if(cnt_1 >= 2 || (cnt_2 >= 2 && cnt_3 >= n)){
		puts("-1");
		return 0;
	}

	for(int i = (1 << n) - 1; i >= 0; i--){
		if(pop_count(i) >= n - 1)
			continue;
		solve(i);
	}
	printf("%lld\n", f[0][0][0]);
	return 0;
}
