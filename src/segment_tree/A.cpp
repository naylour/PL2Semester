#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e9;

long long int n, m;

vector<long long> a;
vector<long long> tree;

void build(long long v, long long tl, long long tr)
{
    if (tl == tr)
        tree[v] = a[tl];
    else
    {
        long long tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
}

void update(long long v, long long tl, long long tr, long long pos, long long new_val)
{
    if (tl == tr)
        tree[v] += new_val;
    else
    {
        long long tm = (tl + tr) / 2;

        if (pos <= tm)
            update(2 * v, tl, tm, pos, new_val);
        else
            update(2 * v + 1, tm + 1, tr, pos, new_val);

        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
}

long long get_min(long long v, long long tl, long long tr, long long l, long long r)
{
    if (l > r)
        return INF;
    if (l == tl && r == tr)
        return tree[v];

    long long tm = (tl + tr) / 2;

    return min(
        get_min(2 * v, tl, tm, l, min(r, tm)),
        get_min(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main()
{
    cin >> n >> m;

    a.resize(n);
    tree.resize(4 * n);

    for (long long i = 0; i < n; i++)
        cin >> a[i];

    build(1, 0, n - 1);

    for (long long i = 0; i < m; i++)
    {
        char type;
        cin >> type;

        if (type == '?')
        {
            long long l, r;
            cin >> l >> r;
            cout << get_min(1, 0, n - 1, l - 1, r - 1) << endl;
        }
        else if (type == '+')
        {
            long long idx, val;
            cin >> idx >> val;
            update(1, 0, n - 1, idx - 1, val);
        }
    }

    return 0;
}
