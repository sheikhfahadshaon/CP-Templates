int kadane(vector<int> &arr)
{
    int best = 0, sum = 0, i;
    for (auto it : arr)
    {
        sum = max(it, sum + it);
        best = max(best, sum);
    }
    return best;
}