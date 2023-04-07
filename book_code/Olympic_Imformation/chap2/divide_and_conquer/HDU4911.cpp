/*
 * Author:lsty
 * Date:2023.1.31
 * Problem:HDU4911 Inversion
 * Tag:归并排序
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string.h>

const int N = 1e5 + 10;
int a[N];
int n, k;
long long t[N];
long long cnt;

void Merge(int l, int mid, int r)
{
    int i = l, j = mid + 1, tid = 1;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            t[tid++] = a[j++];
            cnt += mid - i + 1;
        } else
            t[tid++] = a[i++];
    }
    while (i <= mid)
        t[tid++] = a[i++];
    while (j <= r)
        t[tid++] = a[j++];
    for (int i = 1; i < tid; i++)
        a[l + i - 1] = t[i];
}

void MergeSort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    MergeSort(l, mid);
    MergeSort(mid + 1, r);
    Merge(l, mid, r);
}

int main()
{
    while (scanf("%d%d", &n, &k) != EOF) {
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        MergeSort(1, n);
        printf("%lld\n", std::max((long long)0, cnt - k));
    }
    return 0;
}