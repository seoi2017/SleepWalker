/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_E
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <map>
#define MAXN 100010
using namespace std;
struct Node
{
    int tot, ind;
    Node(int x, int y): tot(x), ind(y) {}
    bool operator<(const Node &x) const
    {
        if (this->tot != x.tot)
            return this->tot < x.tot;
        return this->ind < x.ind;
    }
};
map<Node, int> dict;
char str[256];
bool endTag;
int n, cnt[MAXN], k, temp;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    endTag = false;
    memset(cnt, 0, sizeof(cnt));
    k = 0;
    while (scanf("%s", str))
    {
        switch (str[0])
        {
        case 'p':
            scanf("%d", &n);
            dict[Node(++cnt[n], ++k)] = n;
            break;
        case 'e':
            if (dict.empty() == true)
            {
                printf("pa\n");
                break;
            }
            temp = dict.rbegin()->second;
            printf("%d\n", temp);
            --cnt[temp];
            dict.erase(dict.rbegin()->first);
            break;
        default:
            endTag = true;
            break;
        }
        if (endTag == true)
            break;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}