#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size;
    vector<int> Sum;
    void build(vector<int> &a, int l, int r, int index)
    {
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
    void build(int n, vector<int> &a)
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
    int n, q, i;
    cin >> n >> q;
    vector<int> arr(n);
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int mx = 41;
    vector<vector<int>> a(41, vector<int>(n + 1, 0));

    for (i = 1; i <= 40; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] > i)
                a[i][j] = 1;
        }
    }

    SegmentTree st[41];
    for (i = 1; i <= 40; i++)
    {
        st[i].build(n, a[i]);
    }
    while (q--)
    {
        int c;
        cin >> c;
        if (c == 1)
        {
            int l, r;
            cin >> l >> r;
            int ans = 0;
            for (i = l; i < r; i++)
            {
                ans += st[arr[i]].getSum(l - 1, i + 1);
            }
            cout << ans << endl;
        }
        else
        {
            int x;
            cin >> i >> x;
            for (int j = 1; j <= 40; j++)
            {
                if (x > j)
                    st[j].set(i - 1, 1);
                else
                    st[j].set(i - 1, 0);
            }
            arr[i - 1] = x;
        }
    }
}
