#include<cstdio>
#include<cstring>
const int MAXN=1010;
const int MAXM=210;
const int mod=1e9 + 7;
int f[2][MAXM][MAXM][2];
char a[MAXN],b[MAXM];
int n,m,k;
int now=1;

void dp(){
    f[0][0][0][0]=f[1][0][0][0]=1;
    for(int i=1;i<=n;i++,now^=1)
        for(int j=1;j<=m;j++)
            for(int p=1;p<=k;p++){
                if(a[i]==b[j]){
                    f[now][j][p][0]=(f[now^1][j][p][0] + f[now^1][j][p][1]) % mod;
                    f[now][j][p][1]=(f[now^1][j-1][p][1] +
                                    (f[now^1][j-1][p-1][0] + f[now^1][j-1][p-1][1]) % mod) % mod;
                }
                else{
                    f[now][j][p][0]=(f[now^1][j][p][0] + f[now^1][j][p][1]) % mod;
                    f[now][j][p][1]=0;
                }
            }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s%s",a+1,b+1);
    dp();
    printf("%d\n",(f[n&1][m][k][0] + f[n&1][m][k][1]) % mod);
    return 0;
}