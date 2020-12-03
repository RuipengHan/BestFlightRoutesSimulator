//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
using namespace std;

bool processAirlineData(string& filename) {

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

bool processAirportData(string& filename) {
    ifstream airline(filename);
    string each_row;
    int count = 0;
    if (airline.is_open()) {
        while (getline(airline, each_row)) {
            // Process this row;
            Vertice new_vertex(each_row);
            new_vertex.print();
            count++;
        }
        std::cout<< count << std::endl;
        return true;
    }

    return false;
}

bool processRouteData(string& filename) {
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

    if (!processAirlineData(airline_file))
        std::cout<< "Invalid airline_file." << std::endl;

    if (!processAirportData(airport_file))
        std::cout<< "Oops cannot read airport file." << std::endl;

    if (!processRouteData(route_file))
        std::cout<< "You're fucked." << std::endl;


    return 0;
}