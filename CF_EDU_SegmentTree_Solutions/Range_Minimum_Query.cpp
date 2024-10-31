/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define mp make_pair
#define endl '\n'
#define mem(dp, x) memset(dp, x, sizeof dp)

int pre[100005][20];

void solve()
{
    int n, i, k;
    cin >> n;
    int arr[n];
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
        pre[i][0] = arr[i];
    }

    for (int j = 1; j < 20; j++)
    {
        for (i = 0; (i + (1 << j) - 1) < n; i++)
        {
            pre[i][j] = min(pre[i][j - 1], pre[i + (1 << (j - 1))][j - 1]);
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int bin_log = 31 - __builtin_clz(r - l + 1);
        int ans = min(pre[l][bin_log], pre[r - (1 << bin_log) + 1][bin_log]);
        cout << ans << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();
}