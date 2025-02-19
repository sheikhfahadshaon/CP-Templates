#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 30;
const int M = 100;

// NEVER use rand() function because rand() will always generate same random values even if you run the same code multiple times
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); // using current time as seed, so it will always generate different random values if you run this code multiple times
long long get_rand(long long l, long long r)
{ // random number from l to r
    assert(l <= r);
    return l + rnd() % (r - l + 1);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout << 1 << endl;
    int n = get_rand(2, 1000);
    cout << n << endl;
    ordered_set s1, s2;
    s1.insert(1);
    for (int i = 2; i <= n; i++)
        s2.insert(i);

    for (int i = 1; i < n; i++)
    {
        int sz = s1.size();
        int ord = get_rand(0, sz - 1);
        int x = *s1.find_by_order(ord);
        cout << x << ' ';

        sz = s2.size();
        ord = get_rand(0, sz - 1);
        x = *s2.find_by_order(ord);
        cout << x << '\n';
        s2.erase(s2.find(x));
        s1.insert(x);
    }

    return 0;
}