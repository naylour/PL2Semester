#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

int main()
{
    ifstream fin("distance.in");
    ofstream fout("distance.out");

    int N, M, S, F;
    fin >> N >> M >> S >> F;

    S--;
    F--;

    vector<vector<pair<int, int>>> graph(N);

    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        fin >> u >> v >> w;

        u--;
        v--;

        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    vector<int> dist(N, INF);
    vector<int> parent(N, -1);

    dist[S] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    pq.emplace(0, S);

    while (!pq.empty())
    {
        auto [d, v] = pq.top();
        pq.pop();

        if (d > dist[v])
            continue;

        for (auto [to, w] : graph[v])
        {
            if (dist[v] + w < dist[to])
            {
                dist[to] = dist[v] + w;
                parent[to] = v;
                pq.emplace(dist[to], to);
            }
        }
    }

    if (dist[F] == INF)
    {
        fout << -1 << endl;
        return 0;
    }

    fout << dist[F] << endl;

    vector<int> path;

    for (int v = F; v != -1; v = parent[v])
        path.push_back(v + 1);

    reverse(path.begin(), path.end());

    for (int v : path)
        fout << v << ' ';

    fout << endl;

    return 0;
}
