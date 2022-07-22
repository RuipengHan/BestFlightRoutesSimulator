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
    cout << MAGENTA << "You can enter '-1' anytime to get a reference of each airport id to its English name." << endl;
    cout << MAGENTA << "What type of search do you want to perform?" << endl;

    while (!end_) {
        cout << MAGENTA << "Enter 0 to find all possible paths between two airport." << endl;
        cout << MAGENTA << "Enter 1 to find the shortest paths between two airport." << RESET <<endl;
        cin >> type_;

        if (type_ == -1) {
            graph_.PrintDictionary();
            continue;
        }

        cout << MAGENTA << "Please enter the ID for the departure airport" << endl;
        cin >> id1;
        if (id1 == -1) {
            graph_.PrintDictionary();
            continue;
        }

        cout << MAGENTA << "Please enter the ID for the destination airport" << RESET << endl;
        cin >> id2;
        if (id2 == -1) {
            graph_.PrintDictionary();
            continue;
        }

        if (type_ == BFS_) {
            RunBFS(id1, id2);
        } else if (type_ == DIJKSTRA) {
            RunDijkstra(id1, id2);
        } else {
            cout << "The operation code you entered is invalid. Ending the program." << endl;
            end_ = true;
        }
        cout << MAGENTA << "Do you wish you do another operation? Enter 1 as yes or 0 as no." << RESET << endl;
        cin >> end_;
        end_ = !end_;
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
