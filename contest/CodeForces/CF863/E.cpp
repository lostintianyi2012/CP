#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long ll;
ll a;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;

    while(T--){
        cin >> a;
        string s;
        while(a){
            s = (char)((a % 9) + '0') + s;
            a /= 9;
        }
        for(auto c : s)
            if(c >= '4'){
                char t = c + 1;
                cout << t;
            }
            else
                cout << c;
        cout << '\n';
    }
    return 0;
}