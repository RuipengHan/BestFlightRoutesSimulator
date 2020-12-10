#include "AlgoImpl.h"

AlgoImpl::AlgoImpl(Graph& graph, Vertex& start) {}

map<Vertex, Vertex> AlgoImpl::Dijkstra(Graph& graph, Vertex& s) {
    map<Vertex, Vertex> p;
    map<Vertex, int> d;
    for (Vertex& v : graph.getVertices()) {
        d.insert({v, INT_MAX});
    }
    d[s] = 0;

    priority_queue<pair<Vertex, int>, vector<pair<Vertex, int>>, greater<pair<Vertex, int>>> Q;
    Q.push({s, 0});
    Graph T(true, true);

    while(!Q.empty()) {
        Vertex u = Q.top().first;
        Q.pop();
        T.insertVertex(u);
        vector<Vertex> neighbors = graph.getAdjacent(u);
        for (Vertex v : neighbors) {
            vector<Vertex> T_neighbors = T.getAdjacent(u);
            if (find(T_neighbors.begin(), T_neighbors.end(), v) == T_neighbors.end()) {
                if (graph.getEdgeWeight(u, v) + d[u] < d[v]) {
                    d[v] = graph.getEdgeWeight(u, v) + d[u];
                    p.insert({v, u});
                    T.insertEdge(u, v);
                    Q.push({v, d[v]});
                }
            }
        }
    }

    return p;
}

vector<Vertex> AlgoImpl::getShortestPath(Graph& graph, Vertex& start, Vertex& end) {
    vector<Vertex> output;
    output.push_back(end);

    map<Vertex, Vertex> prevs = Dijkstra(graph, start);

    Vertex curr = end;
    while (curr != start) {
        output.insert(output.begin(), prevs[curr]);
        curr = prevs[curr];
    }

    return output;
}

vector<Vertex> AlgoImpl::landmark(Graph& graph, Vertex& start, Vertex& end, Vertex& middle) {
    vector<Vertex> output = getShortestPath(graph, start, middle);
    output.pop_back(); // pop the last vertex in order not to add duplicate landmark

    vector<Vertex> path2 = getShortestPath(graph, middle, end);
    output.insert(output.end(), path2.begin(), path2.end()); // append the second half path to the end

    return output;
}

