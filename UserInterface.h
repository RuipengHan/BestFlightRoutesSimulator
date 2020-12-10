//
// Created by Ruipeng Han on 12/10/20.
//

#ifndef FINAL_PROJECT_USERINTERFACE_H
#define FINAL_PROJECT_USERINTERFACE_H
class UserInterface {
public:
    UserInterface();
    void Communicate();
    void RunBFS();
    void RunDijkstra();
    void RunLandmark();

private:
    bool end_;
    short type_;
    enum { BFS = 0, DIJKSTRA = 1, LANDMARK = 2};
};
#endif //FINAL_PROJECT_USERINTERFACE_H
