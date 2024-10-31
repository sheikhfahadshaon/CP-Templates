#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size;
    vector<int> Sum;
    void build(vector<int> &a, int l, int r, int index)
    {
        // cout << "Jhamela Kothay: ";
        if (r - l == 1)
        {
            if (l < a.size())
                Sum[index] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(a, l, mid, 2 * index + 1);
        build(a, mid, r, 2 * index + 2);

        Sum[index] = Sum[2 * index + 1] + Sum[2 * index + 2];
    }

    int getSum(int l, int r, int curL, int curR, int index)
    {
        if (curR <= l or curL >= r)
            return 0;
        if (curL >= l and curR <= r)
            return Sum[index];

        int mid = (curL + curR) / 2;

        return getSum(l, r, curL, mid, 2 * index + 1) + getSum(l, r, mid, curR, 2 * index + 2);
    }

    void set(int l, int r, int index, int i, int x)
    {
        if (r - l == 1)
        {
            Sum[index] = x;
            return;
        }
        int mid = (l + r) / 2;

        if (i < mid)
            set(l, mid, 2 * index + 1, i, x);
        else
            set(mid, r, 2 * index + 2, i, x);
        Sum[index] = Sum[2 * index + 1] + Sum[2 * index + 2];
    }

public:
    SegmentTree(vector<int> &a, int n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        Sum.assign(2 * size, 0);
        build(a, 0, size, 0);
    }
    void set(int i, int x)
    {
        set(0, size, 0, i, x);
    }
    int getSum(int l, int r)
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
    int n, i;
    cin >> n;
    vector<int> a(2 * n, 0);
    SegmentTree st(a, 2 * n);
    int vis[n + 1];
    memset(vis, -1, sizeof(vis));
    int x;
    int ans[n + 1];
    // st.show();

    for (i = 0; i < 2 * n; i++)
    {
        cin >> x;
        if (vis[x] != -1)
        {
            ans[x] = st.getSum(vis[x], i);
            // cout << "x: " << x << " " << vis[x] << ' ' << i << endl;
            st.set(vis[x], 1);
        }
        else
        {
            vis[x] = i;
        }
    }
    for (i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}