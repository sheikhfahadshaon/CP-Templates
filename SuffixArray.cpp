/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s += "$";

    int n = s.size();

    vector<pair<char, int>> v;
    for (int i = 0; i < n; i++)
        v.push_back({s[i], i});
    sort(v.begin(), v.end());

    vector<int> pos;
    for (int i = 0; i < n; i++)
        pos.push_back(v[i].second);

    vector<int> c(n);
    c[pos[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        c[pos[i]] = c[pos[i - 1]] + (s[pos[i]] != s[pos[i - 1]]);
    }

    int k = 0;
    while ((1 << k) < n)
    {
        vector<pair<pair<int, int>, int>> v(n);
        for (int i = 0; i < n; i++)
        {
            v[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }

        sort(v.begin(), v.end());
        for (int i = 0; i < n; i++)
            pos[i] = v[i].second;
        c[v[0].second] = 0;
        for (int i = 1; i < n; i++)
        {
            c[v[i].second] = c[v[i - 1].second] + (v[i].first != v[i - 1].first);
        }

        k++;
    }

    for (int i = 0; i < n; i++)
        cout << pos[i] << ' ';
    cout << endl;
}