#include <iostream>
#include <algorithm>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 22;
char mat[N][N], ans[N][N];
int n, m;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
void iddfs(int x, int y, int d){
    if(x < 0 || x >= n || y < 0 || y >= m)
        return ;
    if(d == 0)
        return ;
    //printf("%d %d\n", x, y);
    ans[x][y] = '.';
    for(int i = 0; i < 4; i++){
        iddfs(x + dx[i], y + dy[i], d - 1);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        scanf("%s", mat[i]);
    memcpy(ans, mat, sizeof mat);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(isdigit(mat[i][j]))
                iddfs(i, j, mat[i][j] - '0' + 1);
        }
    }

    for(int i = 0; i < n; i++)
        printf("%s\n", ans[i]);
    return 0;
}