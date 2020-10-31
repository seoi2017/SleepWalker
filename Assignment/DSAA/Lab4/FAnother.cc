/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_F
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <forward_list>
#include <vector>
#include <cstdlib>
#define MAXLEN 210010
#define BLOCK 450
using namespace std;
typedef forward_list<vector<char>>::iterator iter;
forward_list<vector<char>> lst;
char str[MAXLEN], chr;
int n;
inline iter getPos(int &pos)
{
    for (iter it = lst.begin(); it != lst.end(); ++it)
    {
        if (pos <= it->size())
            return it;
        pos -= it->size();
    }
    return lst.before_begin();
}
inline void init(char *s)
{
    int len = strlen(s), nowPos = 0;
    lst.clear();
    vector<char> temp;
    iter it = lst.before_begin();
    while (nowPos < len)
    {
        temp.clear();
        for (int i = 0; i < BLOCK && nowPos < len; ++i, ++nowPos)
            temp.push_back(s[nowPos]);
        lst.insert_after(it, temp);
        ++it;
    }
}
inline void insert(char c, int pos)
{
    iter it = getPos(pos);
    vector<char>::iterator sit = it->begin() + pos - 1;
    it->insert(sit, c);
    if (it->size() >= 2 * BLOCK) // Split
    {
        sit = it->begin() + (it->size() / 2);
        lst.insert_after(it, vector<char>(sit, it->end()));
        it->erase(sit, it->end());
    }
}
inline char query(int pos)
{
    iter it = getPos(pos);
    return *(it->begin() + pos - 1);
}
inline void debugOutput()
{
    for (iter it = lst.begin(); it != lst.end(); ++it)
    {
        printf("[");
        for (int i = 0; i < it->size(); ++i)
            printf("%c", (*it)[i]);
        printf("]\n");
    }
    printf("=================\n");
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str);
        init(str);
        scanf("%d", &n);
        for (int i = 0, oper; i < n; ++i)
        {
            scanf("%d ", &oper);
            if (oper == 1)
            {
                scanf("%c%d", &chr, &oper);
                insert(chr, oper);
                // debugOutput();
            }
            else
            {
                scanf("%d", &oper);
                printf("%c\n", query(oper));
            }
        }
        // debugOutput();
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}