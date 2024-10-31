#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size = 1;
    vector<int> maxTree;

    void build(vector<int> &a, int index, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < a.size())
                maxTree[index] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid, r);

        maxTree[index] = max(maxTree[2 * index + 1], maxTree[2 * index + 2]);
    }

    void set(int i, int v, int index, int l, int r)
    {
        if (r - l == 1)
        {
            maxTree[index] = v;
            return;
        }

        int mid = (l + r) / 2;

        if (i < mid)
        {
            set(i, v, 2 * index + 1, l, mid);
        }
        else
            set(i, v, 2 * index + 2, mid, r);

        maxTree[index] = max(maxTree[2 * index + 1], maxTree[2 * index + 2]);
    }

    int find(int x, int k, int index, int l, int r)
    {
        if (maxTree[index] < x || r <= k)
            return -1;
        if (r - l == 1)
        {
            return l;
        }
        int mid = (l + r) / 2;

        int res = find(x, k, 2 * index + 1, l, mid);
        if (res == -1)
            res = find(x, k, 2 * index + 2, mid, r);
        return res;
    }

public:
    SegmentTree(int n)
    {
        while (size < n)
            size *= 2;
        maxTree.assign(2 * size, 0);
    }

    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    int find(int x, int k)
    {
        return find(x, k, 0, 0, size);
    }

    int getHighest()
    {
        return maxTree[0];
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;

    SegmentTree st(n);
    st.build(a);

    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else
        {
            int x, k;
            cin >> x >> k;

            cout << st.find(x, k) << endl;
        }
    }
}