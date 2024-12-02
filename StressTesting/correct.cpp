/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x, m;
    cin >> x >> m;
    int cnt = 0;
    for (int y = 1; y <= m; y++)
    {
        int d = x ^ y;
        if (d % x == 0 or d % y == 0)
        {
            // cout << "y = " << y << " d = " << d << ' ' << d % x << ' ' << d % y << endl;
            cnt++;
        }
    }
    cout << cnt;
    cout << endl;
}