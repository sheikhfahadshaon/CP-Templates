/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define mem(dp, x) memset(dp, x, sizeof dp)
#define SetBit(x, k) (x |= (1LL << k))
#define ClearBit(x, k) (x &= ~(1LL << k))
#define CheckBit(x, k) ((x >> k) & 1)

void solve()
{
    int n;
    cin >> n;
    vector<int> cnt(n + 10, 0);
    set<pair<int, int>> edges;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        cnt[u]++;
        cnt[v]++;
        edges.insert({min(u, v), max(u, v)});
    }
    vector<int> index(n);
    for (int i = 1; i <= n; i++)
        index[i - 1] = i;

    sort(index.begin(), index.end(), [&](int i, int j) -> bool
         { return cnt[i] > cnt[j]; });
    int u = index[0];
    // cerr << "First Node: " << u << ' ' << cnt[u] << endl;
    int ans = -1;
    for (int i = 1; i < n; i++)
    {
        int v = index[i];
        int score = cnt[v] - 1;
        if (edges.find({min(u, v), max(u, v)}) != edges.end())
            score--;
        // cerr << "v: " << v << " " << score << endl;
        ans = max(ans, cnt[u] + score);
    }

    u = index[1];
    for (int i = 2; i < n; i++)
    {
        int v = index[i];
        int score = cnt[v] - 1;
        if (edges.find({min(u, v), max(u, v)}) != edges.end())
            score--;
        // cerr << "v: " << v << " " << score << endl;
        ans = max(ans, cnt[u] + score);
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
}