#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj_matrix(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;

        for (int j = 0; j < n; ++j)
            adj_matrix[i][j] = row[j] - '0';
    }

    int start_node, end_node;

    cin >> start_node >> end_node;

    --start_node;
    --end_node;

    queue<int> order_visit;
    order_visit.push(start_node);

    vector<int> vector_distance(n, -1);
    vector_distance[start_node] = 0;

    vector<int> parent(n, -1);

    while (!order_visit.empty()) {
        int current_node = order_visit.front();
        order_visit.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor)
            if (adj_matrix[current_node][neighbor] == 1 && vector_distance[neighbor] == -1) {
                vector_distance[neighbor] = vector_distance[current_node] + 1;
                parent[neighbor] = current_node;
                order_visit.push(neighbor);
            }
    }

    if (vector_distance[end_node] == -1)
        cout << -1 << endl;
    else {
        cout << vector_distance[end_node] << endl;

        vector<int> path;
        int current = end_node;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        for (int i = path.size() - 1; i >= 0; --i)
            cout << path[i] + 1 << (i == 0 ? "" : " ");

        cout << endl;
    }

    return 0;
}
