//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
#include "edge.h"

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

    return 0;
}