//
// Created by Ruipeng Han on 11/30/20.
//
#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
using namespace std;

vector<string> parseByComma(string info) {
    vector<string> result;
    stringstream s_stream(info); //create string stream from the string

    //vector<string> parsed_row;
    string line;
    while (std::getline(s_stream, line)) {        // read full line
        const char *mystart=line.c_str();    // prepare to parse the line - start is position of begin of field
        bool instring{false};
        for (const char* p=mystart; *p; p++) {  // iterate through the string
            if (*p=='"')                        // toggle flag if we're btw double quote
                instring = !instring;
            else if (*p==',' && !instring) {    // if comma OUTSIDE double quote
                result.push_back(string(mystart,p-mystart));  // keep the field
                mystart=p+1;                    // and start parsing next one
            }
        }
        result.push_back(string(mystart));   // last field delimited by end of line instead of comma
    }
    return result;
}

/*
 * This process route data by going through all possible departure/dest airport.
 * The edge is initially empty of airlines. This function is just responsible for connecting a basic line between nodes.
 */
bool connectVertice(string& filename, Graph& graph, map<string, Vertex>& airport_dic) {

    ifstream route(filename);
    string each_row;
    int counter = 0; vector<string> list_of_unknown_airport_in_route;
    vector<string> parsed_result;
    if (route.is_open()) {
        while (getline(route, each_row)) {
            parsed_result = parseByComma(each_row);
            Vertex start = airport_dic.find(parsed_result[3])->second;
            Vertex end = airport_dic.find(parsed_result[5])->second;
            if (!graph.edgeExists(start, end) && start.airport_id_ != "" && end.airport_id_ != "") {
                graph.insertEdge(start, end);
            }
        }
         cout<< "Number of unknown airport trying to add edge is: " << counter << endl;
        for (string each: list_of_unknown_airport_in_route)
            cout<< "Number of unknown airport trying to add edge is: " << each << endl;
        return true;
    }
    return false;
}

/**
 * Add vertices to graph only.
 * @param filename
 * @param graph
 * @return
 */
bool addAirportVertices(string& filename, Graph& graph, map<string, Vertex>& airport_dic) {
    ifstream airport(filename);
    string each_row;
    int count = 0;
    if (airport.is_open()) {
        // for each line of airport data:
        while (getline(airport, each_row)) {
            // Process this row;
            Vertex new_vertex(each_row);
            // Add the new vertex to graph;
            if (!graph.vertexExists(new_vertex))
                graph.insertVertex(new_vertex);
            // Add the new vertex to the dictionary.
            if (airport_dic.find(new_vertex.airport_id_) == airport_dic.end())
                airport_dic.insert({new_vertex.airport_id_, new_vertex});
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
    map<string, Vertex> airport_dict;


    // Add vertices first meanwhile correlating each airport vertex to its id (populate the airport_dict)
    if (!addAirportVertices(airport_file, graph, airport_dict))
        std::cout<< "Oops cannot read airport file." << std::endl;

    // Then connect edge.
    if (!connectVertice(route_file, graph, airport_dict))
        std::cout<< "Invalid airline_file." << std::endl;

    if (!initializeEdge(route_file))
        std::cout<< "Oops cannot read route file." << std::endl;

    std::cout<< "NUMBER OF AIRPORT called using getVertices.size(): " << graph.getVertices().size() << std::endl;
    std::cout<< "SIZE OF THE MAP: " << airport_dict.size() << std::endl;
    std::cout<< "NUMBER OF EDGES IN THE GRAPH: " << graph.getEdges().size() << std::endl;
    return 0;
}