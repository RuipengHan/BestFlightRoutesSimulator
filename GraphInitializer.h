//
// Created by Ruipeng Han on 12/6/20.
//

#ifndef FINAL_PROJECT_GRAPHINITIALIZER_H
#define FINAL_PROJECT_GRAPHINITIALIZER_H

#include <iostream>
#include <fstream>
#include "graph.h"
#include "Vertex.h"
#include "edge.h"
using namespace std;
//Edge::AirlineMap Edge::id_airline_info_map_ = {};
class GraphInitializer {

public:
    GraphInitializer(Graph& graph, string airport_file, string airline_file, string route_file);

    /**
     * Initialize the graph.
     * @return Return false if any of the three files failed to open;
     */
    bool GraphInit();

    Graph GetGraph();
private:
    Graph & graph_;
    string airport_file_;
    string airline_file_;
    string route_file_;
    bool init_success_;
    map<pair<string, string>, vector<string>> all_airlines_in_edge_map_;
    map<string, Vertex> airport_dict_;


    vector<string> parseByComma(string info);
    bool connectVertices();
    bool addAirportVertices();
    void initializeEdge();
    bool processAirlineFile();

};
#endif //FINAL_PROJECT_GRAPHINITIALIZER_H
