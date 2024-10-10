/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

struct query
{
    int id, l, r;
};

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int q;
    cin >> q;
    vector<query> ranges(q);
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        ranges[i].id = i;
        ranges[i].l = l - 1; // Make it 0-based
        ranges[i].r = r - 1; // Make it 0-based
    }

    int sq = sqrt(n); // Block size for Mo's Algorithm

    // Sorting ranges based on Mo's order
    sort(ranges.begin(), ranges.end(), [&](query &a, query &b)
         {
        int blockNumber1 = a.l / sq;
        int blockNumber2 = b.l / sq;
        if (blockNumber1 != blockNumber2)
            return blockNumber1 < blockNumber2;
        return (blockNumber1 % 2 == 0) ? a.r < b.r : a.r > b.r; });

    auto add = [&](int ind)
    {
        ;
    };

    auto remove = [&](int ind)
    {
        ;
    };

    for (int i = 0; i < n; i++)
        add(i);

    int l = 0, r = n - 1;
    vector<int> ans(q);

    // Processing each query
    for (int i = 0; i < q; i++)
    {
        int curL = ranges[i].l, curR = ranges[i].r, index = ranges[i].id;

        while (l > curL)
            add(--l);
        while (l < curL)
            remove(l++);
        while (r < curR)
            add(++r);
        while (r > curR)
            remove(r--);

        // ans = ?
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << endl;
}
