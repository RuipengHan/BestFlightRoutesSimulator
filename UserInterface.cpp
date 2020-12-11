//
// Created by Ruipeng Han on 12/10/20.
//

#include "UserInterface.h"
#define MAGENTA "\033[35m"      /* Magenta */
#define RESET   "\033[0m"
UserInterface::UserInterface(Graph& graph) : graph_(graph) {
    //graph_ = graph;
    end_ = false;
    type_ = -1;
}

void UserInterface::Communicate() {
    int id1, id2, id3;
    cout << MAGENTA << "What type of search do you want to perform?" << endl;
    cout << MAGENTA << "Enter 0 to find all possible paths between two airport." << endl;
    cout << MAGENTA << "Enter 1 to find the shortest paths between two airport." << endl;
    cin >> type_;

    while (!end_) {
        cout << MAGENTA << "Please enter the ID for the departure airport" << endl;
        cin >> id1;
        cout << MAGENTA << "Please enter the ID for the destination airport" << RESET << endl;
        cin >> id2;
        if (type_ == BFS_) {
            RunBFS(id1, id2);
        } else if (type_ == DIJKSTRA) {
//            cout << "Please enter the ID for the destination airport" << endl;
//            cin >> id3;
            RunDijkstra(id1, id2);
        } else {
            cout << "The operation code you entered is invalid. Ending the program." << endl;
            end_ = true;
        }
        end_ = true;
    }
}

void UserInterface::RunBFS(int id_1, int id_2) {
    string id1 = to_string(id_1);
    string id2 = to_string(id_2);
    Vertex start = graph_.getVertexById(id1);
    Vertex end = graph_.getVertexById(id2);
    //Vertex end = graph.getVertexByName("Chicago O\'Hare International Airport");
    BFS bfs(graph_, start, end, 2);
    bfs.findPath();
}

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


void UserInterface::RunDijkstra(int id_1, int id_2) {
    string id1 = to_string(id_1);
    string id2 = to_string(id_2);
    Vertex start = graph_.getVertexById(id1);
    Vertex end = graph_.getVertexById(id2);
    AlgoImpl Di(graph_, start);
    map<Vertex, Vertex> p = Di.Dijkstra(graph_, start);
    vector<Vertex> paths = GetPathsFromPreviousMap(p, start, end);
    Di.print(paths);
}
