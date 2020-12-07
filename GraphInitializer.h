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
    /**
     * ONLY constructor of GraphInitializer; takes in three file addresses.
     * @param graph Graph to be initialized
     * @param airport_file
     * @param airline_file
     * @param route_file
     */
    GraphInitializer(Graph& graph, string airport_file, string airline_file, string route_file);

    /**
     * Initialize the graph.
     * @return Return false if any of the three files failed to open;
     */
    bool GraphInit();

    Graph& GetGraph();
private:
    Graph & graph_;       // Graph to be initialized
    string airport_file_; // Address of file
    string airline_file_; // Address of file
    string route_file_;   // Address of file
    bool init_success_;   // indicator of successful initialization.

    /**
     * Map the <source, dest> (edge) to all of its airline IDs.
     */
    map<pair<string, string>, vector<string>> all_airlines_in_edge_map_;

    /**
     * Map airport ID to its vertex.
     */
    map<string, Vertex> airport_dict_;


    /**
     * Parse a single line of text by comma.
     * @param info
     * @return Vector of entries in the line.
     */
    vector<string> parseByComma(string info);

    /**
     * First step of Initialization:
     * Add all airport/vertices to the graph.
     * @return True if sucessfully read the file
     */
    bool addAirportVertices();

    /**
     * Second step of initialization：
     * Connect the single edge in the graph;
     * @return True if sucessfully read the file
     */
    bool connectVertices();

    /**
     * Third step of initialization:
     * Initialize the id_airline_info_map_ that maps the airline id to its row info,
     * which is used in the next step.
     * @return True if sucessfully read the file
     */
    bool processAirlineFile();

    /**
     * Last step of initialization:
     * Using id_airline_info_map_, initialize the vector<Airline> in each edge,
     * that is, make sure each edge in the graph has all airelines in it.
     */
    void initializeEdge();
};
#endif //FINAL_PROJECT_GRAPHINITIALIZER_H
