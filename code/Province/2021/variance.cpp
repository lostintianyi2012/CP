/*
 * Author:lsty
 * Date:2023.2.16
 * Problem:NOIP T3 方差
 * Tag:
 */
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 1e4 + 10;
int a[N];
long long ans;
int n;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        ans += n * a[i];
    }
    return 0;
}