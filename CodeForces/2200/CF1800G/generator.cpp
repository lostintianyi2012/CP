#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
mt19937 rnd(time(0));

int main(){
	int T = 10;
	cout << T << endl;
	while(T--){
		int n = 10;
		cout << n << endl;
		for(int i = 2; i <= n; i++){
			int f = ((rnd() % (i-1)) + (i-1)) % (i-1) + 1;
			cout << f << ' ' << i << endl;
		}
	}
	return 0;
}
