#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    vector<int> tree;
    int sz = 1;
    void build(vector<int> &a, int index, int l, int r)
    {
        if (l == r)
        {
            if (l < a.size())
                tree[index] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid + 1, r);

        tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
    }

    int get(int index, int searchL, int searchR, int l, int r)
    {
        if (l >= searchL and r <= searchR)
            return tree[index];
        if (l > searchR or r < searchL)
            return INT_MIN;

        int mid = (l + r) / 2;
        int x = get(2 * index + 1, searchL, searchR, l, mid);
        int y = get(2 * index + 2, searchL, searchR, mid + 1, r);

        return max(x, y);
    }

    void update(int index, int l, int r, int idx, int val)
    {
        // cout << l << ' ' << r << endl;
        if (l == r)
        {
            tree[index] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (mid >= idx)
            update(2 * index + 1, l, mid, idx, val);
        else
            update(2 * index + 2, mid + 1, r, idx, val);
        tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
    }

public:
    SegmentTree(int n)
    {
        while (sz < n)
            sz *= 2;
        tree.assign(2 * sz, 0);
    }

    void build(vector<int> &a)
    {
        build(a, 0, 0, sz - 1);
    }

    int get(int l, int r)
    {
        return get(0, l, r, 0, sz - 1);
    }

    void update(int idx, int val)
    {
        update(0, 0, sz - 1, idx, val);
    }
    void print()
    {
        for (auto it : tree)
            cout << it << ' ';
        cout << endl;
    }
};
