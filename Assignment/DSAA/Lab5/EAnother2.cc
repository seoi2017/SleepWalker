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
#define MAXN 100010
using namespace std;
struct Node
{
    int tot, ind;
    Node(int x = 0, int y = 0): tot(x), ind(y) {}
    bool operator<(const Node &x) const
    {
        if (this->tot != x.tot)
            return this->tot < x.tot;
        return this->ind < x.ind;
    }
    bool operator==(const Node &x) const
    {
        return this->tot == x.tot && this->ind == x.ind;
    }
};
template<typename T>
class ScapegoatTree
{
private:
    const double epsilon = 0.75;
    struct TreeNode
    {
        T key;
        TreeNode *lc, *rc;
        int value, size, cover;
        bool exist;
        void pushup()
        {
            int lVar = this->lc == nullptr ? 0 : this->lc->size;
            int rVar = this->rc == nullptr ? 0 : this->rc->size;
            this->size = lVar + rVar + (int)this->exist;
            lVar = this->lc == nullptr ? 0 : this->lc->cover;
            rVar = this->rc == nullptr ? 0 : this->rc->cover;
            this->cover = lVar + rVar + 1;
        }
        TreeNode(const T &key, const int &value): key(key), value(value)
        {
            this->size = 1;
            this->cover = 1;
            this->exist = true;
            this->lc = nullptr;
            this->rc = nullptr;
        }
        ~TreeNode()
        {
            this->lc = nullptr;
            this->rc = nullptr;
        }
    }*root;
    bool isUnbalanced(const TreeNode *node)
    {
        if (node == nullptr)
            return false;
        int lCover = node->lc == nullptr ? 0 : node->lc->cover;
        int rCover = node->rc == nullptr ? 0 : node->rc->cover;
        if (max(lCover, rCover) > this->epsilon * node->cover)
            return true;
        return false;
    }
    void travel(TreeNode** &pool, int &cntPtr, TreeNode *now)
    {
        if (now == nullptr)
            return;
        travel(pool, cntPtr, now->lc);
        if (now->exist == true)
            pool[cntPtr++] = now;
        travel(pool, cntPtr, now->rc);
        if (now->exist == false)
            delete now;
    }
    TreeNode* divide(TreeNode** &pool, const int &l, const int &r)
    {
        if (l >= r)
            return nullptr;
        int mid = (l + r) >> 1;
        TreeNode *now = pool[mid];
        now->lc = divide(pool, l, mid);
        now->rc = divide(pool, mid + 1, r);
        now->pushup();
        return now;
    }
    void rebuild(TreeNode* &node)
    {
        if (node == nullptr)
            return;
        TreeNode **pool = new TreeNode*[node->size];
        int cntPtr = 0;
        this->travel(pool, cntPtr, node);
        node = this->divide(pool, 0, cntPtr);
        delete[] pool;
    }
    void remove(TreeNode *node, const int &kth)
    {
        if (node == nullptr)
            return;
        --node->size;
        int lSize = node->lc == nullptr ? 0 : node->lc->size;
        int self = (int)node->exist;
        if (node->exist == true && lSize + self == kth)
            node->exist = false;
        else
        {
            if (lSize + self >= kth)
                remove(node->lc, kth);
            else
                remove(node->rc, kth - (lSize + self));
        }
    }
    TreeNode** newNode(TreeNode* &node, const T &key, const int &value)
    {
        if (node == nullptr)
        {
            node = new TreeNode(key, value);
            return nullptr;
        }
        ++node->size;
        ++node->cover;
        TreeNode** next = this->newNode(key < node->key ? node->lc : node->rc, key, value);
        if (this->isUnbalanced(node) == true)
            next = &node;
        return next;
    }
public:
    bool isEmpty()
    {
        if (this->root == nullptr || this->root->size == 0)
            return true;
        return false;
    }
    int getSize()
    {
        if (this->root == nullptr)
            return 0;
        return this->root->size;
    }
    void insert(const T &key, const int &value)
    {
        TreeNode **subTree = this->newNode(this->root, key, value);
        if (subTree != nullptr)
            this->rebuild(*subTree);
    }
    pair<T, int> getMaxPair()
    {
        TreeNode *node = this->root;
        int lSize, rSize, self, query = this->getSize();
        while (node != nullptr)
        {
            lSize = node->lc == nullptr ? 0 : node->lc->size;
            rSize = node->rc == nullptr ? 0 : node->rc->size;
            self = node->exist == true ? 1 : 0;
            if (lSize + self == query && node->exist == true)
                return make_pair(node->key, node->value);
            else if (lSize >= query)
                node = node->lc;
            else
                query -= (lSize + self), node = node->rc;
        }
        return pair<T, int>();
    }
    void eraseMax()
    {
        this->remove(this->root, this->getSize());
    }
};
char str[256];
bool endTag;
ScapegoatTree<Node> tree;
int n, cnt[MAXN], k;
pair<Node, int> temp;
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
            tree.insert(Node(++cnt[n], ++k), n);
            break;
        case 'e':
            if (tree.isEmpty() == true)
            {
                printf("pa\n");
                break;
            }
            temp = tree.getMaxPair();
            printf("%d\n", temp.second);
            --cnt[temp.second];
            tree.eraseMax();
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