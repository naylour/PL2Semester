#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

int n, q;
vector<long long> a(MAXN), tree(4 * MAXN);

void build(int v, int tl, int tr)
{
    if (tl == tr)
        tree[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

void update(int v, int tl, int tr, int pos, long long add)
{
    if (tl == tr)
        tree[v] += add;
    else
    {
        int tm = (tl + tr) / 2;

        if (pos <= tm)
            update(v * 2, tl, tm, pos, add);
        else
            update(v * 2 + 1, tm + 1, tr, pos, add);

        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

long long sum(int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return tree[v];

    int tm = (tl + tr) / 2;

    return sum(v * 2, tl, tm, l, min(r, tm)) +
           sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    build(1, 0, n - 1);

    for (int i = 0; i < q; ++i)
    {
        char type;
        cin >> type;

        if (type == 'U')
        {
            int p;
            long long x;
            cin >> p >> x;
            update(1, 0, n - 1, p - 1, x);
        }
        else if (type == 'S')
        {
            int l, r;
            cin >> l >> r;
            cout << sum(1, 0, n - 1, l - 1, r - 1) << '\n';
        }
    }

    return 0;
}
