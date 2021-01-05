/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_D
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 1010
using namespace std;
int n, preOrder[MAXN], inOrder[MAXN];
struct Node
{
    int value;
    Node *lc, *rc;
    Node(const int &v) : value(v), lc(nullptr), rc(nullptr) {}
    ~Node()
    {
        delete this->lc;
        delete this->rc;
    }
};
Node* buildTree(const int &preL, const int &preR, const int &inL, const int &inR)
{
    if (preL > preR)
        return nullptr;;
    Node *node = new Node(preOrder[preL]);
    int k = 0;
    for (int i = inL; i <= inR; ++i)
        if (preOrder[preL] == inOrder[i])
        {
            k = i;
            break;
        }
    node->lc = buildTree(preL + 1, preL + k - inL, inL, k - 1);
    node->rc = buildTree(preL + k - inL + 1, preR, k + 1, inR);
    return node;
}
void display(Node *node)
{
    if (node == nullptr)
        return;
    display(node->lc);
    display(node->rc);
    cout << node->value << " ";
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> preOrder[i];
        for (int i = 0; i < n; ++i)
            cin >> inOrder[i];
        Node *root = buildTree(0, n - 1, 0, n - 1);
        display(root);
        cout << endl;
        delete root;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}