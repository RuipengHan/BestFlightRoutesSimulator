/**
 * @file AlgoImpl.h
 * Implementing Dijkstra Algorithm
 */

#pragma once

#include <queue>
#include <vector>
#include "graph.h"

class AlgoImpl {
public:
    AlgoImpl(Graph& graph, Vertex& start);

    /**
     * Dijkstra algorithm implementation
     * @param graph 
     * @param s The starting vertex
     * @return a map with every vertex as key and its corresponding previous vertex as value
     */
    map<Vertex, Vertex> Dijkstra(Graph& graph, Vertex& s);

    /**
     * Find shortest path given start point, end point, and landmark
     * @param graph 
     * @param start The start vertex
     * @param end The end vertex
     * @param middle The landmark
     * @return a vector containing each vertex from start to end
     */
    vector<Vertex> landmark(Graph& graph, Vertex& start, Vertex& end, Vertex& middle);

    /**
     * Find shortest path given start point and end point
     * @param graph 
     * @param start The start vertex
     * @param end The end vertex
     * @return a vector containing each vertex from start to end
     */
    vector<Vertex> getShortestPath(Graph& graph, Vertex& start, Vertex& end);

private:

};