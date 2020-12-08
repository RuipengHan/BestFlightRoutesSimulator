//
// Created by Ruipeng Han on 11/30/20.
//

#ifndef FINAL_PROJECT_VERTEX_H
#define FINAL_PROJECT_VERTEX_H
#include <string>
#include <iostream>

using namespace std;
// Vertex is represented as an airport.
class Vertex {
public:
    string airport_id_;
    string name_;
    string city_;
    string country_;
    double latitude_;
    double longitude_;
    double altitude_;
    bool invalid_vertex_; // used to deal with invalidVertex and invalidEdge in Graph.cpp;
    Vertex(string info); // Receiving in a string and Parse by comma；
    Vertex() {  }

    /**
     * Construct an invalid vertex. Please see
     * @param invalid
     */
    Vertex(bool invalid);
    void print();

    /**
     * Compares two vertice' source and dest.
     * @param other - the edge to compare with
     */
    bool operator!=(Vertex other) const {
        return !(this->airport_id_ == other.airport_id_);
    }

    bool operator==(const Vertex &other) const {
        return airport_id_ == other.airport_id_;
    }

    bool operator<(const Vertex &other) const {
        // return stod(airport_id_) < stod(other.airport_id_);
        return airport_id_ < other.airport_id_;
    }
};

#endif //FINAL_PROJECT_VERTEX_H
