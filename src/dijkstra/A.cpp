#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int main()
{
    ifstream fin("dijkstra.in");
    ofstream fout("dijkstra.out");

    int N, S, F;

    fin >> N >> S >> F;

    S--;
    F--;

    vector<vector<int>> graph(N, vector<int>(N));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            fin >> graph[i][j];

    vector<int> dist(N, INF);
    vector<bool> visited(N, false);

    dist[S] = 0;

    for (int i = 0; i < N; ++i)
    {
        int v = -1;
        for (int j = 0; j < N; ++j)
            if (!visited[j] && (v == -1 || dist[j] < dist[v]))
                v = j;

        if (dist[v] == INF)
            break;

        visited[v] = true;

        for (int u = 0; u < N; ++u)
            if (graph[v][u] != -1 && dist[v] + graph[v][u] < dist[u])
                dist[u] = dist[v] + graph[v][u];
    }

    if (dist[F] == INF)
        fout << -1 << endl;
    else
        fout << dist[F] << endl;

    return 0;
}
