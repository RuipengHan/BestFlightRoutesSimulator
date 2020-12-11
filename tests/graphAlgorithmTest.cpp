//
// Created by Ruipeng Han on 12/7/20.
//

#include <algorithm>
#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../GraphInitializer.h"
#include "../AlgoImpl.h"
/**
 * This test file will test the algorithm and traversal part of the graph.
 */
using namespace std;
string airport_file_test__ = "tests/airports_test.dat.txt";
string airline_file_ = "data_set/airlines.dat.txt";
string route_file_ = "tests/routes_test.txt";
string airport_file_test_landmark = "tests/airports_landmark.txt";
string route_file_landmark = "tests/routes_landmark.txt";

Graph graph__(true, true);
Graph graph_landmark_test(true, true);
GraphInitializer graphInitializer_(graph__, airport_file_test__, airline_file_, route_file_);
GraphInitializer graphInitializer_landmark(graph_landmark_test, airport_file_test_landmark, airline_file_, route_file_landmark);

vector<Vertex> GetPathsFromPreviousMap(map<Vertex, Vertex>& previous, Vertex start, Vertex end) {
    vector<Vertex> paths;
    paths.push_back(end);// insert the end first;
    Vertex current = previous[end];;
    paths.push_back(current);
    while (current != start) {
        current = previous[current];
        paths.push_back(current);
    }
    reverse(paths.begin(), paths.end());
    return paths;
}

TEST_CASE("Dikjstra Beijing to Nanyuan (direct path)", "step 0") {
    graphInitializer_.GraphInit();
    Vertex start = graph__.getVertexById("1");
    Vertex end = graph__.getVertexById("2");
    AlgoImpl Di(graph__, start);
    map<Vertex, Vertex> p = Di.Dijkstra(graph__, start);
    vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);

    REQUIRE((paths[0] == start && paths[1] == end) == true);
}

TEST_CASE("Dikjstra Beijing Capital to O'hare (indirect path)", "step 0") {
    graphInitializer_.GraphInit();
    Vertex start = graph__.getVertexById("1");
    Vertex end = graph__.getVertexById("6");
    AlgoImpl Di(graph__, start);
    // Get the previous map.
    map<Vertex, Vertex> p = Di.Dijkstra(graph__, start);
    // Get the path from the map
    vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);
    // This is the expected airport in the path
    Vertex nanyuan = graph__.getVertexById("2");
    // The airport must match exactly as expected.
    REQUIRE((paths[0] == start && paths[1] == nanyuan && paths[2] == end) == true);
}


TEST_CASE("Landmark 1 ", "step 0") {
    graphInitializer_landmark.GraphInit();
    Vertex start = graph_landmark_test.getVertexById("1");
    Vertex landmark = graph_landmark_test.getVertexById("5");
    Vertex end = graph_landmark_test.getVertexById("4");
    AlgoImpl Di(graph_landmark_test, start);
    vector<Vertex> paths = Di.landmark(graph_landmark_test, start, end, landmark);
    //vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);
    Vertex nanyuan = graph_landmark_test.getVertexById("2");
    REQUIRE((paths[0] == start && paths[1] == landmark && paths[2] == end) == true);
}


TEST_CASE("Landmark 2", "step 0") {
    Vertex start = graph_landmark_test.getVertexById("1");
    Vertex landmark = graph_landmark_test.getVertexById("5");
    Vertex end = graph_landmark_test.getVertexById("7");
    AlgoImpl Di(graph_landmark_test, start);
    vector<Vertex> paths = Di.landmark(graph_landmark_test, start, end, landmark);
    //vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);
    Vertex nanyuan = graph_landmark_test.getVertexById("2");
    REQUIRE((paths[0] == start && paths[1] == landmark && paths[2] == end) == true);
}


//TEST_CASE("Landmark 3", "step 0") {
//    //cout << "11111111111 :" << endl;
//    graphInitializer_landmark.GraphInit();
//    Vertex start = graph_landmark_test.getVertexById("1");
//    Vertex landmark = graph_landmark_test.getVertexById("5");
//    Vertex end = graph_landmark_test.getVertexById("7");
//    graph_landmark_test.removeEdge(landmark, end);
//    //cout << "11111111111 :" << endl;
//    AlgoImpl Di(graph_landmark_test, start);
//    vector<Vertex> paths = Di.landmark(graph_landmark_test, start, end, landmark);
//    //cout << "22222222222 :" << endl;
//    //vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);
//    Vertex ohare = graph_landmark_test.getVertexById("6");
//    Vertex pudong = graph_landmark_test.getVertexById("3");
//    cout << "Start :" << paths[0].airport_id_ << ", " << paths[1].airport_id_ << ", " << paths[2].airport_id_ << ", " << paths[3].airport_id_ << endl;
//    cout << "route 1 5 3 7 :" << graph_landmark_test.getEdgeWeight(start, landmark) + graph_landmark_test.getEdgeWeight(landmark, ohare) + graph_landmark_test.getEdgeWeight(ohare, end) << endl;
//    cout << "route 1 5 6 7 :" <<  graph_landmark_test.getEdgeWeight(start, landmark) + graph_landmark_test.getEdgeWeight(landmark, pudong) + graph_landmark_test.getEdgeWeight(pudong, end) << endl;
//
//    cout << "5 to 6 :" <<  graph_landmark_test.getEdgeWeight(landmark, ohare) << endl;
//    cout << "5 to 3 :" <<  graph_landmark_test.getEdgeWeight(landmark, pudong) << endl;
//    cout << "6 to 7 :" <<  graph_landmark_test.getEdgeWeight(ohare, end) << endl;
//    cout << "3 to 7 :" <<  graph_landmark_test.getEdgeWeight(pudong, end) << endl;
//    REQUIRE((paths[0] == start && paths[1] == landmark && paths[2] == ohare && paths[3] == end) == true);
//
//}