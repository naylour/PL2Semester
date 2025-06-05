#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
public:
    UnionFind(int n) : parent(n + 1), rank(n + 1, 0), componentCount(n)
    {
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]);

        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] < rank[rootV])
                parent[rootU] = rootV;

            else if (rank[rootU] > rank[rootV])
                parent[rootV] = rootU;

            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }

            componentCount--;
        }
    }

    int getComponentCount() const
    {
        return componentCount;
    }

private:
    vector<int> parent;
    vector<int> rank;

    int componentCount;
};

int main()
{
    int N, M;
    cin >> N >> M;

    UnionFind uf(N);

    for (int i = 0; i < M; ++i)
    {
        int u, v;
        cin >> u >> v;

        uf.unionSets(u, v);

        cout << uf.getComponentCount() << endl;
    }

    return 0;
}
