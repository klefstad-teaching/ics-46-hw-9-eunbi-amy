#include "dijkstras.h"

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
