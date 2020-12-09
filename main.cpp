//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
#include "edge.h"

#include "BFS.h"        /* bfs traversal */
#include <stdlib.h>     /* srand, rand */

using namespace std;
Edge::AirlineMap Edge::id_airline_info_map_ = {};

#include "GraphInitializer.h"
int main() {
    std::cout<< "Hello World." << std::endl;
    string airport_file = "data_set/airports.dat.txt";
    string airline_file = "data_set/airlines.dat.txt";
    string route_file = "data_set/routes.dat.txt";
    Graph graph(true, true);

    GraphInitializer graphInitializer(graph, airport_file, airline_file, route_file);
    graphInitializer.GraphInit();
    /*
    vector<Vertex> all_airports = graph.getVertices();
    //Vertex start = all_airports[rand() % all_airports.size()];
    //Vertex start = all_airports[3247];
    Vertex start = graph.getVertexById("3682");
    //Vertex start = graph.getVertexByName("Newark Liberty International Airport");
    //Vertex end = all_airports[rand() % all_airports.size()];
    //Vertex end = all_airports[3251];
    Vertex end = graph.getVertexById("3494");
    //Vertex start = graph.getVertexByName("Newark Liberty International Airport");
    BFS bfs(graph, start, end, 2);
    bfs.findPath();
    */

    std::cout << "Hello World." << std::endl;

    return 0;
}