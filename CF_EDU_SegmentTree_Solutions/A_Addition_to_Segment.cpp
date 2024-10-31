#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    long long int size = 1;

    vector<long long> Sums;                                                                    // Stores the Sums
    void buildSum(vector<long long> &a, long long int index, long long int l, long long int r) // Builds the tree
    {
        if (r - l == 1)
        {
            if (l < a.size())
                Sums[index] = a[l];
            return;
        }
        long long int mid = (l + r) / 2;
        buildSum(a, 2 * index + 1, l, mid);
        buildSum(a, 2 * index + 2, mid, r);

        Sums[index] = Sums[2 * index + 1] + Sums[2 * index + 2]; // Adds the sum of its chilren to the node
    }

    void add(long long int l, long long int r, long long int cur_l, long long int cur_r, long long int index, long long v)
    {
        if (cur_r <= l or cur_l >= r)
            return;
        else if (cur_l >= l and cur_r <= r)
        {
            Sums[index] += v;
            return;
        }
        long long int mid = (cur_l + cur_r) / 2;
        add(l, r, cur_l, mid, 2 * index + 1, v);
        add(l, r, mid, cur_r, 2 * index + 2, v);
    }
    long long int get(long long int l, long long int r, long long int index, long long int i)
    {
        if (l == r - 1)
        {
            return Sums[index];
        }
        long long int mid = (l + r) / 2;
        if (mid <= i)
        {
            return Sums[index] + get(mid, r, 2 * index + 2, i);
        }
        else
            return Sums[index] + get(l, mid, 2 * index + 1, i);
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
    void add(long long int l, long long int r, long long int v)
    {
        add(l, r, 0, size, 0, v);
    }

    long long int get(long long int i)
    {
        return get(0, size, 0, i);
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
    long long int n, m;
    cin >> n >> m;
    vector<long long> a(n, 0);
    SegmentTree st(n);
    st.build(a);

    while (m--)
    {
        long long int op;
        cin >> op;
        if (op == 1)
        {
            long long int l, r;
            long long v;
            cin >> l >> r >> v;
            st.add(l, r, v);
            // st.show();
        }
        else
        {
            long long int i;
            cin >> i;
            cout << st.get(i) << endl;
            ;
        }
    }
}