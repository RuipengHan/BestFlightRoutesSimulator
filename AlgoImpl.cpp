#include "AlgoImpl.h"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

void AlgoImpl::print(vector<Vertex>& path) {
    int size = path.size();
    cout << GREEN << path[0].name_ << RESET << BLUE << "->" << RESET;
    for (int i = 1; i < size - 1; i++)
        cout << RED << path[i].name_ << BLUE "->";
    cout << GREEN << path[size - 1].name_ << endl;
}

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
        cout << GREEN << "u: " << u.name_ << " " << u.airport_id_ << RESET << endl;
        Q.pop();
        T.insertVertex(u);
        vector<Vertex> neighbors = graph.getAdjacent(u);
        cout << "adjacent" << endl;
        for (Vertex v : neighbors) {
            cout << RED << "v: " << v.name_ << " " << v.airport_id_ << RESET << endl;
            vector<Vertex> T_neighbors = T.getAdjacent(u);
            if (find(T_neighbors.begin(), T_neighbors.end(), v) == T_neighbors.end()) {
                cout << graph.getEdgeWeight(u, v) << " " << d[u] << " " << d[v] << endl;
                if (graph.getEdgeWeight(u, v) + d[u] < d[v]) {
                    cout << YELLOW << "add edge " << "v: " << v.name_ << " " << v.airport_id_ << " u: " << u.name_ << " " << u.airport_id_ << RESET << endl;
                    d[v] = graph.getEdgeWeight(u, v) + d[u];
                    //p.insert({v, u});
                    p[v] = u;
                    T.insertEdge(u, v);
                    Q.push({v, d[v]});
                    for (auto& each: p) {
                        cout << each.first.name_ << " " << each.first.airport_id_ << " ->> " << each.second.name_ << " " << each.second.airport_id_ << endl;
                    }
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
    cout << "Are you ok? aoligai" << endl;
    for (auto& each: prevs) {
        cout << each.first.name_ << " " << each.first.airport_id_ << " ->> " << each.second.name_ << " " << each.second.airport_id_ << endl;
    }
    cout << "Are you ok?" << endl;
    Vertex curr = end;
    cout << curr.name_ << " " << curr.airport_id_ << endl;
    while (curr != start) {
        output.insert(output.begin(), prevs[curr]);
        curr = prevs[curr];
        cout << curr.name_ << " " << curr.airport_id_ << endl;
    }

    return output;
}

vector<Vertex> AlgoImpl::landmark(Graph& graph, Vertex& start, Vertex& end, Vertex& middle) {
    vector<Vertex> output = getShortestPath(graph, start, middle);
    output.pop_back(); // pop the last vertex in order not to add duplicate landmark
    cout << "Hello mid reached" << endl;
    vector<Vertex> path2 = getShortestPath(graph, middle, end);
    cout << "Hello" << endl;
    for (unsigned i = 0; i < path2.size(); i++)
        cout << path2[i].name_ << " " << path2[i].airport_id_ << " -> ";
    cout << "Hello" << endl;
    output.insert(output.end(), path2.begin(), path2.end()); // append the second half path to the end

    return output;
}

