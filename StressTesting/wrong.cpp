/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define mp make_pair
#define endl '\n'
#define mem(dp, x) memset(dp, x, sizeof dp)
#define SetBit(x, k) (x |= (1LL << k))
#define ClearBit(x, k) (x &= ~(1LL << k))
#define CheckBit(x, k) ((x >> k) & 1)

void solve()
{
    int x, m;
    cin >> x >> m;

    int ans = 0;
    if (m == 1)
    {
        cout << 1 << endl;
        return;
    }
    if (x == 1)
    {
        cout << m << endl;
        return;
    }
    for (int y = 1; y <= m and y < x; y++)
    {
        int d = x ^ y;
        if (d % x == 0 or d % y == 0)
            ans++;
    }
    // cerr << ans << endl;

    int d = (m + x - 1) / x;
    d *= (x);
    d += 2 * x;

    ans += (d / x);
    // cerr << ans << endl;
    for (int i = 0; i <= 10 and d - i * x >= 0; i++)
    {
        int new_d = d - i * x;
        int y = (new_d ^ x);
        // cerr << "y " << y << endl;
        if (y > m)
            ans--;
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // int t;
    // cin >> t;
    // while (t--)
    solve();
}