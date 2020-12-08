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
<<<<<<< HEAD
    map<string, Vertex> airport_dict;

    // Add vertices first meanwhile correlating each airport vertex to its id (populate the airport_dict). Checked Okay
    if (!addAirportVertices(airport_file, graph, airport_dict))
        std::cout<< "Oops cannot read airport file." << std::endl;

    // Then connect edge. Checked Okay
    if (!connectVertice(route_file, graph, airport_dict))
        std::cout<< "Invalid airline_file." << std::endl;

    // Then map the airline id to its data; Checked Okay
    if (!processAirlineFile(airline_file))
        std::cout<< "Oops cannot read route file." << std::endl;

    initializeEdge(graph);
    std::cout<< "NUMBER Airlines: " << Edge::id_airline_info_map_.size() << std::endl;
    std::cout<< "NUMBER OF AIRPORT called using getVertices.size(): " << graph.getVertices().size() << std::endl;
    std::cout<< "SIZE OF THE MAP: " << airport_dict.size() << std::endl;
    std::cout<< "NUMBER OF EDGES IN THE GRAPH: " << graph.getEdges().size() << std::endl;

    vector<Vertex> all_airports = graph.getVertices();
    //Vertex start = all_airports[rand() % all_airports.size()];
    //Vertex start = all_airports[3247];
    Vertex start = graph.getVertexById("3682");
    //Vertex start = graph.getVertexByName("Newark Liberty International Airport");
    //Vertex end = all_airports[rand() % all_airports.size()];
    //Vertex end = all_airports[3251];
    Vertex end = graph.getVertexById("3494");
    //Vertex start = graph.getVertexByName("Newark Liberty International Airport");
    BFS bfs(graph, start, end, 3);
    bfs.findPath();

    std::cout << "Hello World." << std::endl;

=======
    GraphInitializer graphInitializer(graph, airport_file, airline_file, route_file);
    graphInitializer.GraphInit();

>>>>>>> e67559ebaa7f53b4ad1c854a4d63af79edd230d1
    return 0;
}