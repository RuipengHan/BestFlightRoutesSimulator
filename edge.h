/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <string>
#include <limits.h>
#include "Vertex.h"
#include <map>
using std::string;

//typedef string Vertex;


/**
 * Represents an edge in a graph; used by the Graph class.
 * Specially it represents a connection between two airport;
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge {
    struct Airline {
        string name_;
        string id_;
        string country_;

        Airline(string info) {
            // Parse
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
            id_ = result[0];
            name_ = result[1];
            country_ = result[6];
        }
    };

public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     */
    Edge(Vertex u, Vertex v)
            : source(u), dest(v), label(""), weight(-1)
    { /* nothing */
    }

    /**
     * Parameter constructor for unweighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, string lbl)
            : source(u), dest(v), label(lbl), weight(-1)
    { /* nothing */
    }

    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the weight of the edge
     * @param lbl - the edge label
     */
    Edge(Vertex u, Vertex v, int w, string lbl)
            : source(u), dest(v), label(lbl), weight(w)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(""), dest(""), label(""), weight(-1)
    { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }

    /**
     * Gets edge label.
     */
    string getLabel() const
    {
        return this->label;
    }

    /**
     * Gets edge weight.
     */
    int getWeight() const
    {
        return this->weight;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }

    /**
     * Add given airline to the route/edge.
     * @param airline
     */
    void addAirline(string airline) {
        Airline new_airline(airline);
        airlines_.push_back(new_airline);
    }

private:
    string label; /**< The edge label **/
    int weight; /**< The edge weight (if in a weighed graph) In this case, it is the distance between 2 airports**/
    vector<Airline> airlines_;
    map<string, pair<string, string>> airline_map;
};