class SparseTableMax
{
    int N = 2e5 + 5, LOG = 20;
    vector<vector<int>> pre_calc;

public:
    SparseTableMax(vector<int> &a)
    {
        pre_calc.assign(LOG, vector<int>(a.size(), -1));
        int n = a.size();
        for (int i = 0; i < n; i++)
            pre_calc[0][i] = a[i];

        for (int lg = 1; lg < LOG; lg++)
        {
            for (int i = 0; i + (1 << lg) - 1 < n; i++)
            {
                pre_calc[lg][i] = min(pre_calc[lg - 1][i], pre_calc[lg - 1][i + (1 << (lg - 1))]);
            }
        }
    }
    int query(int l, int r)
    {
        int k = 31 - __builtin_clz(r - l + 1);

        return min(pre_calc[k][l], pre_calc[k][r - (1 << k) + 1]);
    }
};
