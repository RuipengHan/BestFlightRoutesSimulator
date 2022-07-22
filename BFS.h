/**
 * @file BFS.h
 * Implementing BFS traversal
 */

#pragma once

#include <queue>
#include <vector>

#include "traversal.h"
#include "graph.h"

class BFS {
public:
	BFS(const Graph& graph, const Vertex& start, const Vertex& end, int num) : graph_(graph), start_(start), end_(end), num_(num) { }

	std::vector<std::vector<Vertex>> findPath();

	void printPath(vector<Vertex>& path);

private:
	Graph graph_;
	Vertex start_;
	Vertex end_;
	int num_;
};

/*
	A
	|  \----------------
	|                  \ D
	|				   / |
	|	--------------   E
	| /----------------/
	B-----------------------------N
*/