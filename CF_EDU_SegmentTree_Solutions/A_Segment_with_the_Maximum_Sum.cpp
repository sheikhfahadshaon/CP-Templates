#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
    int size = 1;
    vector<long long> sum, pref, suf, maximal_seg;

    void build(vector<long long> &a, int index, int l, int r)
    {
        if (r - l == 1)
        {
            if (l < a.size())
            {
                sum[index] = a[l];

                /*If they are less then 0 then maximum will be 0*/
                pref[index] = max(a[l], 0LL);
                suf[index] = max(a[l], 0LL);
                maximal_seg[index] = max(a[l], 0LL);
            }
            return;
        }

        int mid = (l + r) / 2;
        build(a, 2 * index + 1, l, mid);
        build(a, 2 * index + 2, mid, r);

        /*
        ->The Maximum sum segment of the node can:
            Either on the segment of it's child
            Or Highest Suffix of the left child and highest Prefix of the right child
        */
        maximal_seg[index] = max(maximal_seg[2 * index + 1], max(maximal_seg[2 * index + 2], suf[2 * index + 1] + pref[2 * index + 2]));

        /*
        ->Current Prefix can be:
            Either on the highest prefix of the left child
            Or Total of Sum of the left child and maximum prefix of the right child
        */
        pref[index] = max(0LL, max(pref[2 * index + 1], sum[2 * index + 1] + pref[2 * index + 2]));

        /*
        -> Current suffix can be:
            Either on the highest suffix of the right child
            Or Total of sum of the right child and maximum suffix of the left child
        */

        suf[index] = max(0LL, max(suf[2 * index + 2], suf[2 * index + 1] + sum[2 * index + 2]));
        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
    }

    void set(int i, long long v, int index, int l, int r)
    {
        if (r - l == 1)
        {
            sum[index] = v;
            pref[index] = max(v, 0LL);
            suf[index] = max(v, 0LL);
            maximal_seg[index] = max(v, 0LL);
            return;
        }

        int mid = (l + r) / 2;

        if (i < mid)
            set(i, v, 2 * index + 1, l, mid);
        else
            set(i, v, 2 * index + 2, mid, r);

        maximal_seg[index] = max(maximal_seg[2 * index + 1], max(maximal_seg[2 * index + 2], suf[2 * index + 1] + pref[2 * index + 2]));
        pref[index] = max(0LL, max(pref[2 * index + 1], sum[2 * index + 1] + pref[2 * index + 2]));
        suf[index] = max(0LL, max(suf[2 * index + 2], suf[2 * index + 1] + sum[2 * index + 2]));
        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
    }

public:
    SegmentTree(int n)
    {
        while (size < n)
            size *= 2;
        sum.assign(2 * size, 0LL);
        pref.assign(2 * size, 0LL);
        suf.assign(2 * size, 0LL);
        maximal_seg.assign(2 * size, 0LL);
    }

    void build(vector<long long> &a)
    {
        build(a, 0, 0, size);
    }
    void set(int i, long long v)
    {
        set(i, v, 0, 0, size);
    }
    long long getRoot()
    {
        return maximal_seg[0];
    }
};

int main()
{

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);

    for (auto &i : a)
        cin >> i;

    SegmentTree st(n);
    st.build(a);
    cout << st.getRoot() << endl;
    while (m--)
    {
        int i, v;
        cin >> i >> v;
        st.set(i, v);
        cout << st.getRoot() << endl;
    }
}