#include "D:\Codes\CP Templates\hashing\double_hasing.cpp"
using namespace std;

int lcp(int i, int j, int x, int y)
{
    int l = 1, r = min(j - i + 1, y - x + 1), ans = 0;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (get_hash(i, i + mid - 1) == get_hash(x, x + mid - 1))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}
int compare(string s, int i, int j, int x, int y)
{
    /* @brief
        0 -> equal
       -1 -> lesser
        1 -> greater
    */
    int l = lcp(i, j, x, y);
    if (j - i == y - x and l == j - i + 1)
        return 0; // equal
    else if (l == j - i + 1)
        return -1;
    else if (l == y - x + 1)
        return 1;
    // i + l or x + l may not exist so corner cases are handled separately.
    return (s[i + l] < s[x + l] ? -1 : 1);
}

int32_t main()
{
    prec();
    string s = "abcabcc";
    build(s);

    cout << compare(s, 0, 2, 4, 7);
}
