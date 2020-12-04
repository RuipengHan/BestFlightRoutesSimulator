//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
using namespace std;
/*
 * This process route data by going through all possible departure/dest airport.
 * The edge is initially empty of airlines. This function is just responsible for connecting a basic line between nodes.
 */
bool connectVertice(string& filename, Graph& graph) {

    ifstream route(filename);
    string each_row;
    if (route.is_open()) {
        while (getline(route, each_row)) {

        }
        return true;
    }
    return false;
}

bool addAirportVertices(string& filename, Graph& graph) {
    ifstream airline(filename);
    string each_row;
    int count = 0;
    if (airline.is_open()) {
        while (getline(airline, each_row)) {
            // Process this row;
            Vertex new_vertex(each_row);
            // Add the new vertex to graph;
            if (!graph.vertexExists(new_vertex))
                graph.insertVertex(new_vertex);
            //new_vertex.print();
            count++;
        }
        std::cout<< "AFTER READ, WE HAVE NUM OF AIRPORTS: " << count << std::endl;
        return true;
    }

    return false;
}

bool initializeEdge(string& filename) {
    ifstream airline(filename);
    string each_row;
    if (airline.is_open()) {
        while (getline(airline, each_row)) {
            // Process this row;
        }
        return true;
    }

    return false;
}

int main() {
    std::cout<< "Hello World." << std::endl;
    string airport_file = "data_set/airports.dat.txt";
    string airline_file = "data_set/airlines.dat.txt";
    string route_file = "data_set/routes.dat.txt";
    Graph graph(true, true);

    // Add vertices first;
    if (!addAirportVertices(airport_file, graph))
        std::cout<< "Oops cannot read airport file." << std::endl;

    // Connect edge.
    if (!connectVertice(route_file, graph))
        std::cout<< "Invalid airline_file." << std::endl;

    if (!initializeEdge(route_file))
        std::cout<< "Oops cannot read route file." << std::endl;

    std::cout<< "NUMBER OF AIRPORT called using getVertices.size(): " << graph.getVertices().size() << std::endl;

    return 0;
}