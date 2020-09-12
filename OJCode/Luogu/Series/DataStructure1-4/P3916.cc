/*
Author: Invrise
OJ Site: Luogu
Problem ID: P3916
*/
#include <bits/stdc++.h>
#define MAX_NODE 100010
#define MAX_EDGE 100010
using namespace std;
class graph_t // 指针邻接表实现
{
private:
    int totalNode;
    int totalEdge;
    int ans[MAX_NODE] = {0};

    struct node_t
    {
        int val;
        node_t *next;

        node_t(int val = 0, node_t *next = nullptr)
        {
            this->val = val;
            this->next = next;
        }
    } node[MAX_NODE], edge[MAX_EDGE];

public:
    graph_t(int totalNode)
    {
        this->totalNode = totalNode;
        for (int i = 1; i <= totalNode; ++i)
        {
            this->node[i].val = i;
            this->node[i].next = nullptr;
        }
        this->totalEdge = 0;
    }

    void addEdge(int from, int to)
    {
        this->edge[++this->totalEdge] = node_t(to, this->node[from].next);
        this->node[from].next = &this->edge[this->totalEdge];
    }

    void query(int begin, int ansMax)
    {
        if (this->ans[begin] >= ansMax)
            return;
        this->ans[begin] = ansMax;
        for (node_t *i = this->node[begin].next; i != nullptr; i = i->next)
        {
            this->query(i->val, this->ans[begin]);
        }
    }

    void print()
    {
        for (int i = 1; i <= this->totalNode; ++i)
        {
            printf("%d%c", this->ans[i], i == this->totalNode ? '\n' : ' ');
        }
    }
};
class graph_vector_t // std::vector实现
{
private:
    int totalNode;
    int ans[MAX_NODE] = {0};
    vector<int> edge[MAX_NODE];

public:
    graph_vector_t(int totalNode)
    {
        this->totalNode = totalNode;
    }

    void addEdge(int from, int to)
    {
        this->edge[from].push_back(to);
    }

    void query(int begin, int ansMax)
    {
        if (this->ans[begin] >= ansMax)
            return;
        this->ans[begin] = ansMax;
        for (vector<int>::iterator i = this->edge[begin].begin(); i != this->edge[begin].end(); ++i)
        {
            this->query(*i, this->ans[begin]);
        }
    }

    void print()
    {
        for (int i = 1; i <= this->totalNode; ++i)
        {
            printf("%d%c", this->ans[i], i == this->totalNode ? '\n' : ' ');
        }
    }
};
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    graph_t graph(n);
    // graph_vector_t graph(n);
    for (int i = 0, a, b; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        graph.addEdge(b, a);
    }
    for (int i = n; i >= 1; --i)
    {
        graph.query(i, i);
    }
    graph.print();
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}