/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_F
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 500010
#define ALPHABET 200
using namespace std;
char str[MAXN], pattern[MAXN], key[MAXN], alphabet[ALPHABET], temp;
int len, half, result, nextArray[MAXN];
inline int solve(const char *s, const char *pat)
{
    nextArray[0] = -1;
    int lenS = strlen(s), lenPat = strlen(pat);
    for (int i = 1, j; i < lenPat; ++i)
    {
        j = nextArray[i - 1];
        while (j >= 0 && pat[j + 1] != pat[i])
            j = nextArray[j];
        if (pat[j + 1] == pat[i])
            nextArray[i] = j + 1;
        else
            nextArray[i] = -1;
    }
    int ptr1 = 0, ptr2 = 0;
    while (ptr1 < lenS && ptr2 < lenPat)
    {
        if (pat[ptr2] == s[ptr1])
            ++ptr1, ++ptr2;
        else if (ptr2 > 0)
            ptr2 = nextArray[ptr2 - 1] + 1;
        else
            ++ptr1;
    }
    return ptr2;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    for (int i = 0; i < 26; ++i)
    {
        scanf("%c", &temp);
        alphabet[temp] = i;
        if (i < 25)
            scanf(" ");
        else
            scanf("\n");
    }
    scanf("%s", str);
    len = strlen(str);
    for (int i = 0; i < len; ++i)
        pattern[i] = 'a' + alphabet[str[i]];
    half = len / 2;
    if ((len & 1) == 1)
        ++half;
    memcpy(key, str + half, (len - half) * sizeof(char));
    result = solve(key, pattern);
    printf("%d\n", len - result);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}