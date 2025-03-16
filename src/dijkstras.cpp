#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    G.resize(n, INF);
    previous.resize(n, -1);
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    priority_queue<int> pq;
    pq.push(source);
    distance[source] = 0;

    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();
        
        if (visited[u] = true) continue;
        visited[u] = true;

        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>&, const vector<int> previous, int destination) {
    vector<int> path;
    if (previous[destination] == -1) return path;

    for (int v = destination; v != -1; v = previous[v])
        path.push_back(v);

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    cout << "0 " << endl;
    for (size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << "Total cost is " << total << endl;
}
