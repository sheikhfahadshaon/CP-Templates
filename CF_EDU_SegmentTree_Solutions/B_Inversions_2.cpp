#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size = 1;
    vector<int> sum;

    void build(vector<int> &a, int index, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < a.size())
                sum[index] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid, r);

        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
    }

    void set(int i, int index, int l, int r)
    {
        if (r - l == 1)
        {
            sum[index] = 1 - sum[index];
            return;
        }

        int mid = (l + r) / 2;

        if (i < mid)
            set(i, 2 * index + 1, l, mid);
        else
            set(i, 2 * index + 2, mid, r);

        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
    }

    int find(int k, int index, int l, int r)
    {
        if (r - l == 1)
        {
            return l;
        }
        int mid = (l + r) / 2;
        if (sum[2 * index + 1] > k)
        {
            return find(k, 2 * index + 1, l, mid);
        }
        else
            return find(k - sum[2 * index + 1], 2 * index + 2, mid, r);
    }

public:
    SegmentTree(int n)
    {
        while (size < n)
            size *= 2;
        sum.assign(2 * size, 0LL);
    }

    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }
    void set(int i)
    {
        set(i, 0, 0, size);
    }
    int find(int k)
    {
        return find(k, 0, 0, size);
    }
    void show()
    {
        for (auto i : sum)
            cout << i << ' ';
        cout << endl;
    }
};

int main()
{
    int n;
    cin >> n;
    SegmentTree st(n);

    vector<int> a(n, 1);

    st.build(a);
    int prev[n];
    for (int i = 0; i < n; i++)
    {
        cin >> prev[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int x = prev[i];
        int id = st.find(x);
        // cout << id << ' ';
        st.set(id);
        prev[i] = id;
    }

    for (int i = 0; i < n; i++)
        cout << n - prev[i] << ' ';
    cout << endl;
}