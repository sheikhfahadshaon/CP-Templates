#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size = 1;

    vector<int> Sums, Lazy;                                // Stores the Sums
    void buildSum(vector<int> &a, int index, int l, int r) // Builds the tree
    {
        if (r - l == 1)
        {
            if (l < a.size())
                Sums[index] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        buildSum(a, 2 * index + 1, l, mid);
        buildSum(a, 2 * index + 2, mid, r);

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2]; // Adds the sum of its chilren to the node
    }

    void updateRange(int lx, int rx, int l, int r, int index)
    {

        Sums[index] += (Lazy[index] * (rx - lx));
        if (rx - lx > 1)
        {
            Lazy[2 * index + 1] += Lazy[index];
            Lazy[2 * index + 2] += Lazy[index];
        }
        Lazy[index] = 0;
        if (lx >= r or rx <= l)
            return;
        if (lx >= l and rx <= r)
        {
            Sums[index] += (rx - lx);
            if (rx - lx > 1)
            {
                Lazy[2 * index + 1] += 1;
                Lazy[2 * index + 2] += 1;
            }
            return;
        }

        int mid = (lx + rx) / 2;
        updateRange(lx, mid, l, r, 2 * index + 1);
        updateRange(mid, rx, l, r, 2 * index + 2);

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2];
    }
    int get(int l, int r, int index, int i)
    {
        Sums[index] += (Lazy[index] * (r - l));
        if (r - l > 1)
        {
            Lazy[2 * index + 1] += Lazy[index];
            Lazy[2 * index + 2] += Lazy[index];
        }
        Lazy[index] = 0;
        if (r - l == 1)
        {
            return Sums[index];
        }

        int mid = (l + r) / 2;

        if (i < mid)
        {
            return get(l, mid, 2 * index + 1, i);
        }
        else
        {
            return get(mid, r, 2 * index + 2, i);
        }
    }

    int RangeSum(int lx, int rx, int l, int r, int index)
    {
        Sums[index] += (Lazy[index] * (rx - lx));
        if (rx - lx > 1)
        {
            Lazy[2 * index + 1] += Lazy[index];
            Lazy[2 * index + 2] += Lazy[index];
        }
        Lazy[index] = 0;
        if (lx >= r or rx <= l)
            return 0;
        if (lx >= l and rx <= r)
        {
            return Sums[index];
        }

        int mid = (lx + rx) / 2;
        int a = RangeSum(lx, mid, l, r, 2 * index + 1);
        int b = RangeSum(mid, rx, l, r, 2 * index + 2);
        return a + b;
    }

public:
    SegmentTree(int n)
    {
        while (size < n)
            size *= 2;
        Sums.assign(2 * size, 0LL);
        Lazy.assign(2 * size, 0LL);
    }
    void build(vector<int> &a)
    {
        buildSum(a, 0, 0, size);
    }
    void updateRange(int l, int r)
    {
        updateRange(0, size, l, r, 0);
    }

    int get(int i)
    {
        return get(0, size, 0, i);
    }

    int RangeSum(int l, int r)
    {
        return RangeSum(0, size, l, r, 0);
    }

    void show()
    {
        for (auto i : Sums)
        {
            cout << i << ' ';
        }
        cout << endl;
    }
};

const int mx = 200005;
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(mx, 0);
    SegmentTree st(mx);
    st.build(a);
    SegmentTree st2(mx);
    st2.build(a);

    while (n--)
    {
        int a, b;
        cin >> a >> b;
        st.updateRange(a, b + 1);
    }

    for (int i = 0; i < mx; i++)
    {
        int k = st.get(i);
        if (k >= m)
        {
            st2.updateRange(i, i + 1);
        }
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << st2.RangeSum(a, b + 1) << endl;
    }
}