#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
	int T;
	cin >> T;
	while(T--){
		int n, m;
		cin >> n >> m;
		cout << "? 1 1" << endl;
		int len;
		cin >> len;
		if(len >= n){
			int x;
			cout << "? 1 " << 1 + len << endl;
			cin >> x;
			cout << "! " << x + 1 << ' ' << len + 1 << endl;
		}
		else if(len >= m){
			int x;
			cout << "? " << 1 + len << ' ' << 1 << endl;
			cin >> x;
			cout << "! " << 1 + len << ' ' << x + 1 << endl;
		}
		else{
			int x, y;

			cout << "? " << len + 1 << ' ' << 1 << endl;
			cin >> x;
			cout << "? " << 1 << ' ' << len + 1 << endl;
			cin >> y;

			if(x == y && x == len)
				cout << "! " << 1 + len << ' ' << 1 + len << endl;
			if(x < len){
				cout << "! " << 1 + len << ' ' << 1 + x << endl;
			}
			if(y < len){
				cout << "! " << 1 + y << ' ' << 1 + len << endl;
			}
		}
	}
	return 0;
}
