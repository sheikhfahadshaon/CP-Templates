// starting with the name of almighty ALLAH
//  Practice is the only shortcut to improve
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define vc vector
#define vi vc<int>
#define vl vc<ll>
#define mp(x, y) make_pair(x, y)
#define yes cout << "YES" << '\n';
#define no cout << "NO" << '\n';
#define tst   \
    int t;    \
    cin >> t; \
    while (t--)
#define srt(v) sort(v.begin(), v.end());
#define rsrt(v) sort(v.rbegin(), v.rend());
#define rj                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);
#define rvs(v) reverse(v.begin(), v.end());
#define F first
#define S second
#define MOD 1000000007
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) (a * b) / gcd(a, b)
#define PI 2 * acos(0.0)
#define pii pair<int, int>
#define fr(i, a, b) for (int i = a; i <= b; i++)
#define coutv(v)           \
    for (auto it : v)      \
        cout << it << ' '; \
    cout << endl;
#define cinv(v)        \
    for (auto &it : v) \
        cin >> it;
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define ld long double
#define nl '\n'
const int N = 1e5;
using namespace std;
/* #ifndef ONLINE_JUDGE
#include "algo/debug.h"
#else
#define dbg(x...)
#endif */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}
void solve()
{
    int a;
    cin >> a;
    map<pii, int> m;
    vector<int> deg(a + 1);
    vector<pii> v;
    for (int i = 1; i < a; i++)
    {
        int x, y;
        cin >> x >> y;
        m[{x, y}]++;
        deg[x]++;
        deg[y]++;
    }
    for (int i = 1; i <= a; i++)
    {
        v.emplace_back(deg[i], i);
    }
    rsrt(v) int an = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = i + 1; j < a; j++)
        {
            int t = v[i].F + v[j].F - 1;
            if (m.find({v[i].S, v[j].S}) != m.end() or m.find({v[j].S, v[i].S}) != m.end())
            {
                t--;
            }
            an = max(an, t);
        }
    }
    cout << an << nl;
}
int main()
{
    /*#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE*/
    rj
        tst
        // int t;cin>>t;fr(i,1,t) cout<<"Case "<<i<<": ",solve();
        // ll t;scanf("%lld",&t);fr(i,1,t) printf("Case %lld: ",i),solve();
        solve();
    return 0;
}