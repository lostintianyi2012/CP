#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;
const int N = 3;
char mat[N][N];
int n;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--){
		for(int i = 0; i < 2; i++)
			cin >> mat[i];
		set<char> s;
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				if(!s.count(mat[i][j]))
					s.insert(mat[i][j]);
		cout << s.size() - 1 << '\n';
	}
	return 0;
}
