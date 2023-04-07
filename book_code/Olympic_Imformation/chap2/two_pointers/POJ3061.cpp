#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, s;
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    int ans = 0x3f3f3f3f, sum = 0;
    for (int i = 0, j = 0; i < n; i++) {
      sum += a[i];

      if (sum >= s) {
        while (sum >= s) {
          sum -= a[j++];
        }

        ans = min(ans, i - j + 2); // 多减了一位
      }
    }
    if (ans == 0x3f3f3f3f)
      ans = 0;
    printf("%d\n", ans);
  }
  return 0;
}