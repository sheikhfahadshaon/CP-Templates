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