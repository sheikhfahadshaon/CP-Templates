#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size = 1;

    vector<long long> Sums;                                      // Stores the Sums
    void buildSum(vector<long long> &a, int index, int l, int r) // Builds the tree
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

    void set(int i, long long v, int index, int l, int r)
    {
        if (r - l == 1)
        {
            Sums[index] = v;
            return;
        }
        int mid = (r + l) / 2;
        if (i < mid)
            set(i, v, 2 * index + 1, l, mid); // If it's in the left subtree
        else
            set(i, v, 2 * index + 2, mid, r); // the element is on the right subtree

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2];
    }

    long long getSum(int l, int r, int index, int lx, int rx)
    {

        if (rx <= l or r <= lx) // If it is outside the range
            return 0;
        if (l <= lx and rx <= r) /*If it is inside the given range*/
            return Sums[index];
        int mid = (lx + rx) / 2;

        return getSum(l, r, 2 * index + 1, lx, mid) + getSum(l, r, 2 * index + 2, mid, rx);
    }

public:
    SegmentTree(long long n)
    {
        while (size < n)
            size *= 2;
        Sums.assign(2 * size, 0LL);
    }
    void build(vector<long long> &a)
    {
        buildSum(a, 0, 0, size);
    }

    // Sets v at index i
    void set(int i, long long v)
    {
        set(i, v, 0, 0, size);
    }

    // Returns the sum from l....r-1
    long long getSum(int l, int r)
    {
        return getSum(l, r, 0, 0, size);
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

int main()
{
    int n, m, i;
    cin >> n >> m;

    SegmentTree st(n);

    vector<long long> a(n);

    for (auto &i : a)
        cin >> i;

    st.build(a);
    // st.show();
    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i;
            long long x;
            cin >> i >> x;
            st.set(i, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.getSum(l, r) << endl;
        }
    }
}