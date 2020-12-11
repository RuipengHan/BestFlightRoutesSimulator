//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include <cmath> 
#include <queue>
#include <thread>
#include <chrono>
#include "graph.h"
#include "Vertex.h"
#include "edge.h"
#include "GraphInitializer.h"
#include "UserInterface.h"
#include "BFS.h"        /* bfs traversal */
#include <stdlib.h>     /* srand, rand */

using namespace std;
Edge::AirlineMap Edge::id_airline_info_map_ = {};
string Initializing = ".....";
int main() {
    string airport_file = "data_set/airports.dat.txt";
    string airline_file = "data_set/airlines.dat.txt";
    string route_file = "data_set/routes.dat.txt";
    Graph graph(true, true);

    GraphInitializer graphInitializer(graph, airport_file, airline_file, route_file);
    cout << "Initializing the graph";
    for (char c : Initializing) {
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << c << std::flush;
    }
    graphInitializer.GraphInit();
    UserInterface interface(graph);
    interface.Communicate();

    std::cout << "Program Finished." << std::endl;

    return 0;
}