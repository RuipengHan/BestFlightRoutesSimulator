//
// Created by Ruipeng Han on 12/5/20.
//
#include <algorithm>
#include "../cs225/catch/catch.hpp"
#include "/Users/ruipenghan/cs225git/final_project/graph.h"
#include "/Users/ruipenghan/cs225git/final_project/GraphInitializer.h"
/**
 * This test file will test the initialization of the graph and reading of the file.
 */
using namespace std;
Edge::AirlineMap Edge::id_airline_info_map_ = {};

map<pair<string, string>, vector<string>> all_airlines_in_edge_map;
map<string, Vertex> airport_map;
map<pair<string, string>, int> all_edges;
map<pair<string, string>, map<string, int>> expected_airlines_edge;
Graph graph(true, true);
string airport_file = "data_set/airports.dat.txt";
string airline_file = "data_set/airlines.dat.txt";
string route_file = "data_set/routes.dat.txt";

GraphInitializer graphInitializer(graph, airport_file, airline_file, route_file);

vector<string> parseByComma(string info) {
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

// Vector version of vector is much slower than the map. I put it here just to remind me. Below is the faster one.
//vector<string> TestAirportVerticesHelper() {
//    vector<string> all_unique_airport_id;
//    ifstream airport(airport_file);
//    string each_row;
//    if (airport.is_open()) {
//        while (getline(airport, each_row)) {
//            string id = parseByComma(each_row)[0];
//            // If this id isn't in the vector yet, add it.
//            if (find(all_unique_airport_id.begin(), all_unique_airport_id.end(), id) == all_unique_airport_id.end())
//                all_unique_airport_id.push_back(id);
//        }
//    }
//    return all_unique_airport_id;
//}

map<string, int> TestAirportVerticesHelper() {
    map<string, int> all_unique_airport_id;
    ifstream airport(airport_file);
    string each_row;
    if (airport.is_open()) {
        while (getline(airport, each_row)) {
            string id = parseByComma(each_row)[0];
            // If this id isn't in the vector yet, add it.
            if (all_unique_airport_id.find(id) == all_unique_airport_id.end())
                all_unique_airport_id.insert({id, 1});
        }
    }
    return all_unique_airport_id;
}

map<pair<string, string>, map<string, int>> TestConnectVerticesEdgeAirlinesHelper() {
    // Edge maps to this vector of airlines (using a map)
    map<pair<string, string>, map<string, int>> actual_airlines_edge;
    ifstream route(route_file);
    string each_row;
    if (route.is_open()) {
        while (getline(route, each_row)) {
            vector<string> parsed_result = parseByComma(each_row);
            if (parsed_result[1].find_first_of("0123456789") == std::string::npos ||
                parsed_result[3].find_first_of("0123456789") == std::string::npos ||
                parsed_result[5].find_first_of("0123456789") == std::string::npos ||
                airport_map.find(parsed_result[3]) == airport_map.end() ||
                airport_map.find(parsed_result[5]) == airport_map.end()) {
                continue;
            }
            pair<string,string> this_edge  = {parsed_result[3], parsed_result[5]};
            // If this edge is not yet included, add it.
            if (actual_airlines_edge.find(this_edge) == actual_airlines_edge.end()) {
                map<string, int> airline;
                airline.insert({parsed_result[1], 1});
                actual_airlines_edge.insert({this_edge, airline});
            } else {
                // If this airline is not yet found:
                if (actual_airlines_edge[this_edge].find(parsed_result[1]) == actual_airlines_edge[this_edge].end()) {
                    actual_airlines_edge[this_edge].insert({parsed_result[1], 1});
                }
            }
        }
    }
    return actual_airlines_edge;
}


map<pair<string, string>, int> TestConnectVerticesHelper() {
    map<pair<string, string>, int> all_edges;
    ifstream route(route_file);
    string each_row;
    if (route.is_open()) {
        while (getline(route, each_row)) {
            vector<string> parsed_result = parseByComma(each_row);
            if (parsed_result[1].find_first_of("0123456789") == std::string::npos ||
                parsed_result[3].find_first_of("0123456789") == std::string::npos ||
                parsed_result[5].find_first_of("0123456789") == std::string::npos ||
                airport_map.find(parsed_result[3]) == airport_map.end() ||
                airport_map.find(parsed_result[5]) == airport_map.end()) {
                continue;
            }
            pair<string,string> this_edge  = {parsed_result[3], parsed_result[5]};
            if (all_edges.find(this_edge) == all_edges.end())
                all_edges.insert({this_edge, 1});
        }
    }
    return all_edges;
}

vector<string> AirlinesID(vector<Airline>& airlines) {
    vector<string> IDs;
    for (Airline& airline : airlines) {
        IDs.push_back(airline.id_);
    }
    return IDs;
}

TEST_CASE("Test parse by comma 1", "step 0") {
    string test_line = "s, 2, 1, string, good,, ";
    vector<string> expected = { "s", " 2", " 1", " string", " good", "", " " };
    vector<string> actual = graphInitializer.parseByComma(test_line);
    REQUIRE(expected == actual);
}

TEST_CASE("Test parse by comma, with double quotes and comma in side", "step 0") {
    string test_line = "s, 2, 1, \"string, good\", good,, ";
    vector<string> expected = { "s", " 2", " 1", " \"string, good\"", " good", "", " " };
    vector<string> actual = graphInitializer.parseByComma(test_line);
    REQUIRE(expected == actual);
}

// DON'T SWAP THE ORDER OF THIS TEST! OTHERWISE TESTS WILL BREAK;
TEST_CASE("Test addAirportVertices (bijection test)", "step 1") {
    map<string, int> all_ids = TestAirportVerticesHelper();
    graphInitializer.addAirportVertices(); // run the origin function;
    airport_map = graphInitializer.GetAirportDict();

    // 1. The vector of all ids should equal to the result graphInitializer.
    REQUIRE(all_ids.size() == airport_map.size());

    // 2. All airport ids in the map should exist in the vector of ids.
    bool test_pass = true;
    unsigned counter = 0;
    for (auto& key_val_pair : airport_map) {
        if (all_ids.find(key_val_pair.first) == all_ids.end()) {
            test_pass = false;
            break;
        }
        counter ++;
    }
    REQUIRE(test_pass == true);

    // 3: All airport ids in the vector should exist in the airport map.
    test_pass = true;
    for (auto& each_string : all_ids) {
        if (airport_map.find(each_string.first) == airport_map.end()) {
            test_pass = false;
            break;
        }
    }
    REQUIRE(test_pass == true);
    // If all three assertions pass, then a bijection relation between actual and expected is established.
    // The map is initialized correctly.
}

TEST_CASE("Test connectVertices (bijection test)", "step 2") {
    all_edges = TestConnectVerticesHelper();
    graphInitializer.connectVertices();
    vector<Edge> graph_edges = graphInitializer.GetGraph().getEdges();

    // 1. The vector of all ids should equal to the result graphInitializer.
    REQUIRE(all_edges.size() == graph_edges.size());

    // 2. All edges in the graph should exist in the vector of edges.
    bool test_pass = true;
    unsigned counter = 0;
    for (Edge& each_edge : graph_edges) {
        // Find whether or not this edge in the graph exist in the expected edges vector.
        if (all_edges.find(make_pair(each_edge.source.airport_id_, each_edge.dest.airport_id_)) == all_edges.end()) {
            test_pass = false;
            break;
        }
        counter ++;
    }
    REQUIRE(test_pass == true);

    // 3: All airport ids in the vector should exist in the airport map.
    map<pair<string, string>, int> graph_edges_in_pair;
    for (Edge& edge : graph_edges) { // convert it to map to fasten process.
        graph_edges_in_pair.insert({make_pair(edge.source.airport_id_, edge.dest.airport_id_), 1});
    }

    test_pass = true;
    for (auto& each_pair : all_edges) {
        if (graph_edges_in_pair.find(each_pair.first) == graph_edges_in_pair.end()) {
            test_pass = false;
            break;
        }
    }
    REQUIRE(test_pass == true);
    // If all three assertions pass, then a bijection relation between actual and expected is established.
    // The map is initialized correctly.
}

TEST_CASE("Test connectVertices on each edge's airlines)", "step 2") {
    // map<pair<string, string>, vector<string>>
    all_airlines_in_edge_map = graphInitializer.Getall_airlines_in_edge_map_();
    //map<pair<string, string>, map<string, int>>
    expected_airlines_edge = TestConnectVerticesEdgeAirlinesHelper();
    bool test_pass = true;
    bool should_break = false;
    // Test if all stuff in the actual one exist in the expected one.
    for (auto& each_actual_pair : all_airlines_in_edge_map) {
        // if a pair of edge in the actual doesn't exist in the expected, fail the test.
        if (expected_airlines_edge.find(each_actual_pair.first) == expected_airlines_edge.end()) {
            test_pass = false;
            break;
        } else if (expected_airlines_edge[each_actual_pair.first].size() != each_actual_pair.second.size()){
            // If size of edge in the expected doesn't equal to that of the actual one, fail the test.
            test_pass = false;
            break;
        } else {
            // Else, loop through every airline in this edge and see if they are exist in the expected value.
            for (string& each_airline_id : each_actual_pair.second) {
                if (expected_airlines_edge[each_actual_pair.first].find(each_airline_id) == expected_airlines_edge[each_actual_pair.first].end()) {
                    test_pass = false;
                    should_break = true;
                    break;
                }
            }
            if (should_break) {
                break;
            }
        }
    }

    REQUIRE(test_pass == true);


    // Reverse. Test if all stuff in the expected one exist in the actual one.
    test_pass = true;
    should_break = false;
    // Test if all stuff in the actual one exist in the expected one.
    for (auto& each_expected_pair : expected_airlines_edge) {
        // if a pair of edge in the actual doesn't exist in the expected, fail the test.
        if (all_airlines_in_edge_map.find(each_expected_pair.first) == all_airlines_in_edge_map.end()) {
            test_pass = false;
            break;
        } else if (all_airlines_in_edge_map[each_expected_pair.first].size() != each_expected_pair.second.size()){
            // If size of edge in the expected doesn't equal to that of the actual one, fail the test.
            test_pass = false;
            break;
        } else {
            // Else, loop through every airline in this edge and see if they are exist in the expected value.
            for (auto& each_airline_id : each_expected_pair.second) {
                if (find(all_airlines_in_edge_map[each_expected_pair.first].begin(), all_airlines_in_edge_map[each_expected_pair.first].end(),each_airline_id.first ) == all_airlines_in_edge_map[each_expected_pair.first].end()) {
                    test_pass = false;
                    should_break = true;
                    break;
                }
            }
            if (should_break) {
                break;
            }
        }
    }

    REQUIRE(test_pass == true);

    // If both assertions above pass, then a bijection relation between actual and expected is established.
    // The map is initialized correctly.
}

TEST_CASE("Test initialized edge - simple", "step 4") {
    graphInitializer.processAirlineFile();
    graphInitializer.initializeEdge();
    bool test_pass = true;
    int counter = 0;
    vector<Edge> graph_edges = graph.getEdges();
    for (Edge& edge : graph_edges) {
        if (edge.GetAirlines().size() < 1) {
            test_pass = false;
            break;
        }
    }
    REQUIRE(test_pass == true);
}

TEST_CASE("Test initialized edge", "step 4") {
    cout << "Testing last part... This will take a while." << endl;
    graphInitializer.processAirlineFile();
    graphInitializer.initializeEdge();
    // map<pair<string, string>, map<string, int>>
    vector<Edge> graph_edges = graph.getEdges();
    bool test_pass = true;
    bool should_break = false;
    int counter = 0;
    for (Edge& edge : graph_edges) {
        pair<string, string> current_pair = make_pair(edge.source.airport_id_, edge.dest.airport_id_);
        // if this edge in the graph doesn't exist in the expected edge map, fail the test. Should pass since this is
        // test in step 2 already.
        if (expected_airlines_edge.find(current_pair) == expected_airlines_edge.end()) {
            test_pass = false;
            break;
        } else if (expected_airlines_edge[current_pair].size() != edge.GetAirlines().size()) {
            // If number of airlines in the edge doesn't equal to the expected number, fail the test.
            test_pass = false;
             cout << "counter: "<<counter<< "Expected size: "<<expected_airlines_edge[current_pair].size() <<", actual: " << edge.GetAirlines().size() << endl;
            break;
        } else {
            // Loop through the airlines in the edge in graph and make sure every airline the edge exist in the expected.
            for (Airline& each_airline : edge.GetAirlines()) {
                if (expected_airlines_edge[current_pair].find(each_airline.id_) == expected_airlines_edge[current_pair].end()) {
                    should_break = true;
                    test_pass = false;

                    break;
                }
            }
        }
        if (should_break) {
            break;
        }
        counter++;
    }

    REQUIRE(test_pass == true);

    map<pair<string, string>, Edge> graph_edge_airlines_map;
    for (Edge& edge : graph_edges) {
        graph_edge_airlines_map.insert({make_pair(edge.source.airport_id_, edge.dest.airport_id_), edge});
    }

    test_pass = true;
    should_break = false;
    counter = 0;
    // map<pair<string, string>, map<string, int>>
    for (auto& edge : expected_airlines_edge) {
        pair<string, string> current_pair = edge.first;
        // if this edge in the graph doesn't exist in the expected edge map, fail the test. Should pass since this is
        // test in step 2 already.
        if (graph_edge_airlines_map.find(current_pair) == graph_edge_airlines_map.end()) {
            test_pass = false;
            break;
        } else if (edge.second.size() != graph_edge_airlines_map[current_pair].GetAirlines().size()) {
            // If number of airlines in the edge doesn't equal to the expected number, fail the test.
            test_pass = false;
            //cout << "counter: "<<counter<< "Expected size: "<<expected_airlines_edge[current_pair].size() <<", actual: " << edge.GetAirlines().size() << endl;
            break;
        } else {
            // Loop through the airlines in the edge's expected airlines and make sure every airline exist in the graph.
            for (auto& each_airline : edge.second) {
                // string airline id = each_airline.first
                vector<Airline> airlines_in_graph = graph_edge_airlines_map[current_pair].GetAirlines();
                vector<string> IDs = AirlinesID(airlines_in_graph);
                if (find(IDs.begin(), IDs.end(), each_airline.first) == IDs.end()) {
                    should_break = true;
                    test_pass = false;
                    break;
                }
            }
        }
        if (should_break) {
            break;
        }
        counter++;
    }

    REQUIRE(test_pass == true);
    // If both assertions above pass, then a bijection relation between actual and expected is established.
    // The map is initialized correctly.
}