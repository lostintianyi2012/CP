#include <iostream>
#include <algorithm>
#include <string.h>

bool a[5][5][5][5][5][5][5][5][5];
double ans[5][5][5][5][5][5][5][5][5];
double p[10][5];

double dfs(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9){
	if(a[p1][p2][p3][p4][p5][p6][p7][p8][p9])
		return ans[p1][p2][p3][p4][p5][p6][p7][p8][p9];
	a[p1][p2][p3][p4][p5][p6][p7][p8][p9] = 1;
	int t[10] = {0, p1, p2, p3, p4, p5, p6, p7, p8, p9};
	double cnt = 0, sum = 0;
	for(int i = 1; i <= 9; i++)
		for(int j = i + 1; j <= 9; j++){
			if(t[i] > 0 && t[j] > 0 && p[i][t[i]] == p[j][t[j]]){
				t[i]--, t[j]--;
				sum += 1;
				cnt += dfs(t[1], t[2], t[3], t[4], t[5], t[6], t[7], t[8], t[9]);
				t[i]++, t[j]++;
			}
		}
	if(sum > 0)
		ans[p1][p2][p3][p4][p5][p6][p7][p8][p9] = cnt / sum;
	return ans[p1][p2][p3][p4][p5][p6][p7][p8][p9];
}

int main(){
	while(1){
		memset(a, 0, sizeof a);
		memset(ans, 0, sizeof ans);
		a[0][0][0][0][0][0][0][0][0] = 1;
		ans[0][0][0][0][0][0][0][0][0] = 1.0;

		for(int i = 1; i <= 9; i++){
			std::string s1, s2, s3, s4;
			if(!(std::cin >> s1 >> s2 >> s3 >> s4))
				goto end;
			p[i][1] = s1[0] - '0';
			p[i][2] = s2[0] - '0';
			p[i][3] = s3[0] - '0';
			p[i][4] = s4[0] - '0';
		}
		printf("%.6lf\n", dfs(4, 4, 4, 4, 4, 4, 4, 4, 4));
	}
	end:
	return 0;
}
