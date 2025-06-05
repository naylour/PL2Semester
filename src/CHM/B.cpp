#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 5e6 + 5;
vector<int> parent(MAXN), rank_(MAXN);

int find(int x)
{
    if (x != parent[x])
        parent[x] = find(parent[x]);

    return parent[x];
}

bool unite(int x, int y)
{
    x = find(x);
    y = find(y);

    if (x == y)
        return false;

    if (rank_[x] < rank_[y])
        swap(x, y);

    parent[y] = x;

    if (rank_[x] == rank_[y])
        rank_[x]++;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        parent[i] = i;

    int answer = 0;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;

        if (unite(u, v))
            answer++;
        else
            break;
    }

    cout << answer << '\n';
    return 0;
}
