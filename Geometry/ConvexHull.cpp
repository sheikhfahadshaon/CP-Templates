/*BISMILLAH*/
#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

int SQdist(Point p, Point q)
{
    return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

int orientation(Point p, Point q, Point r)
{ // orientation of p and r w.r.t. q
    int o = (p.x - q.x) * (r.y - q.y) - (p.y - q.y) * (r.x - q.x);
    if (o == 0)
        return 0;
    return (o < 0 ? -1 : 1); // -1 for clockwise
}

Point nextToTop(stack<Point> &s)
{
    Point tmp = s.top();
    s.pop();
    Point ret = s.top();
    s.push(tmp);
    return ret;
}

vector<Point> ConvexHull(vector<Point> &points)
{
    int n = points.size();

    // Find the minimum point
    int mnY = INT_MAX, mnX = INT_MAX, mnInd = -1;
    for (int i = 0; i < n; i++)
    {
        if (points[i].y < mnY)
        {
            mnY = points[i].y, mnX = points[i].x, mnInd = i;
        }
        else if (points[i].y == mnY and points[i].x < mnX)
        {
            mnX = points[i].x;
            mnInd = i;
        }
    }

    if (mnInd != 0)
        swap(points[0], points[mnInd]);
    Point P0 = points[0];

    // sort w.r.t polar angle with p0
    auto cmp = [&](Point &a, Point &b) -> bool
    {
        int o = orientation(P0, a, b);
        if (o == 0)
            return SQdist(P0, a) <= SQdist(P0, b);
        return o == -1;
    };
    sort(points.begin() + 1, points.end(), cmp);

    // Now remove the co-linear points by keeping just the farthest one
    vector<Point> pointsModified;
    pointsModified.push_back(P0);
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 and orientation(P0, points[i], points[i + 1]) == 0)
            i++;
        pointsModified.push_back(points[i]);
    }

    stack<Point> s;
    if (pointsModified.size() <= 3)
        return pointsModified;

    s.push(P0);
    s.push(pointsModified[1]);
    s.push(pointsModified[2]);
    for (int i = 3; i < pointsModified.size(); i++)
    {
        while (s.size() > 1 and orientation(nextToTop(s), s.top(), pointsModified[i]) == 1)
            s.pop();
        s.push(pointsModified[i]);
    }

    vector<Point> ret;
    while (!s.empty())
    {
        ret.push_back(s.top());
        s.pop();
    }
    return ret;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};

    vector<Point> Hull = ConvexHull(points);
    for (Point p : Hull)
        cout << p.x << ' ' << p.y << endl;
}