#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> bfs(int startCity, const vector<vector<int>>& graph) {
    int numCities = graph.size();
    vector<int> distances(numCities, -1);
    queue<int> cityQueue;
    distances[startCity] = 0;
    cityQueue.push(startCity);

    while (!cityQueue.empty()) {
        int currentCity = cityQueue.front();
        cityQueue.pop();

        for (int neighbor : graph[currentCity]) {
            if (distances[neighbor] == -1) {
                distances[neighbor] = distances[currentCity] + 1;
                cityQueue.push(neighbor);
            }
        }
    }

    return distances;
}

int main() {
    int numCities, numRails;
    cin >> numCities >> numRails;

    vector<vector<int>> railGraph(numCities + 1);
    vector<vector<int>> roadGraph(numCities + 1);

    for (int i = 0; i < numRails; ++i) {
        int cityA, cityB;
        cin >> cityA >> cityB;
        railGraph[cityA].push_back(cityB);
        railGraph[cityB].push_back(cityA);
    }

    for (int city1 = 1; city1 <= numCities; ++city1) {
        for (int city2 = city1 + 1; city2 <= numCities; ++city2) {
            if (find(railGraph[city1].begin(), railGraph[city1].end(), city2) == railGraph[city1].end()) {
                roadGraph[city1].push_back(city2);
                roadGraph[city2].push_back(city1);
            }
        }
    }

    vector<int> trainDistances = bfs(1, railGraph);
    vector<int> busDistances = bfs(1, roadGraph);

    int minimumTime = -1;

    for (int i = 1; i <= numCities; ++i) {
        if (trainDistances[i] != -1 && busDistances[i] != -1) {
            if (i != numCities) {
                continue;
            }
            int time = max(trainDistances[i], busDistances[i]);
            if (minimumTime == -1 || time < minimumTime) {
                minimumTime = time;
            }
        }
    }

    cout << minimumTime << endl;
    return 0;
}
