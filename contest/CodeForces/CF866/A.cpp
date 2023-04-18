#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        string s;
        cin >> s;
        int pre = s.length();
        if(pre == 1 && s[0] == '^'){
            cout << 1 << '\n';
            continue;
        }
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '_' && (i == 0 || s[i-1] != '^')){
                s.insert(i, 1, '^');
            }
        }
        if(s[s.length() - 1] == '_')
            s = s + '^';
        cout << s.length() - pre << '\n';
    }
    return 0;
}