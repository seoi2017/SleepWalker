/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_E
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <list>
#include <deque>
#include <cstdlib>
#define MAXN 100010
#define MINN -100010
using namespace std;
typedef list<int>::iterator iter;
int n;
list<int> lst;
deque<pair<iter, iter>> ope;
deque<iter> nxt;
inline void scan()
{
    iter top = lst.begin(), last;
    for (iter it = lst.begin(); it != lst.end(); ++it)
    {
        if (*it >= *top)
            top = it;
        else
        {
            last = top;
            while (*it < *last)
                last = it++;
            ope.push_back(make_pair(top, last));
            top = it;
        }
    }
}
inline void solve()
{
    iter st, en, temp;
    while (ope.size() > 0)
    {
        st = ope.front().first;
        en = ope.front().second;
        ope.pop_front();
        temp = --lst.erase(st, ++en);
        if (nxt.size() == 0 || temp != *(--nxt.end()))
            nxt.push_back(temp);
    }
}
inline void nextScan()
{
    iter st, en, last, edge;
    bool del = false;
    while (nxt.size() > 0)
    {
        en = st = *nxt.begin();
        nxt.pop_front();
        if (nxt.size() > 0)
            edge = nxt.front();
        else
            edge = --lst.end();
        while (*en >= *st && en != edge)
            last = st = en++;
        while (*en < *last)
        {
            del = true;
            if (nxt.front() == en)
                nxt.pop_front();
            last = en++;
        }
        if (en != edge || del == true)
        {
            ope.push_back(make_pair(st, --en));
            del = false;
        }
    }
}
inline void print(int x = 1)
{
    for (iter it = lst.begin(); it != lst.end(); ++it)
        if (*it != MINN && *it != MAXN)
            printf("%d ", *it);
    // if (x != 0)
        printf("\n");
};
inline void debugOutputOpe()
{
    for (deque<pair<iter, iter>>::iterator it = ope.begin(); it != ope.end(); ++it)
        printf("[%d,%d]", *(it->first), *(it->second));
    printf("\n");
}
inline void debugOutputNxt()
{
    for (deque<iter>::iterator it = nxt.begin(); it != nxt.end(); ++it)
        printf("[%d]", *(*it));
    printf("\n");
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
        scanf("%d", &n);
        lst.clear();
        lst.push_back(MINN);
        for (int i = 0, temp; i < n; ++i)
        {
            scanf("%d", &temp);
            lst.push_back(temp);
        }
        lst.push_back(MAXN);
        scan();
        while (ope.size() > 0)
        {
            // debugOutputOpe();
            solve();
            // debugOutputNxt();
            // print();
            nextScan();
        }
        print(T);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
/*
11
13
2897 4329 3309 3918 4379 592 4792 3886 1288 1434 1521 2229 2031
7
7 8 4 6 3 2 5 
27
2881 1631 655 3084 3249 3689 1081 3092 4517 3225 751 2561 4086 4096 2046 154 4746 2141 2070 2873 3700 3555 4889 1621 4686 1462 1751
24
1245 888 3451 3812 1569 3359 2479 2104 3541 1639 2385 4229 3285 923 2720 703 2268 853 2315 4433 3322 4861 3123 2061
17
20052 60451 81143 72120 42211 208 84458 47579 95100 70565 89434 23629 29979 49489 8640 14209 77996
10
1 4 4 3 2 8 9 4 5 7
5
1 8 6 2 4
8
9 2 5 6 3 8 1 9
6
5 8 2 3 1 4
8
43749 69820 20664 99174 44806 7159 19013 73479
*/