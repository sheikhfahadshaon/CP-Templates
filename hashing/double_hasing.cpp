#include <bits/stdc++.h>
using namespace std;

#define int long long

const int p1 = 137;
const int mod1 = 127657753;
const int p2 = 277;
const int mod2 = 987654319;
const int N = 1e5 + 9;
pair<int, int> pw[N], ipw[N], pref[N];
int invp1, invp2;

int BigMod(int a, int p, int mod)
{
    int ans = 1;
    while (p)
    {
        if (p & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        p >>= 1;
    }

    return ans;
}

void prec()
{
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i].first = 1LL * pw[i - 1].first * p1 % mod1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % mod2;
    }

    invp1 = BigMod(p1, mod1 - 2, mod1);
    invp2 = BigMod(p2, mod2 - 2, mod2);

    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++)
    {
        ipw[i].first = 1LL * ipw[i - 1].first * invp1 % mod1;
        ipw[i].second = 1LL * ipw[i - 1].second * invp2 % mod2;
    }
}

pair<int, int> string_hash(string s)
{
    int n = s.size();
    int hs1 = 0;
    for (int i = 0; i < n; i++)
    {
        hs1 += 1LL * s[i] * pw[i].first % mod1;
        hs1 %= mod1;
    }
    int hs2 = 0;
    for (int i = 0; i < n; i++)
    {
        hs2 += 1LL * s[i] * pw[i].second % mod2;
        hs2 %= mod2;
    }
    return {hs1, hs2};
}

void build(string s)
{
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        pref[i].first = 1LL * s[i] * pw[i].first % mod1;
        if (i)
            (pref[i].first += pref[i - 1].first) %= mod1;

        pref[i].second = 1LL * s[i] * pw[i].second % mod2;
        if (i)
            (pref[i].second += pref[i - 1].second) %= mod2;
    }
}

pair<int, int> get_hash(int i, int j)
{
    assert(i <= j);

    pair<int, int> hs({0, 0});

    hs.first = pref[j].first;
    if (i)
        hs.first = (hs.first - pref[i - 1].first + mod1) % mod1;
    hs.first = 1LL * hs.first * ipw[i].first % mod1;

    hs.second = pref[j].second;
    if (i)
        hs.second = (hs.second - pref[i - 1].second + mod2) % mod2;
    hs.second = 1LL * hs.second * ipw[i].second % mod2;

    return hs;
}
