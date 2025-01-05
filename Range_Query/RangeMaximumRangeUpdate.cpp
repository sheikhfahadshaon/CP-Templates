class SegmentTree
{
    int N, n, init_val;
    vector<int> tree, lazy, a;
    vector<bool> upd;

    int op(int &a, int &b) { return max(a, b); }

    void build(int l, int r, int ind)
    {
        if (r == l)
        {
            tree[ind] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, 2 * ind + 1);
        build(mid + 1, r, 2 * ind + 2);

        tree[ind] = op(tree[2 * ind + 1], tree[2 * ind + 2]);
    }

    int get(int l, int r, int curL, int curR, int index)
    {
        if (curL > r or curR < l)
            return init_val;

        if (upd[index])
        {
            tree[index] = lazy[index];
            lazy[2 * index + 1] = lazy[2 * index + 2] = lazy[index];
            upd[2 * index + 1] = upd[2 * index + 2] = 1;
            upd[index] = 0;
        }

        if (curL >= l and curR <= r)
        {
            return tree[index];
        }

        int mid = (curL + curR) >> 1;
        int mnl = get(l, r, curL, mid, 2 * index + 1);
        int mnr = get(l, r, mid + 1, curR, 2 * index + 2);
        return op(mnl, mnr);
    }

    void update(int l, int r, int curL, int curR, int index, int val)
    {
        if (curL > r or curR < l)
            return;

        if (upd[index])
        {
            tree[index] = lazy[index];
            lazy[2 * index + 1] = lazy[2 * index + 2] = lazy[index];
            upd[2 * index + 1] = upd[2 * index + 2] = upd[index];
            upd[index] = 0;
        }

        if (curL >= l and curR <= r)
        {
            tree[index] = val;
            lazy[2 * index + 1] = lazy[2 * index + 2] = val;
            upd[2 * index + 1] = upd[2 * index + 2] = 1;
            return;
        }

        int mid = (curL + curR) >> 1;
        update(l, r, curL, mid, 2 * index + 1, val);
        update(l, r, mid + 1, curR, 2 * index + 2, val);

        tree[index] = op(tree[2 * index + 1], tree[2 * index + 2]);
    }

public:
    SegmentTree(vector<int> &a)
    {
        tree.assign(8LL * a.size() + 5, init_val);
        lazy.assign(8LL * a.size() + 5, init_val);
        upd.assign(8LL * a.size() + 5, 0);
        this->a = a;
        n = a.size();
        init_val = INT_MIN;
    }

    void build()
    {
        build(0, n - 1, 0);
    }
    int get(int l, int r) { return get(l, r, 0, n - 1, 0); }
    void update(int l, int r, int val) { update(l, r, 0, n - 1, 0, val); }
};
