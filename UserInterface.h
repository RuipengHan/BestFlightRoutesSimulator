//
// Created by Ruipeng Han on 12/10/20.
//

#ifndef FINAL_PROJECT_USERINTERFACE_H
#define FINAL_PROJECT_USERINTERFACE_H
#include <iostream>
#include "BFS.h"
#include "graph.h"
#include "AlgoImpl.h"
using namespace std;
class UserInterface {
public:
    UserInterface(Graph& graph);
    void Communicate();
    void RunBFS(int id_1, int id_2);
    void RunDijkstra(int id_1, int id_2);
    void RunLandmark();

private:
    Graph& graph_;
    bool end_;
    short type_;
    bool help_; /* The help keyword used when the user polls up airport information.*/
    enum { BFS_ = 0, DIJKSTRA = 1, LANDMARK = 2};
};
#endif //FINAL_PROJECT_USERINTERFACE_H
