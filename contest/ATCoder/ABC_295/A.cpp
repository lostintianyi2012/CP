#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;
typedef long long ll;
int n;
string s;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> s;
        if(s == "and" || s == "not" || s == "that" || s == "the" || s == "you"){
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}