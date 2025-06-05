#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> bit(MAXN), a(MAXN);

void update(int i, int delta)
{
    while (i < MAXN)
    {
        bit[i] += delta;
        i += i & -i;
    }
}

int query(int i)
{
    int res = 0;

    while (i > 0)
    {
        res += bit[i];
        i -= i & -i;
    }

    return res;
}

int find_kth(int k, int n)
{
    int l = 1, r = n, ans = 0;

    while (l <= r)
    {
        int m = (l + r) / 2;

        if (query(m) >= k)
        {
            ans = m;
            r = m - 1;
        }
        else
            l = m + 1;
    }
    return query(ans) == k ? ans : 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    while (q--)
    {
        char type;
        int k;

        cin >> type >> k;

        if (type == '!')
        {
            int delta = a[k] ? -1 : 1;
            a[k] ^= 1;
            update(k, delta);
        }
        else
        {
            cout << find_kth(k, n) << '\n';
        }
    }

    return 0;
}
