#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

int main() {
    ifstream inputFile("diameter.in");
    ofstream outputFile("diameter.out");

    int M, S, P;
    inputFile >> M >> S >> P; // Читаем количество вершин, начальную и конечную вершины

    vector<vector<long long>> graph(M, vector<long long>(M));

    // Считываем матрицу смежности
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            inputFile >> graph[i][j];
            if (graph[i][j] == -1 && i != j) {
                graph[i][j] = INF; // Заменяем -1 на INF для алгоритма
            }
        }
    }

    // Дейкстра
    vector<long long> dist(M, INF);
    dist[S - 1] = 0; // Начинаем с одной вершины, уменьшаем на 1 для обеспечения нулевой индексации

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, S - 1}); // (расстояние, вершина)

    while (!pq.empty()) {
        long long currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) {
            continue;
        }

        // Обход всех соседей
        for (int neighbor = 0; neighbor < M; ++neighbor) {
            if (graph[currentNode][neighbor] < INF) { // Если существует ребро
                long long newDist = currentDist + graph[currentNode][neighbor];
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }
    }

    // Выводим результат
    long long result = dist[P - 1]; // Уменьшаем на 1 для обеспечения нулевой индексации
    if (result == INF) {
        outputFile << -1 << endl; // Если путь не существует
    } else {
        outputFile << result << endl; // Выводим найденное расстояние
    }

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    return 0;
}
