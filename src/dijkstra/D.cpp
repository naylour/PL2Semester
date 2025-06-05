#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int MAXN = 100000;
const long long INF = numeric_limits<long long>::max();

struct Edge
{
    int to;
    long long weight;
};

vector<Edge> graph[MAXN + 1];

vector<long long> dijkstra(int start, int n)
{
    vector<long long> dist(n + 1, INF);
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;

        for (const Edge &edge : graph[u])
        {
            int v = edge.to;
            long long w = edge.weight;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;

    vector<pair<int, pair<int, int>>> edges; // хранение дорог как (вес, (город1, город2))

    for (int i = 0; i < m; i++)
    {
        int v, u, w;
        cin >> v >> u >> w;
        graph[v].push_back({u, w});
        graph[u].push_back({v, w});
        edges.push_back({w, {v, u}}); // сохраняем ребро
    }

    long long l;
    cin >> l;

    vector<long long> distances = dijkstra(s, n);
    int count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (distances[i] == l)
        {
            count++;
        }
    }

    // Проверка на нахождение шахт на дорогах
    for (auto &edge : edges)
    {
        int v = edge.second.first;
        int u = edge.second.second;
        long long w = edge.first;

        long long d1 = distances[v];
        long long d2 = distances[u];

        // Проверяем возможные позиции на дороге
        if ((d1 < l && d2 > l) || (d1 > l && d2 < l))
        {
            if (abs(d1 - d2) >= l)
            {
                count++;
            }
        }

        // Проверка на случай, если точка на середине дороги
        if (d1 + w == l || d2 + w == l)
        {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}
