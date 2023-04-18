#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 110;
const int inf = 0x3f3f3f3f;
ll t[N];

int main(){
	int n, d;
	cin >> n >> d;
	for(int i = 1; i <= n; i++)
		cin >> t[i];
	int ans = 0;
	int click = 0;
	for(int i = 2; i <= n; i++)
		if(t[i] - t[i-1] <= d)
			if(click == 0){
				click = t[i];
				break;
			}
	if(click == 0)
		cout << -1 << endl;
	else
		cout << click << endl;
	return 0;
}
