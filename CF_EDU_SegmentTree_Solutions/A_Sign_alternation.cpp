#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SegmentTree
{
    ll size;
    vector<ll> Sums;
    void build(vector<ll> &a, ll index, ll l, ll r)
    {
        if (r - l == 1)
        {
            if (l < a.size())
                Sums[index] = a[l];
            if (l % 2 == 1)
                Sums[index] = -Sums[index];
            return;
        }
        ll mid = (l + r) / 2;

        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid, r);

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2];
    }

    void set(ll i, ll x, ll index, ll l, ll r)
    {
        if (r - l == 1)
        {
            Sums[index] = x;
            if (l % 2 == 1)
                Sums[index] = -Sums[index];
            return;
        }

        ll mid = (l + r) / 2;

        if (i < mid)
        {
            set(i, x, 2 * index + 1, l, mid);
        }
        else
        {
            set(i, x, 2 * index + 2, mid, r);
        }

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2];
    }

    ll getSum(ll curL, ll curR, ll index, ll l, ll r)
    {
        if (curL >= l and curR <= r)
        {
            return Sums[index];
        }
        if (curR <= l or curL >= r)
            return 0;
        ll mid = (curL + curR) / 2;

        return getSum(curL, mid, 2 * index + 1, l, r) + getSum(mid, curR, 2 * index + 2, l, r);
    }

public:
    SegmentTree(vector<ll> &a, ll n)
    {
        size = 1;
        while (size <= n)
            size *= 2;
        Sums.assign(2 * size, 0);
        build(a, 0, 0, size);
    }
    void set(ll i, ll x)
    {
        set(i, x, 0, 0, size);
    }
    int getSum(ll l, ll r)
    {
        return getSum(0, size, 0, l, r);
    }
    void show()
    {
        for (auto it : Sums)
        {
            cout << it << ' ';
        }
        cout << endl;
    }
};

int main()
{
    ll n, i;
    cin >> n;
    vector<ll> arr(n);
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    // for (i = 0; i < n; i++)
    // {
    //     cout << arr[i] << ' ';
    // }
    // cout << endl;
    SegmentTree st(arr, n + 1);
    // st.show();
    ll q;
    cin >> q;
    while (q--)
    {
        int c;
        cin >> c;
        if (c == 0)
        {
            int i, x;
            cin >> i >> x;
            st.set(i - 1, x);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            ll ans = st.getSum(l - 1, r);
            if (l % 2 == 0)
                ans = -ans;
            cout << ans << endl;
        }
    }
}