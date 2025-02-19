vector<int> nextGreater(vector<int> a, int n)
{
    stack<int> s;
    vector<int> prev(n);
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() and a[s.top()] < a[i])
        {
            s.pop();
        }
        if (!s.empty() and a[s.top()] > a[i])
            prev[i] = s.top();
        else
            prev[i] = -1;

        s.push(i);
    }

    return prev;
}