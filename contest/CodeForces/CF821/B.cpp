#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 2e5 + 10;
int n, x, y;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        cin >> n >> x >> y;
        if(x > y)
            swap(x, y);
        //x <= y
        if(x || !y){
            cout << "-1\n";
            continue;
        }
        if((n - 1) % y){
            cout << "-1\n";
            continue;
        }
        for(int i = 2; i <= n; i += y){
            for(int j = 1; j <= y; j++)
                cout << i << ' ';
        }
        cout << '\n';
    }
    return 0;
}