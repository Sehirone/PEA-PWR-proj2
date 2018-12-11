#pragma once
#include "AdjacencyMatrix.h"
class tabuSearch
{
private: 
	AdjacencyMatrix cities;
	int* shortestRoute = nullptr;
	int shortestRouteValue = INT_MAX;
	const int startNode = 0; // starting node should be 0
	void initRoute();
	void copySolution(int *from, int *to);
	void swapElements(int * route, int i, int j);
	int calculateRouteLength(int * route);

public:
	tabuSearch();
	~tabuSearch();

	int setSource(string filename);
	string printSource();

	string getShortestRoute();
	int getShortestRouteValue();
	void solve(int repetitions = 200, int repetitionsTillTabuRemoval = 10, int aspirationValue = -10);
};

