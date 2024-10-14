#include <bits/stdc++.h>
using namespace std;
#define ll long long

/// @brief uses 1 based indexing.
vector<ll> tree(200005, 0);
ll lim = 200005;
ll p(ll k)
{
    return (k & (-k));
}

// adds x to ind.
void updateSum(ll ind, ll x)
{
    while (ind <= lim)
    {
        tree[ind] += x;
        ind += p(ind);
    }
}

ll getSum(ll k)
{ /// Returns Sum(1, k)
    ll s = 0;
    while (k > 0)
    {
        s += tree[k];
        k -= p(k);
    }
    return s;
}