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
map<pair<string, string>, vector<string>> all_airlines_in_edge_map;

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
            // MF THIS MF DATA SET. SPEND TWO WHOLE HOURS FIGURING OUT THAT AIRPORT ID CAN BE '\N'
            // If an ID doesn't contain numbers, that is, '\N', ignore this motherfk row entry.
            if (parsed_result[1].find_first_of("0123456789") == std::string::npos ||
                parsed_result[3].find_first_of("0123456789") == std::string::npos ||
                parsed_result[5].find_first_of("0123456789") == std::string::npos) {
                continue;
            }

            Vertex start = airport_dic.find(parsed_result[3])->second;
            Vertex end = airport_dic.find(parsed_result[5])->second;
            // If the graph doesn't contain the edge yet, insert.
            if (!graph.edgeExists(start, end) && start.airport_id_ != "" && end.airport_id_ != "") {
                graph.insertEdge(start, end);
            }
            pair<string, string> edge_key{start.airport_id_, end.airport_id_};
            if (all_airlines_in_edge_map.find(edge_key) != all_airlines_in_edge_map.end() && start.airport_id_ != "" && end.airport_id_ != "")
                all_airlines_in_edge_map[edge_key].push_back(parsed_result[1]); // parsed_result[1] is the airline id
            else if (start.airport_id_ != "" && end.airport_id_ != "") {
                vector<string> value;
                value.push_back(parsed_result[1]);
                all_airlines_in_edge_map.insert({edge_key, value}); // insert it if no previous record found.
            }
        }
        cout<< "Number of unknown airport trying to add edge is: " << counter << endl;
        cout<< "Number of edges in the  all_airlines_in_edge_map is: " << all_airlines_in_edge_map.size() << endl;
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

/**
 * Populate the edges with all airlines pass through it.
 * @param graph
 */
void initializeEdge(Graph& graph) {
    // pc: loop through every route data
    vector<Edge> edges = graph.getEdges();
    for (Edge& edge : edges) {
        // Use the map and pass in the source+dest key to find vector of all airport ids and add it to the edge.
        edge.addAirline(all_airlines_in_edge_map[{edge.source.airport_id_, edge.dest.airport_id_}], Edge::id_airline_info_map_);
    }

}

/**
 * Initialize the static variable map in edge.h; to let edge class has all airline information.
 * @param airline_file
 * @return
 */
bool processAirlineFile(string& airline_file) {
    ifstream airline(airline_file);
    string each_row;
    Edge edge;
    vector<string> result;

    if (airline.is_open()) {
        // for each line of airport data:
        while (getline(airline, each_row)) {
            result = parseByComma(each_row);
            // result[0] is the airline id; if it hasn't present in the map add it.
            if (Edge::id_airline_info_map_.find(result[0]) == Edge::id_airline_info_map_.end()) {
                Edge::id_airline_info_map_.insert({result[0], result});
            }
        }
        return true;
    }
    return false;
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
//    Graph graph(true, true);
//    map<string, Vertex> airport_dict;
//
//
//    // Add vertices first meanwhile correlating each airport vertex to its id (populate the airport_dict). Checked Okay
//    if (!addAirportVertices(airport_file, graph, airport_dict))
//        std::cout<< "Oops cannot read airport file." << std::endl;
//
//    // Then connect edge. Checked Okay
//    if (!connectVertice(route_file, graph, airport_dict))
//        std::cout<< "Invalid airline_file." << std::endl;
//
//    // Then map the airline id to its data; Checked Okay
//    if (!processAirlineFile(airline_file))
//        std::cout<< "Oops cannot read route file." << std::endl;
//
//    initializeEdge(graph);
//    std::cout<< "NUMBER Airlines: " << Edge::id_airline_info_map_.size() << std::endl;
//    std::cout<< "NUMBER OF AIRPORT called using getVertices.size(): " << graph.getVertices().size() << std::endl;
//    std::cout<< "SIZE OF THE MAP: " << airport_dict.size() << std::endl;
//    std::cout<< "NUMBER OF EDGES IN THE GRAPH: " << graph.getEdges().size() << std::endl;
    return 0;
}