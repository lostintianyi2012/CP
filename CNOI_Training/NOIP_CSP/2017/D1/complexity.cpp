/*
 * Author:lsty
 * Date:2023.2.6
 * Problem:NOIP 2017 D1T2 时间复杂度
 * Tag:纯模拟
 */
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>
#include <string.h>

const int L = 110;
std::string prog[L];
int line;
bool st[26];
char stk[L];
int tt;
int const_num[L], tt2;
int stop[L], tt3;

// 判断 F 和 E 的匹配情况
// 已经经过测试
bool UnMatch()
{
    int f_cnt = 0, e_cnt = 0;
    for (int i = 1; i <= line; i++) {
        if (prog[i][0] == 'F')
            f_cnt++;
        if (prog[i][0] == 'E')
            e_cnt++;
        if (e_cnt > f_cnt)
            return false;
    }
    if (e_cnt == f_cnt)
        return true;
    return false;
}

int TakeNum(int l, int r, int k)
{
    int s = 0;
    for (int i = l; i <= r; i++) {
        s = s * 10 + (prog[k][i] - '0');
    }
    return s;
}

void skip(int& i)
{
    int f_cnt = 0, e_cnt = 0;
    i++, f_cnt++;
    while (f_cnt != e_cnt) {
        char c = prog[i++][0];
        if (c == 'F')
            f_cnt++;
        if (c == 'E')
            e_cnt++;
    }
}

int Solve()
{
    int ans = 0;

    for (int i = 1; i <= line; i++) {
        // 分几类情况讨论:
        // 1.数字 + n
        // 2.n + 数字 || 大数 + 小数(显然中间遇到的所有循环都会skip掉), 开一个 bool 表示正处在这种情况中, 答案不更新
        // 3.小数 + 大数, 开一个栈维护当前这种情况的数量, 存放这种情况时的循环栈高, 更新 ans 时就是循环栈高 - 常数栈高
        std::string str = prog[i];
        if (str[0] == 'F') {
            char var = str[2];

            // 使用过就不合法, 没有使用过就加入栈中
            if (st[var - 'a'])
                return -1;
            st[var - 'a'] = true;
            stk[++tt] = var;

            // 分类讨论: 第一个是n
            if (str[4] == 'n') {
                if (str[6] != 'n')
                    stop[++tt3] = tt;
                else
                    const_num[++tt2] = tt;
            }
            // 分类讨论: 第一个是数字
            if (isdigit(str[4])) {
                int first = 4;
                while (isdigit(str[first]))
                    first++;
                first--;
                int first_num = TakeNum(4, first, i);

                int second_st = first + 2;

                // 如果第二个是n
                if (str[second_st] == 'n') {
                    // 停滞栈空
                    if (!tt3)
                        ans = std::max(ans, tt - tt2);
                    continue;
                }
                // 如果不是n
                else {
                    // 得到第二个数
                    int second_end = second_st;
                    while (isdigit(str[second_end]))
                        second_end++;
                    second_end--;
                    int second_num = TakeNum(second_st, second_end, i);

                    // 第一个小于第二个
                    if (first_num > second_num) {
                        stop[++tt3] = tt;
                    } else {
                        const_num[++tt2] = tt;
                    }
                }
            }
        }
        else {
            if (stop[tt3] == tt)
                tt3--;
            if (const_num[tt2] == tt)
                tt2--;
            char c = stk[tt];
            st[c - 'a'] = 0;
            tt--;
        }
    }
    return ans;
}

int main()
{
    //    freopen("complexity.in", "r", stdin);
    //    freopen("complexity.out", "w", stdout);
    std::string Time;
    int T;
    scanf("%d", &T);

    // 输入部分已经经过测试
    while (T--) {
        tt = 0, tt2 = 0, tt3 = 0;
        memset(st, 0, sizeof st);
        scanf("%d", &line);
        getchar();
        std::getline(std::cin, Time);

        for (int i = 1; i <= line; i++) {
            std::getline(std::cin, prog[i]);
        }

        if (!UnMatch()) {
            puts("ERR");
            continue;
        }
        int complexity = Solve();

        if (complexity == -1)
            puts("ERR");
        else {
            if (isdigit(Time[2])) {
                if (complexity == 0)
                    printf("Yes\n");
                else
                    printf("No\n");
            } else {
                int len = 4;
                while (isdigit(Time[len]))
                    len++;
                len--;
                int s = 0;
                for (int i = 4; i <= len; i++)
                    s = s * 10 + (Time[i] - '0');
                if (s == complexity)
                    printf("Yes\n");
                else
                    printf("No\n");
            }
        }
        for (int i = 1; i <= L - 1; i++)
            prog[i] = "";
    }
    return 0;
}