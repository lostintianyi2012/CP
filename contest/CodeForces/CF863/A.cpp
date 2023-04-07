#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        char c;
        cin >> c;
        string s;
        cin >> s;
        int i = 0;
        for(i = 0; i < n; i++)
            if(s[i] < c)
                break;
        s.insert(i, 1, c);
        cout << s << '\n';
    }
    return 0;
}