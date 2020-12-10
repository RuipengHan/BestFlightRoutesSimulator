//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include <cmath> 
#include <queue>
#include "graph.h"
#include "Vertex.h"
#include "edge.h"

#include "BFS.h"        /* bfs traversal */
#include <stdlib.h>     /* srand, rand */

using namespace std;
Edge::AirlineMap Edge::id_airline_info_map_ = {};


/**
 * Dijkstra algorithm implementation
 * @param graph 
 * @param s The starting vertex
 * @return a map with every vertex as key and its corresponding previous vertex as value
 */
map<Vertex, Vertex> Dijkstra(Graph& graph, Vertex& s) {
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

#include "GraphInitializer.h"
int main() {
    std::cout<< "Hello World." << std::endl;
    string airport_file = "data_set/airports.dat.txt";
    string airline_file = "data_set/airlines.dat.txt";
    string route_file = "data_set/routes.dat.txt";
    Graph graph(true, true);

    GraphInitializer graphInitializer(graph, airport_file, airline_file, route_file);
    graphInitializer.GraphInit();

    vector<Vertex> all_airports = graph.getVertices();
    //Vertex start = all_airports[rand() % all_airports.size()];
    //Vertex start = all_airports[3247];
    //Vertex start = graph.getVertexById("3682");
    Vertex start = graph.getVertexByName("Taoxian Airport");
    //Vertex end = all_airports[rand() % all_airports.size()];
    //Vertex end = all_airports[3251];
    //Vertex end = graph.getVertexById("3494");
    Vertex end = graph.getVertexByName("Chicago O\'Hare International Airport");
    BFS bfs(graph, start, end, 3);
    bfs.findPath();

    std::cout << "Hello World." << std::endl;

    return 0;
}