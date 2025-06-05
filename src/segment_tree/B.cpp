#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 5;
vector<long long> bit(MAXN);

void add(int i, long long val)
{
    while (i < MAXN)
    {
        bit[i] += val;
        i += i & -i;
    }
}

long long sum(int i)
{
    long long res = 0;

    while (i > 0)
    {
        res += bit[i];
        i -= i & -i;
    }

    return res;
}

long long range_sum(int l, int r)
{
    return sum(r) - sum(l - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m--)
    {
        char type;
        cin >> type;

        if (type == '+')
        {
            int i;
            long long c;
            cin >> i >> c;
            add(i, c);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << range_sum(l, r) << "\n";
        }
    }

    return 0;
}
