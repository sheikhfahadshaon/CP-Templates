#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    vector<pair<int, int>> MinTree; /* Minimum of the childrens are on the first element and Minumum count of the children on the second element*/
    int size = 1;

    void build(vector<int> &a, int index, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < a.size())
                MinTree[index] = {a[l], 1};
            return;
        }

        int mid = (l + r) / 2;
        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid, r);

        MinTree[index].first = min(MinTree[2 * index + 1].first, MinTree[2 * index + 2].first);

        // Calculate the minimum count check with the children
        if (MinTree[index].first == MinTree[2 * index + 1].first)
            MinTree[index].second += MinTree[2 * index + 1].second;

        if (MinTree[index].first == MinTree[2 * index + 2].first)
            MinTree[index].second += MinTree[2 * index + 2].second;
    }

    void set(int u, int v, int index, int l, int r)
    {
        if (r - l == 1)
        {
            MinTree[index] = {v, 1};
            return;
        }

        int mid = (l + r) / 2;

        if (u < mid)
            set(u, v, 2 * index + 1, l, mid);
        else
            set(u, v, 2 * index + 2, mid, r);

        MinTree[index].first = min(MinTree[2 * index + 1].first, MinTree[2 * index + 2].first);
        MinTree[index].second = 0; // For updating it again

        // Calculate the minimum count check with the children
        if (MinTree[index].first == MinTree[2 * index + 1].first)
            MinTree[index].second += MinTree[2 * index + 1].second;

        if (MinTree[index].first == MinTree[2 * index + 2].first)
            MinTree[index].second += MinTree[2 * index + 2].second;
    }

    pair<int, int> getMin(int l, int r, int index, int lx, int rx)
    {
        if (l <= lx and rx <= r)
            return MinTree[index];
        if (rx <= l or r <= lx)
            return {INT_MAX, 0};

        int mid = (lx + rx) / 2;

        pair<int, int> currentNode, leftChild, rightChild;

        currentNode.second = 0;
        leftChild = getMin(l, r, 2 * index + 1, lx, mid);
        rightChild = getMin(l, r, 2 * index + 2, mid, rx);
        currentNode.first = min(leftChild.first, rightChild.first);

        if (currentNode.first == leftChild.first)
            currentNode.second += leftChild.second;
        if (currentNode.first == rightChild.first)
            currentNode.second += rightChild.second;

        return currentNode;
    }

public:
    SegmentTree(int n)
    {
        while (size < n)
            size *= 2;
        MinTree.assign(2 * size, {INT_MAX, 0LL});
    }

    // Build the Segment tree for the elements of a
    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }

    /*Set v at index i*/
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    pair<int, int> getMin(int l, int r)
    {
        return getMin(l, r, 0, 0, size);
    }

    void show()
    {
        for (auto p : MinTree)
            cout << p.first << ' ' << p.second << '\n';
        cout << endl;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    SegmentTree st(n);

    vector<int> a(n);

    for (auto &i : a)
        cin >> i;

    st.build(a);

    while (m--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int u, v;
            cin >> u >> v;
            st.set(u, v);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            pair<int, int> ans = st.getMin(l, r);
            cout << ans.first << ' ' << ans.second << endl;
        }
    }
}