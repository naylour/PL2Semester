#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int x, y;
    cin >> x >> y;

    --x;
    --y;

    vector<vector<pair<int, int>>> roads(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;

        --u;
        --v;

        roads[u].emplace_back(v, w);
        roads[v].emplace_back(u, w);
    }

    vector<long long> t(n), c(n);

    for (int i = 0; i < n; ++i)
        cin >> t[i] >> c[i];

    vector<vector<pair<int, long long>>> taxiGraph(n);

    for (int i = 0; i < n; ++i)
    {
        vector<long long> dist(n, INF);
        dist[i] = 0;

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.emplace(0, i);

        while (!pq.empty())
        {
            auto [d, v] = pq.top();
            pq.pop();

            if (d > dist[v])
                continue;

            for (auto [to, w] : roads[v])
                if (dist[v] + w < dist[to])
                {
                    dist[to] = dist[v] + w;
                    pq.emplace(dist[to], to);
                }
        }

        for (int j = 0; j < n; ++j)
            if (i != j && dist[j] <= t[i])
                taxiGraph[i].emplace_back(j, c[i]);
    }

    vector<long long> cost(n, INF);
    cost[x] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace(0, x);

    while (!pq.empty())
    {
        auto [curCost, v] = pq.top();

        pq.pop();

        if (curCost > cost[v])
            continue;

        for (auto [to, price] : taxiGraph[v])
            if (cost[v] + price < cost[to])
            {
                cost[to] = cost[v] + price;
                pq.emplace(cost[to], to);
            }
    }

    if (cost[y] == INF)
        cout << -1 << '\n';
    else
        cout << cost[y] << '\n';

    return 0;
}
