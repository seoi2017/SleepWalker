/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_A
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 1010
using namespace std;
string str[MAXN];
int n, minLen, cntPre, cntPost;
bool tag;
char chr;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> n;
    minLen = 0x3F3F3F3F;
    for (int i = 0; i < n; ++i)
    {
        cin >> str[i];
        minLen = min(minLen, (int)str[i].length());
    }
    cntPre = 0;
    for (int i = 0; i < minLen; ++i)
    {
        tag = true;
        chr = str[0][i];
        for (int j = 0; j < n; ++j)
            if (str[j][i] != chr)
            {
                tag = false;
                break;
            }
        if (tag == false)
            break;
        ++cntPre;
    }
    cntPost = 0;
    for (int i = 0; i < minLen; ++i)
    {
        tag = true;
        chr = str[0][str[0].length() - i - 1];
        for (int j = 0; j < n; ++j)
            if (str[j][str[j].length() - i - 1] != chr)
            {
                tag = false;
                break;
            }
        if (tag == false)
            break;
        ++cntPost;
    }
    cout << cntPre * cntPost << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}