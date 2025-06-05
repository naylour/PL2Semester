#include <iostream>
#include <vector>
using namespace std;

void query(int l, int r, int ql, int qr, vector<pair<int, int>> &result)
{
    if (r < ql || l > qr)
        return;

    if (ql <= l && r <= qr)
    {
        result.emplace_back(l, r);
        return;
    }

    int m = (l + r) / 2;

    query(l, m, ql, qr, result);
    query(m + 1, r, ql, qr, result);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int n, l, r;
        cin >> n >> l >> r;

        vector<pair<int, int>> result;

        query(1, n, l, r, result);

        for (auto &p : result)
            cout << "(" << p.first << ", " << p.second << ") ";
        cout << '\n';
    }

    return 0;
}
