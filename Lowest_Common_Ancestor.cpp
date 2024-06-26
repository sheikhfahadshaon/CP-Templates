#include <bits/stdc++.h>
using namespace std;

const int LOG = 15;
const int N = 10001;
vector<int> graph[N];
int up[N][LOG], depth[N];

void dfs(int u)
{
    for (auto v : graph[u])
    {
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        for (int j = 1; j < LOG; j++)
        {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
        dfs(v);
    }
}

int get_lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);

    int k = depth[a] - depth[b];

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (k & (1 << j))
            a = up[a][j];
    }

    if (a == b)
        return a;

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[a][j] != up[b][j])
        {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int main()
{
    int n, m, u, v;
    cin >> n;
    for (u = 0; u < n; u++)
    {
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> v;
            graph[u].push_back(v);
        }
    }
    dfs(0);
    int q;
    cin >> q;
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << get_lca(a, b) << endl;
    }
}