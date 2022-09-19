#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <climits>
#include <numeric>
#include <random>

using namespace std;

int n = 10;
vector<int> a(n + 1, 0), SegmentTree(4 * n + 1, 0);

int sum(int x, int tl, int tr, int l, int r)
{
    if (tl > tr)
        return 0;
    if (tl == l && tr == r)
        return SegmentTree[x];
    int mid = (tl + tr) / 2;

    if (r <= mid)
        return sum(x * 2, tl, mid, l, r);
    else if (l > mid)
        return sum((x * 2) + 1, mid + 1, tr, l, r);
    else
        return sum(x * 2, tl, mid, l, mid) + sum((x * 2) + 1, mid + 1, tr, mid + 1, r);
}

void update(int x, int l, int r, int ind, int val)
{
    if (l == r)
    {
        a[l] = SegmentTree[x] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid)
        update(x * 2, l, mid, ind, val);
    else
        update((x * 2) + 1, mid + 1, r, ind, val);
    SegmentTree[x] = SegmentTree[x * 2] + SegmentTree[(x * 2) + 1];
    return;
}

void build(int x, int l, int r)
{
    if (l == r)
    {
        SegmentTree[x] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build((x * 2) + 1, mid + 1, r);
    SegmentTree[x] = SegmentTree[x * 2] + SegmentTree[(x * 2) + 1];
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i <= n; i++)
        a[i] = i;

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << "\n";

    build(1, 1, n);
    cout << sum(1, 1, n, 3, 9) << "\n";

    update(1, 1, n, 7, 29);
    cout << sum(1, 1, n, 3, 9) << "\n";
}