//
// Created by Ruipeng Han on 11/30/20.
//

#ifndef FINAL_PROJECT_VERTEX_H
#define FINAL_PROJECT_VERTEX_H
#include <string>
#include <iostream>
using namespace std;
// Vertex is represented as an airport.
class Vertice {
public:
    string airport_id_;
    string name_;
    string city_;
    string country_;
    double latitude_;
    double longitude_;
    double altitude_;
    Vertice(string info); // Receiving in a string and Parse by comma；
    void print();
};

#endif //FINAL_PROJECT_VERTEX_H
