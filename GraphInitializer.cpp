//
// Created by Ruipeng Han on 12/6/20.
//

#include "GraphInitializer.h"
GraphInitializer::GraphInitializer(Graph& graph, string airport_file, string airline_file, string route_file):graph_(graph) {
    airport_file_ = airport_file;
    airline_file_ = airline_file;
    route_file_ = route_file;
    init_success_ = true;

}

bool GraphInitializer::GraphInit() {
    // Add vertices first meanwhile correlating each airport vertex to its id (populate the airport_dict_). Checked Okay
    if (!addAirportVertices())
        std::cout<< "Oops cannot read airport file." << std::endl;

    // Then connect edge. Checked Okay
    if (!connectVertices())
        std::cout<< "Invalid airline_file." << std::endl;

    // Then map the airline id to its data; Checked Okay
    if (!processAirlineFile())
        std::cout<< "Oops cannot read route file." << std::endl;

    initializeEdge();
    std::cout<< "NUMBER Airlines: " << Edge::id_airline_info_map_.size() << std::endl;
    std::cout<< "NUMBER OF AIRPORT called using getVertices.size(): " << graph_.getVertices().size() << std::endl;
    std::cout<< "SIZE OF THE MAP: " << airport_dict_.size() << std::endl;
    std::cout<< "NUMBER OF EDGES IN THE GRAPH: " << graph_.getEdges().size() << std::endl;
    return init_success_;
}

vector<string> GraphInitializer:: parseByComma(string info) {
    vector<string> result;
    stringstream s_stream(info); //create string stream from the string
    string line;
    while (std::getline(s_stream, line)) {        // read full line
        const char *mystart = line.c_str();    // prepare to parse the line - start is position of begin of field
        bool instring{false};
        for (const char* p=mystart; *p; p++) {  // iterate through the string
            if (*p == '"')                        // toggle flag if we're btw double quote
                instring = !instring;
            else if (*p == ',' && !instring) {    // if comma OUTSIDE double quote
                result.push_back(string(mystart,p-mystart));  // keep the field
                mystart = p+1;                    // and start parsing next one
            }
        }
        result.push_back(string(mystart));   // last field delimited by end of line instead of comma
    }
    return result;
}

bool GraphInitializer::addAirportVertices() {
    ifstream airport(airport_file_);
    string each_row;
    int count = 0;
    if (airport.is_open()) {
        // for each line of airport data:
        while (getline(airport, each_row)) {
            Vertex new_vertex(each_row);
            // Add the new vertex to graph;
            if (!graph_.vertexExists(new_vertex))
                graph_.insertVertex(new_vertex);
            // Add the new vertex to the dictionary, which maps the airport ID to its vertex.
            if (airport_dict_.find(new_vertex.airport_id_) == airport_dict_.end())
                airport_dict_.insert({new_vertex.airport_id_, new_vertex});
            count++;
        }
        std::cout<< "AFTER READ, WE HAVE NUM OF AIRPORTS: " << count << std::endl;
        return true;
    }

    return false;
}

double GraphInitializer::calculateDist(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes and longitudes 
    double dLat = (lat2 - lat1) * M_PI / 180.0; 
    double dLon = (lon2 - lon1) * M_PI / 180.0; 
    // convert to radians 
    lat1 = (lat1) * M_PI / 180.0; 
    lat2 = (lat2) * M_PI / 180.0; 
    // apply formulae 
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2); 
    double rad = 6371; 
    double c = 2 * asin(sqrt(a)); 
    return rad * c; 
}

double GraphInitializer::calculateDistTest(double lat1, double lon1, double lat2, double lon2) {
    return calculateDist(lat1, lon1, lat2, lon2);
}

bool GraphInitializer::connectVertices() {
    ifstream route(route_file_);
    string each_row;
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

            Vertex start = airport_dict_.find(parsed_result[3])->second;
            Vertex end = airport_dict_.find(parsed_result[5])->second;
            // If the graph doesn't contain the edge yet, insert.
            if (!graph_.edgeExists(start, end) && start.airport_id_ != "" && end.airport_id_ != "") {
                graph_.insertEdge(start, end);

                // Set edge's weight using distance between two vertices
                double dist = calculateDist(start.latitude_, start.longitude_, end.latitude_, end.longitude_);
                graph_.setEdgeWeight(start, end, (int)dist);
            }
            pair<string, string> edge_key{start.airport_id_, end.airport_id_};
            if (all_airlines_in_edge_map_.find(edge_key) != all_airlines_in_edge_map_.end() && start.airport_id_ != "" && end.airport_id_ != "") {
                // If this airline hasn't been recorded in the edge yet, add it. This prevents duplicate of airlines in the edge.
                if (find(all_airlines_in_edge_map_[edge_key].begin(), all_airlines_in_edge_map_[edge_key].end(), parsed_result[1]) == all_airlines_in_edge_map_[edge_key].end())
                    all_airlines_in_edge_map_[edge_key].push_back(parsed_result[1]); // parsed_result[1] is the airline id
            }
            else if (start.airport_id_ != "" && end.airport_id_ != "") {
                vector<string> value;
                value.push_back(parsed_result[1]);
                all_airlines_in_edge_map_.insert({edge_key, value}); // insert it if no previous record found.
            }
        }
        cout<< "Number of edges in the all_airlines_in_edge_map is: " << all_airlines_in_edge_map_.size() << endl;
        return true;
    }
    return false;
}


bool GraphInitializer::processAirlineFile() {
    ifstream airline(airline_file_);
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

void GraphInitializer::initializeEdge() {
    // pc: loop through every route data
    vector<Edge> edges = graph_.getEdges();
    for (Edge& edge : edges) {
        // Use the map and pass in the source+dest key to find vector of all airport ids and add it to the edge.
        Edge& edge_update = graph_.getEdgeReference(edge.source, edge.dest);
        edge_update.addAirline(all_airlines_in_edge_map_[{edge.source.airport_id_, edge.dest.airport_id_}], Edge::id_airline_info_map_);
    }
}

Graph& GraphInitializer::GetGraph() {
    return graph_;
}

map<string, Vertex> GraphInitializer::GetAirportDict() const{
    return airport_dict_;
}

map<pair<string, string>, vector<string>> GraphInitializer::Getall_airlines_in_edge_map_() const {
    return all_airlines_in_edge_map_;
}