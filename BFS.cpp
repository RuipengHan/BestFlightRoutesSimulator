#include "BFS.h"
#include "graph.h"

#include <queue>
#include <vector>
#include <algorithm>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

void BFS::printPath(vector<Vertex>& path)
{
    int size = path.size();
    cout << GREEN << path[0].name_ << RESET << BLUE << "->" << RESET;
    for (int i = 1; i < size - 1; i++)
        cout << RED << path[i].name_ << BLUE "->";
    cout << GREEN << path[size - 1].name_ << endl;
}

std::vector<std::vector<Vertex>> BFS::findPath() {
    std::cout << "start airport is: ";
    start_.print();
    std::cout << "end airport is: ";
    end_.print();

	std::vector<std::vector<Vertex>> toReturn;

    queue<vector<Vertex>> q;    // queue to add all possible path
    vector<Vertex> path;    // path vector to store the current path 
    
    path.push_back(start_);
    q.push(path);

    while (!q.empty()) {
        path = q.front();
        q.pop();
        Vertex curr = path[path.size() - 1];
        //std::cout << "current airport is: ";  //print_line---------------------------------------------------------
        //curr.print();  //print_line---------------------------------------------------------

        //if last airport of the curr path is the destination or reach limited airport num
        if ((int)path.size() >= num_ || curr == end_) {
            //std::cout << "reach search num or found airport" << std::endl;  //print_line---------------------------------------------------------
            if (curr == end_) { // if the airport is the destination
                printPath(path);
                toReturn.push_back(path);
            }
        }
        else { //if not, traverse all possible airport adjacent to the curr airport
            std::vector<Vertex> adjacent_airports = graph_.getAdjacent(curr);
            //std::cout << "number of adjacent airports: " << adjacent_airports.size() << endl;  //print_line---------------------------------------------------------
            for (unsigned i = 0; i < adjacent_airports.size(); i++) {
                //adjacent_airports[i].print();  //print_line---------------------------------------------------------
                //if could not find current airport in the path
                if (std::find(path.begin(), path.end(), adjacent_airports[i]) == path.end()) {
                    vector<Vertex> newPath(path);
                    newPath.push_back(adjacent_airports[i]);
                    q.push(newPath);
                }
            }
        }
    }
    if (toReturn.empty()) {
        std::cout <<RED<< "no possible routes from " << start_.name_ << " to " << end_.name_ << " within " << num_ << " airport limit" << RESET <<std::endl;
    }

	return toReturn;
}