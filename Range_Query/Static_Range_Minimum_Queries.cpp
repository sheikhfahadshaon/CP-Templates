#include <bits/stdc++.h>
using namespace std;

#define bitlen 31
#define LOG 18
#define MAXLEN 200005
// 2^16 < 10^5
int arr[MAXLEN], pre[MAXLEN][LOG], n, q;

// 0-indexed
int query(int l, int r)
{
    int k = bitlen - __builtin_clz(r - l + 1);

    return min(pre[l][k], pre[r - (1 << k) + 1][k]);
}

void SparseTable()
{
    cin >> n >> q;
    int i;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
        pre[i][0] = arr[i];
    }

    // Preprocessing
    for (int k = 1; k < LOG; k++)
    {
        for (i = 0; i + (1 << k) - 1 < n; i++)
        {
            pre[i][k] = min(pre[i][k - 1], pre[i + (1 << (k - 1))][k - 1]);
        }
    }

    int l, r;

    while (q--)
    {
        cin >> l >> r;
        l--, r--;

        cout << query(l, r) << endl;
        ;
    }
}

int main()
{
    SparseTable();
}