#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> adj_matrix[i][j];

    int start_node, end_node;

    std::cin >> start_node >> end_node;

    --start_node;
    --end_node;

    std::queue<int> order_visit;
    order_visit.push(start_node);

    std::vector<int> vector_distance(n, -1);
    vector_distance[start_node] = 0;

    while (!order_visit.empty()) {
        int current_node = order_visit.front();
        order_visit.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor)
            if (adj_matrix[current_node][neighbor] == 1 && vector_distance[neighbor] == -1) {
                vector_distance[neighbor] = vector_distance[current_node] + 1;
                order_visit.push(neighbor);
            }
    }

    std::cout << vector_distance[end_node] << '\n';

    return 0;
}
