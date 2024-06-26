#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5;
vector<int> child(N), graph[N], tin(N), low(N);

bool vis[N];
int n, m, ans, timer;

void Bridge(int u, int v)
{
    ;
}

void dfs(int u, int par = -1)
{
    vis[u] = 1;
    tin[u] = low[u] = timer++;
    child[u]++;
    for (auto v : graph[u])
    {
        if (v == par)
            continue;
        if (vis[v])
        {
            low[u] = min(low[u], tin[v]);
        }
        else
        {
            dfs(v, u);
            low[u] = min(low[v], low[u]);
            child[u] += child[v];
            if (low[v] > tin[u])
                Bridge(u, v);
        }
    }
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        dfs(1);

        for (int i = 0; i < n + 5; i++)
        {
            graph[i].clear();
            ans = 0;
            vis[i] = 0, tin[i] = 0, low[i] = 0, child[i] = 0, timer = 0;
        }
    }
}