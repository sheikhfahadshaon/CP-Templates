#include <bits/stdc++.h>
using namespace std;
#define ll long long
class SegmentTree
{
    ll size;
    vector<ll> Sum;
    void build(vector<ll> &a, ll l, ll r, ll index)
    {
        if (r - l == 1)
        {
            if (l < a.size())
                Sum[index] = a[l];
            return;
        }

        ll mid = (l + r) / 2;

        build(a, l, mid, 2 * index + 1);
        build(a, mid, r, 2 * index + 2);

        Sum[index] = Sum[2 * index + 1] + Sum[2 * index + 2];
    }

    ll getSum(ll l, ll r, ll curL, ll curR, ll index)
    {
        if (curR <= l or curL >= r)
            return 0;
        if (curL >= l and curR <= r)
            return Sum[index];

        ll mid = (curL + curR) / 2;

        return getSum(l, r, curL, mid, 2 * index + 1) + getSum(l, r, mid, curR, 2 * index + 2);
    }

    void set(ll l, ll r, ll index, ll i, ll x)
    {
        if (r - l == 1)
        {
            Sum[index] += x;
            return;
        }
        ll mid = (l + r) / 2;

        if (i < mid)
            set(l, mid, 2 * index + 1, i, x);
        else
            set(mid, r, 2 * index + 2, i, x);
        Sum[index] = Sum[2 * index + 1] + Sum[2 * index + 2];
    }

public:
    SegmentTree(vector<ll> &a, ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        Sum.assign(2 * size, 0);
        build(a, 0, size, 0);
    }
    void set(ll i, ll x)
    {
        set(0, size, 0, i, x);
    }
    ll getSum(ll l, ll r)
    {
        return getSum(l, r, 0, size, 0);
    }
    void show()
    {
        for (auto i : Sum)
            cout << i << ' ';
        cout << endl;
    }
};

int main()
{
    ll n, q, i;
    cin >> n >> q;
    vector<ll> a(n + 1, 0); // Suppose you get the range till the last element in the query then you will need to perform get sum over the n + 1 that is why segment tree is made as n + 1
    SegmentTree st(a, n + 1);

    while (q--)
    {
        ll l, r, x, c;
        cin >> c;
        if (c == 1)
        {
            cin >> l >> r >> x;
            st.set(l, x);
            st.set(r, -x);
        }
        else
        {
            cin >> i;
            cout << st.getSum(0, i + 1) << endl;
        }
    }
}