#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int main(){
	ll A, B;
	cin >> A >> B;
	ll ans = 0;
	while(A != B){
		if(A > B){
			if(A % B){
				ans += A / B;
				A = A % B;
			}
			else{
				ans += A / B - 1;
				break;
			}
		}
		else{
			if(B % A){
				ans += B / A;
				B = B % A;
			}
			else{
				ans += B / A - 1;
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
