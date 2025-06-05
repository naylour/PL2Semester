#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1005;

int parent[MAXN];

int find(int x)
{
    if (x != parent[x])
        parent[x] = find(parent[x]);

    return parent[x];
}

bool unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return false;

    parent[b] = a;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i)
        parent[i] = i;

    vector<pair<int, int>> redundant;
    vector<pair<int, int>> edges;

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;

        if (!unite(u, v))
            redundant.emplace_back(u, v);
        else
            edges.emplace_back(u, v);
    }

    for (int i = 1; i <= n; ++i)
        parent[i] = i;

    for (auto &e : edges)
        unite(e.first, e.second);

    vector<pair<int, int>> new_edges;

    for (int i = 2; i <= n; ++i)
        if (find(i) != find(1))
        {
            new_edges.emplace_back(1, i);
            unite(1, i);
        }

    int t = new_edges.size();

    cout << t << '\n';

    for (int i = 0; i < t; ++i)
    {
        auto [a, b] = redundant[i];
        auto [u, v] = new_edges[i];
        cout << a << ' ' << b << ' ' << u << ' ' << v << '\n';
    }

    return 0;
}
